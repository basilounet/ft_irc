#include <Server.h>

int Server::_sig = 0;

Server::Server() :
		_port(8080),
		_socket(-1),
		_addr() {
}

Server::Server(const int port, const std::string& password) :
		_port(port),
		_password(password),
		_socket(-1),
		_addr() {
}

Server::~Server() {
	for (std::vector<pollfd>::const_iterator it = _fds.begin(); it != _fds.end(); ++it)
		if (it->fd >= 0)
			close(it->fd);
}

Server::Server(const Server& src) :
		_port(),
		_socket(-1),
		_addr() {
	*this = src;
}

Server& Server::operator=(const Server& src) {
	if (this != &src) {
		_port = src._port;
		_password = src._password;
		_socket = src._socket;
		_addr = src._addr;
		_fds = src._fds;
		_clients = src._clients;
		_channels = src._channels;
	}
	return (*this);
}

std::map<int, Client>& Server::getClients() {
	return (_clients);
}

std::map<std::string, Channel>& Server::getChannels() {
	return (_channels);
}

const std::string &Server::getPassword() const {
	return _password;
}

void Server::createServer() {
	signal(SIGINT, &sigHandler);
	signal(SIGQUIT, &sigHandler);
	signal(SIGPIPE, SIG_IGN);
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	_fds.push_back((pollfd){_socket, POLLIN, 0});
	if (_socket < 0)
		throw (std::runtime_error("\033[31mError: socket creation failed\033[0m"));
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(_port);
	_addr.sin_addr.s_addr = INADDR_ANY;
	if (fcntl(_socket, F_SETFL, O_NONBLOCK) == -1)
		throw (std::runtime_error("\033[31mError : cannot setup option (O_NONBLOCK).\033[0m"));
	int yes = 1;
	if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
		throw (std::runtime_error("\033[31mError: setsockopt failed\033[0m"));
	if (bind(_socket, reinterpret_cast<sockaddr*>(&_addr), sizeof(_addr)) < 0)
		throw (std::runtime_error("\033[31mError: bind failed\033[0m"));
	if (listen(_socket, 5) == -1)
		throw (std::runtime_error("\033[31mError: listen failed\033[0m"));
	std::cout << "\033[32mServer is running on port " << _port << "\033[0m" << std::endl;
}

void Server::runServer() {
	while (_sig == 0)
	{
		int pollCount = poll(_fds.data(), _fds.size(), 0);
		if (_sig != 0)
			break ;
		if (pollCount < 0)
			throw (std::runtime_error("\033[31mError: poll failed\033[0m"));
		for (size_t i = 0; i < _fds.size(); ++i)
		{
			if (_fds[i].fd == _socket && _fds[i].revents & POLLIN)
				acceptClient();
			else if (_fds[i].revents & POLLIN)
				handleClient(_fds[i]);
		}
	}
}

void Server::sendMessage(std::string message, const int fd) {
	if (message.size() >= 2 &&  message[message.size() - 1] != '\n' && message[message.size() - 2] != '\r')
		message += "\r\n";
	if (message.size() > 512)
		message = message.substr(0, 510) + "\r\n";
	send(fd, message.c_str(), message.size(), MSG_DONTWAIT | MSG_NOSIGNAL);
	std::cout << C_OR << "fd " << fd << ":" << C_LIME " >> " << C_RESET << message.substr(0,message.size()-2) << std::endl;
}

void Server::broadcast(const std::vector<Client*>& clients, const std::string& msg, const Client& sender,
	const bool shouldSendToSender) {
	for (std::vector<Client*>::const_iterator it = clients.begin(); it != clients.end(); ++it)
		if ((*it)->getfd().fd != sender.getfd().fd)
			sendMessage(msg, (*it)->getfd().fd);
	if (shouldSendToSender)
		sendMessage(msg, sender.getfd().fd);
}

void Server::broadcast(const std::string& msg, const Client& sender, const bool shouldSendToSender) {
	for (std::vector<pollfd>::iterator it = _fds.begin(); it != _fds.end(); ++it) {
		if (it->fd != _socket && (it->fd != sender.getfd().fd))
			sendMessage(msg, it->fd);
	}
	if (shouldSendToSender)
		sendMessage(msg, sender.getfd().fd);
}

Client* Server::getClientWithNick(const std::string& nick) {
	for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
		if (it->second.getNick() == nick)
			return (&(it->second));
	}
 	return NULL;
}

Channel* Server::getChannelWithName(const std::string& name) {
	for (std::map<std::string, Channel>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
		if (it->first == name)
			return (&(it->second));
	}
	return NULL;
}

void Server::removeClient(const int fd)
{
	std::cout << C_ROUGE << "Client with fd " << fd << " disconnected" << C_RESET << std::endl;
	close(fd);
	_clients[fd].quitAllChannels();
	for (std::vector<pollfd>::iterator it = _fds.begin(); it != _fds.end(); ++it) {
		if (it->fd == fd) {
			_fds.erase(it);
			break ;
		}
	}
	_clients.erase(fd);
}

void Server::removeChannel(const std::string& name) {
	std::cout << "removing channel " << name << std::endl;
	if (_channels.find(name) != _channels.end() && _channels.find(name)->second.getClients().empty())
		_channels.erase(name);
}

void Server::acceptClient() {
	int fd = accept(_socket, __nullptr, __nullptr);
	if (fd < 0)
	{
		std::cerr << C_ROUGE << "Error: accept failed" << C_RESET << std::endl;
		return ;
	}
	_clients[fd] = Client(fd, "default", "default nick", this);
	_fds.push_back((pollfd){fd, POLL_IN, 0});
	std::cout << C_VERT << "Client connected with fd " << fd << C_RESET << std::endl;
}

void Server::handleClient(const pollfd &pollfd) {
	char buffer[1024] = {0};
	std::string total_buf;
	ssize_t bytes_read = recv(pollfd.fd, buffer, sizeof(buffer), MSG_DONTWAIT);
	Client &client = _clients[pollfd.fd];

	if (bytes_read > 0) {
		client.appendBuffer(buffer);
		total_buf = client.getBuffer();
		if (total_buf.size() > 2 && total_buf[total_buf.size() - 2] == '\r' && total_buf[total_buf.size() - 1] == '\n') {
			client.parseBuffer();
			client.setBuffer("");
		}
	}
	if (bytes_read == -1 || client.getFlags() & IS_RM)
		removeClient(pollfd.fd);
}

void Server::sigHandler(const int signal) {
	if (signal == SIGINT || signal == SIGQUIT)
		_sig = signal;
}

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

void Server::sendMessage(std::string msg, const Client& sender, const int to, const std::string& type) {
	std::string	message = ":" + sender.getNick() + "!" + sender.getUser() + "@localhost " + type + " " + msg + "\r\n";
	if (message.size() > 512)
		message = message.substr(0, 510) + "\r\n";
	send(to, msg.c_str(), msg.size(), MSG_DONTWAIT | MSG_NOSIGNAL);
}

void Server::broadcast(const std::string& msg) {
	for (std::vector<pollfd>::iterator it = _fds.begin(); it != _fds.end(); ++it) {
		if (it->fd != _socket)
			sendMessage(msg, _clients[it->fd], it->fd, "PRIVMSG");
	}
}

void Server::removeClient(const int fd)
{
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

	if (bytes_read > 0) {
		_clients[pollfd.fd].appendBuffer(buffer);
		total_buf = _clients[pollfd.fd].getBuffer();
		//std::cout << "Message to server: " << buffer << "  ";
		if (total_buf.size() > 2 && total_buf[total_buf.size() - 2] == '\r' && total_buf[total_buf.size() - 1] == '\n') {
			std::cout << "Message to server: " << _clients[pollfd.fd].getBuffer() ;
			_clients[pollfd.fd].parseBuffer(); //////////////////////////////////////////////////////////////////////////////////////////////////////////
			// respond to the message
			_clients[pollfd.fd].setBuffer("");
		}
	}
	else if (bytes_read == 0) {
		std::cout << C_ROUGE << "Client with fd " << pollfd.fd << " disconnected" << C_RESET << std::endl;
		removeClient(pollfd.fd);
	}
}


void Server::sigHandler(const int signal) {
	if (signal == SIGINT || signal == SIGQUIT)
		_sig = signal;
}

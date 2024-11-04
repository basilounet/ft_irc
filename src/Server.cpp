#include <Server.h>

int Server::_sig = 0;

Server::Server(const int port, const std::string& password) :
		_port(port),
		_password(password),
		_socket(-1),
		_addr(),
		_fds(),
		_clients(),
		_channels() {
}

Server::~Server() {
	for (std::vector<pollfd>::const_iterator it = _fds.begin(); it != _fds.end(); ++it) // NOLINT(*-use-auto, *-loop-convert)
		if (it->fd >= 0)
			close(it->fd);
}

Server::Server(const Server& src) :
		_port(),
		_password(),
		_socket(-1),
		_addr(),
		_fds(),
		_clients(),
		_channels() {
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
	_socket = socket(AF_INET, SOCK_STREAM, 0);
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
	_fds.push_back((pollfd){_socket, POLLIN, 0});
	std::cout << "\033[32mServer is running on port " << _port << "\033[0m" << std::endl;
}

void Server::runServer() {
	while (_sig == 0)
	{
		int pollCount = poll(_fds.data(), _fds.size(), 0);
		if (pollCount < 0)
			throw (std::runtime_error("\033[31mError: poll failed\033[0m"));
		for (size_t i = 0; i < _fds.size(); ++i)
		{
			if (_fds[i].fd == _socket && _fds[i].revents & POLLIN)
				acceptClient();
			else if (_fds[i].revents & POLLIN)
				handleClient(_fds[i], i);
		}
	}
}

void Server::acceptClient() {
	int fd = accept(_socket, __nullptr, __nullptr);
	if (fd < 0)
	{
		std::cerr << "\033[31mError: accept failed\033[0m" << std::endl;
		return ;
	}
	_clients[fd] = Client(fd);
	_fds.push_back((pollfd){fd, POLL_IN, 0});
	std::cout << "\033[32mClient connected with fd " << fd << "\033[0m" << std::endl;
}

void Server::handleClient(const pollfd &fd, const size_t i) {
	char buffer[512] = {0};
	ssize_t bytes_read = recv(fd.fd, buffer, sizeof(buffer), MSG_DONTWAIT);

	if (bytes_read > 0 && bytes_read < 512) {
		if (DEBUG)
			sendMessage(buffer, fd.fd);
		std::cout << "Message to server: " << buffer;

	}
	else if (bytes_read == 0) {
		std::cout << "\033[31mClient with fd " << fd.fd << " disconnected\033[0m" << std::endl;
		close(fd.fd);
		_fds.erase(_fds.begin() + i);
		_clients.erase(fd.fd);
	}
}

void Server::sendMessage(std::string msg, const int fd) {
	if (msg[msg.size() - 2] != '\r' && msg[msg.size() - 1] != '\n')
		msg += "\r\n";
	send(fd, msg.c_str(), msg.size(), MSG_DONTWAIT | MSG_NOSIGNAL);
}

void Server::sendMessage(const char* msg, const int fd) {
	std::string str(msg);
	sendMessage(str, fd);
}

void Server::sigHandler(const int signal) {
	if (signal == SIGINT || signal == SIGQUIT)
		_sig = signal;
}

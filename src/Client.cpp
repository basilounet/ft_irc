#include "Client.h"

Client::Client() {
	Client(-1);
}

Client::Client(const int fd, const std::string& name, const std::string& nick) :
	_nick(nick),
	_realName(name),
	_channels(),
	_fd((pollfd){fd, POLLIN, 0}) {
}

Client::~Client() {
}

Client::Client(const Client& src) : _realName(), _channels(),  _fd(src._fd){
	*this = src;
}

Client& Client::operator=(const Client& src) {
	if (this != &src) {
		_realName = src._realName;
		_channels = src._channels;
		_fd = src._fd;
	}
	return (*this);
}

pollfd Client::getfd() const {
	return (_fd);
}

std::string Client::getRealName() const {
	return (_realName);
}

std::string Client::getNick() const {
	return (_nick);
}


void Client::setRealName(const std::string& name) {
	_realName = name;
}

void Client::setNick(const std::string& name) {
	_nick = name;
}

std::ostream& operator<<(std::ostream& out, const Client& client) {
	out << "Client " << client.getRealName() << " with fd " << client.getfd().fd << " connected";
	return (out);
}

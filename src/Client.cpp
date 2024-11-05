#include "Client.h"

Client::Client() {
	Client(-1, "default", "default nick", __nullptr);
}

Client::Client(const int fd, const std::string& name, const std::string& nick, Server* server) :
	_server(server),
	_nick(nick),
	_realName(name),
	_fd((pollfd){fd, POLLIN, 0}) {
}

Client::~Client() {
}

Client::Client(const Client& src) {
	*this = src;
}

Client& Client::operator=(const Client& src) {
	if (this != &src) {
		_server = src._server;
		_nick = src._nick;
		_user = src._user;
		_realName = src._realName;
		_channels = src._channels;
		_fd = src._fd;
	}
	return (*this);
}

void Client::addChannel(Channel& channel) {
	_channels[channel.getName()] = &channel;
}

void Client::removeChannel(const std::string& name) {
	if (_channels.find(name) != _channels.end())
		_channels.erase(name);
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

std::string Client::getUser() const {
	return (_user);
}


void Client::setRealName(const std::string& name) {
	_realName = name;
}

void Client::setNick(const std::string& name) {
	_nick = name;
}

void Client::setUser(const std::string& name) {
	_user = name;
}


std::ostream& operator<<(std::ostream& out, const Client& client) {
	out << "Client " << client.getRealName() << " with fd " << client.getfd().fd << " connected";
	return (out);
}

#include "Client.h"

#include <sstream>

Client::Client() {
	*this = Client(-1, "default", "default nick", __nullptr);
}

Client::Client(const int fd, const std::string& name, const std::string& nick, Server* server) :
	_server(server),
	_nick(nick),
	_realName(name),
	_fd((pollfd){fd, POLLIN, 0}),
	_flags(HAS_REGISTERED){
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
		_buffer = src._buffer;
		_flags = src._flags;
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

void Client::quitAllChannels() {
	for(std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it)
		it->second->removeClient(*this);

}

void Client::broadcastToAllKnownUsers(const std::string& msg, const bool shouldSendToSender) {
	std::vector<int>	_alreadyBroadcasted;

	for (std::map<std::string, Channel*>::iterator itChannel = _channels.begin(); itChannel != _channels.end(); ++itChannel) {
		for (std::map<int, Client*>::const_iterator itClient = itChannel->second->getClients().begin(); itClient !=
		     itChannel->second->getClients().end(); ++itClient) {
			if ((itClient->first != _fd.fd || shouldSendToSender) && std::find(
				_alreadyBroadcasted.begin(), _alreadyBroadcasted.end(), itClient->first) == _alreadyBroadcasted.end()) {
				Server::sendMessage(msg, itClient->first);
				_alreadyBroadcasted.push_back(itClient->first);
			}
		}
	}
}

Server* Client::getServer() const {
	return (_server);
}

pollfd Client::getfd() const {
	return (_fd);
}

std::string Client::getRealName() const {
	return (_realName);
}

const std::map<std::string, Channel*>& Client::getChannels() const {
	return (_channels);
}

std::string Client::getNick() const {
	return (_nick);
}

std::string Client::getUser() const {
	return (_user);
}

std::string Client::getBuffer() const {
	return (_buffer);
}

short Client::getFlags() const {
	return (_flags);
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

void Client::setBuffer(const std::string& buf) {
	_buffer = buf;
}

void Client::setFlags(short flags) {
	_flags = flags;
}

void Client::appendBuffer(const std::string& buf) {
	_buffer += buf;
}

void Client::parseBuffer() {
	try {
		std::stringstream	storage(_buffer);
		std::string			str;
		while (std::getline(storage, str, '\n') && !str.empty()) {
			Message msg(this, str);
			msg.parseMsg();
			msg.execCommand();
		}
	} catch (std::exception& e) {
		std::cerr << C_ROUGE << "Message error :" << e.what() << C_RESET << std::endl;
	}
}

std::ostream& operator<<(std::ostream& out, const Client& client) {
	out << "Client " << client.getRealName() << " with fd " << client.getfd().fd << " connected";
	return (out);
}

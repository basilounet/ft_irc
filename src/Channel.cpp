#include "Channel.h"

Channel::Channel() :
		_server(__nullptr),
		_name("default") {
}

Channel::Channel(const std::string& name, Server* server) :
		_server(server),
		_name(name) {
}

Channel::~Channel() {
}

Channel::Channel(const Channel& src) : _name(src._name) {
	*this = src;
}

Channel& Channel::operator=(const Channel& src) {
	if (this != &src) {
		_server = src._server;
		_name = src._name;
		_clients = src._clients;
	}
	return (*this);
}


void Channel::broadcastMessage(const std::string& msg, const Client& sender) {
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
		if (it->first != sender.getfd().fd)
			Server::sendMessage(msg, sender, it->second->getfd().fd, "PRIVMSG " + _name + " :");
	}
}

void Channel::addClient(Client& client) {
	_clients[client.getfd().fd] = &client;
}

void Channel::removeClient(const Client& client) {
	if (_clients.find(client.getfd().fd) != _clients.end())
		_clients.erase(client.getfd().fd);
}

std::string Channel::getName() const {
	return (_name);
}

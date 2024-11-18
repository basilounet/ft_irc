#include "Channel.h"

Channel::Channel() :
		_server(NULL),
		_name("default"),
		_limit(0),
		_inviteOnly(false),
		_settableTopic(true){
}

Channel::Channel(const std::string& name, Server* server) :
		_server(server),
		_name(name),
		_limit(0),
		_inviteOnly(false),
		_settableTopic(true){
}

Channel::~Channel() {
}

Channel::Channel(const Channel& src) {
	*this = src;
}

Channel& Channel::operator=(const Channel& src) {
	if (this != &src) {
		_server = src._server;
		_name = src._name;
		_clients = src._clients;
		_chanops = src._chanops;
		_key = src._key;
		_limit = src._limit;
		_inviteOnly = src._inviteOnly;
		_settableTopic = src._settableTopic;
	}
	return (*this);
}


void Channel::broadcastMessage(const std::string& msg) {
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
			Server::sendMessage(msg, it->second->getfd().fd);
}

void Channel::broadcastMessage(const std::string& msg, const Client& sender) {
	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
		if (it->first != sender.getfd().fd)
			Server::sendMessage(msg, it->second->getfd().fd);
}

void Channel::addClient(std::string &nick) {
	Client* client = _server->getClientWithNick(nick);
	if (client == NULL) {
		// TODO si NULL >> 401   ERR_NOSUCHNICK				"<nickname> :No such nick/channel"
		return;
	}
	_clients[client->getfd().fd] = client;
	// TODO MESSAGE OK AJOUT ?
}

void Channel::addClient(Client& client) {
	_clients[client.getfd().fd] = &client;
}

void Channel::removeClient(std::string &nick) {
	Client* client = _server->getClientWithNick(nick);
	if (client == NULL)
		// TODO si NULL >> 401   ERR_NOSUCHNICK				"<nickname> :No such nick/channel"
		return;
	if (_clients.find(client->getfd().fd) != _clients.end()) {
		_clients.erase(client->getfd().fd);
		// TODO MESSAGE OK DE RETRAIT ?
		return;
	}

	// TODO PAS DANS LE CHANNEL ERR n?
}

void Channel::removeClient(const Client& client) {
	if (_clients.find(client.getfd().fd) != _clients.end())
		_clients.erase(client.getfd().fd);
}

std::string Channel::getName() const {
	return (_name);
}

bool Channel::isInChannel(const std::string& nick) const {
	(void)nick;
	for (std::map<int, Client*>::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
		if (it->second->getNick() == nick)
			return true;
	return false;
	return (true);
}

bool Channel::isChanop(const std::string nick) const {
	(void)nick;
	for (std::map<int, Client*>::const_iterator it = _chanops.begin(); it != _chanops.end(); ++it)
		if (it->second->getNick() == nick)
			return true;
	return false;
	return (true);
}

bool Channel::isKey() const {
	if (_key.empty())
		return false;
	return true;
}

std::string Channel::getKey() const {
	return _key;
}

bool Channel::access(const std::string &pwd) const {
	// TODO
	(void) pwd;
	return (true);
}

bool Channel::isLimit() const {
	if (_limit == 0)
		return (false);
	return (true);
}

int Channel::getLimit() const {
	return (_limit);
}

bool Channel::isFull() const {
	if ((int) _clients.size() >= _limit)
		return (true);
	return (false);
}

bool Channel::isInviteOnly() const {
	return (_inviteOnly);
}

bool Channel::isSettableTopic() const {
	return (_settableTopic);
}

void Channel::addChanop(std::string &nick) {
	// TODO
	(void) nick;
}

void Channel::removeChanop(std::string &nick) {
	// TODO
	(void) nick;
}

void Channel::setKey(std::string &key) {
	_key = key;
}

void Channel::setLimit(int limit) {
	_limit = limit;
}

void Channel::setInviteOnly(bool state) {
	_inviteOnly = state;
}

void Channel::setSettableTopic(bool state) {
	_settableTopic = state;
}

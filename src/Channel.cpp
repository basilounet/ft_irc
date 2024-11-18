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
		_invite = src._invite;
		_chanops = src._chanops;
		_key = src._key;
		_limit = src._limit;
		_inviteOnly = src._inviteOnly;
		_settableTopic = src._settableTopic;
	}
	return (*this);
}


void Channel::broadcastMessage(const std::string& msg) {
	for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
			Server::sendMessage(msg, (*it)->getfd().fd);
}

void Channel::broadcastMessage(const std::string& msg, const Client& sender, const bool shouldSendToSender) {
	for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
		if ((*it)->getfd().fd != sender.getfd().fd || shouldSendToSender)
			Server::sendMessage(msg, (*it)->getfd().fd);
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
	std::vector<Client*>::iterator it = std::find(_clients.begin(), _clients.end(), client);
	if (it != _clients.end()) {
		_clients.erase(it);
		// TODO MESSAGE OK DE RETRAIT ?
		return;
	}

	// TODO PAS DANS LE CHANNEL ERR n?
}

void Channel::removeClient(const Client& client) {
	std::vector<Client*>::iterator it = std::find(_clients.begin(), _clients.end(), &client);
	if (it != _clients.end()) {
		_clients.erase(it);
		// TODO MESSAGE OK DE RETRAIT ?
		return;
	}
}

std::string Channel::getName() const {
	return (_name);
}

const std::vector<Client *> &Channel::getClients() const {
	return (_clients);
}

bool Channel::isInChannel(const std::string& nick) const {
	for (std::vector<Client*>::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
		if ((*it)->getNick() == nick)
			return true;
	return false;
	return (true);
}

bool Channel::isChanop(const std::string nick) const {
	for (std::vector<Client*>::const_iterator it = _chanops.begin(); it != _chanops.end(); ++it)
		if ((*it)->getNick() == nick)
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

bool Channel::addChanop(std::string &nick) {
	if (!isChanop(nick)) {
		_chanops.push_back(_server->getClientWithNick(nick));
		return true;
	}
	return false;
}

bool Channel::removeChanop(std::string &nick) {
	for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
		if ((*it)->getNick() == nick) {
			_chanops.erase(it);
			return true;
		}
	}
	return false;
}

void Channel::setKey(std::string key) {
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

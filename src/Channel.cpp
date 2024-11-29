#include "Channel.h"

Channel::Channel() :
		_server(NULL),
		_name("default"),
		_inviteOnly(false),
		_topicProtected(true),
		_limit(0) {
}

Channel::Channel(const std::string& name, Server* server) :
		_server(server),
		_name(name),
		_inviteOnly(false),
		_topicProtected(true),
		_limit(0) {
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
		_invites = src._invites;
		_inviteOnly = src._inviteOnly;
		_topic = src._topic;
		_topicProtected = src._topicProtected;
		_key = src._key;
		_limit = src._limit;

	}
	return (*this);
}

void Channel::broadcastMessage(const std::string& msg) const {
	for (std::vector<Client*>::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
			Server::sendMessage(msg, (*it)->getfd().fd);
}

void Channel::broadcastMessage(const std::string& msg, const Client& sender, const bool shouldSendToSender) const {
	for (std::vector<Client*>::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
		if ((*it)->getfd().fd != sender.getfd().fd)
			Server::sendMessage(msg, (*it)->getfd().fd);
	if (shouldSendToSender)
		Server::sendMessage(msg, sender.getfd().fd);
}

Server* Channel::getServer() const {
	return (_server);
}

std::string Channel::getName() const {
	return (_name);
}

const std::vector<Client *> &Channel::getClients() const {
	return (_clients);
}
const std::vector<Client *> &Channel::getChanops() const {
	return (_chanops);
}

const std::vector<Client*> &Channel::getInvites() const
{
	return (_invites);
}

bool Channel::addClient(Client* client) {
	std::vector<Client*>::iterator it = std::find(_clients.begin(), _clients.end(), client);
	if (it != _clients.end())
		return false;
	_clients.push_back(client);
	return true;
}

bool Channel::addChanop(Client* client) {
	std::vector<Client*>::iterator it = std::find(_chanops.begin(), _chanops.end(), client);
	if (it != _chanops.end())
		return false;
	_chanops.push_back(client);
	return true;
}

bool Channel::addInvite(Client* client) {
	std::vector<Client*>::iterator it = std::find(_invites.begin(), _invites.end(), client);
	if (it != _invites.end())
		return false;
	_invites.push_back(client);
	return true;
}

bool Channel::removeClient(Client* client) {
	std::vector<Client*>::iterator it = std::find(_clients.begin(), _clients.end(), client);

	if (it != _clients.end()) {
		_clients.erase(it);
		if (_clients.empty())
		{
			_server->removeChannel(_name);
			return true;
		}
	}
	return false;
}

bool Channel::removeChanop(Client* client) {
	std::vector<Client*>::iterator it = std::find(_chanops.begin(), _chanops.end(), client);
	if (it != _chanops.end()) {
		_chanops.erase(it);
		return true;
	}
	return false;
}

bool Channel::removeInvite(Client* client) {
	std::vector<Client*>::iterator it = std::find(_invites.begin(), _invites.end(), client);
	if (it != _invites.end()) {
		_invites.erase(it);
		return true;
	}
	return false;
}

bool Channel::isClient(Client* client) const {
	for (std::vector<Client*>::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
		if ((*it) == client)
			return true;
	return false;
}

bool Channel::isChanop(Client* client) const {
	for (std::vector<Client*>::const_iterator it = _chanops.begin(); it != _chanops.end(); ++it)
		if ((*it) == client)
			return true;
	return false;
}

bool Channel::isInvite(Client* client) const {
	for (std::vector<Client*>::const_iterator it = _invites.begin(); it != _invites.end(); ++it)
		if ((*it) == client)
			return true;
	return false;
}

bool Channel::isInviteOnly() const {
	return (_inviteOnly);
}

bool Channel::setInviteOnly(bool state) {
	if (state != _inviteOnly) {
		_inviteOnly = state;
		return true;
	}
	return false;
}

std::string	Channel::getTopic() const {
	return _topic;
}

void Channel::setTopic(const std::string& str) {
	_topic = str;
}

bool Channel::isTopicProtected() const {
	return (_topicProtected);
}

bool Channel::setTopicProtected(bool state) {
	if (state != _topicProtected) {
		_topicProtected = state;
		return true;
	}
	return false;
}

std::string Channel::getKey() const {
	return _key;
}

void Channel::setKey(std::string key) {
	_key = key;
}

bool Channel::isKeyProtected() const {
	if (_key.empty())
		return (false);
	return (true);
}

bool Channel::access(const std::string &pwd) const {
	if (!isKeyProtected())
		return (true);
	if (_key == pwd)
		return (true);
	return (false);
}

int Channel::getLimit() const {
	return (_limit);
}

bool Channel::isLimit() const {
	if (_limit == 0)
		return (false);
	return (true);
}

void Channel::setLimit(int limit) {
	_limit = limit;
}

bool Channel::isFull() const {
	if (static_cast<int>(_clients.size()) >= _limit)
		return (true);
	return (false);
}

std::string	Channel::getFlagString(bool inChan) const {
	std::string flags;
	if (isInviteOnly() || isTopicProtected() || isKeyProtected() || isLimit()) {
		flags += "+";
		if (isTopicProtected())	flags += "t";
		if (isInviteOnly())		flags += "i";
		if (isLimit())			flags += "l";
		if (isKeyProtected())	flags += "k";
		if (inChan && isLimit())		flags += " " + to_string(getLimit());
		if (inChan && isKeyProtected())	flags += " " + getKey();
	}
	return flags;
}

const std::map<const Client *, Player>	&Channel::getGameBoard(void)	const		{ return (_gameBoard); }
Player									&Channel::getPlayer(const Client *client)	{ return _gameBoard[client]; }

void	Channel::addPlayer(const Client *toAdd) {
	if (_gameBoard.find(toAdd) == _gameBoard.end())
		_gameBoard[toAdd] = Player();
}

void	Channel::removePlayer(const Client *toRm) {
	if (_gameBoard.find(toRm) != _gameBoard.end())
		_gameBoard.erase(toRm);
}

void	Channel::addPoints(int toAdd) {
	for (std::map<const Client *, Player>::iterator it = _gameBoard.begin() ;
			it != _gameBoard.end() ; it++)
		it->second.gainPoints(toAdd);
}

void	Channel::removeNbImmunity(int toRemove) {
	for (std::map<const Client *, Player>::iterator it = _gameBoard.begin() ;
			it != _gameBoard.end() ; it++)
		it->second.addImmunity(-toRemove);
}

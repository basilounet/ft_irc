//
// Created by bvasseur on 11/15/24.
//

#include "Nick.h"
#include "Commands/Nick.h"

#include "Server.h"

Nick::Nick() {
}

Nick::Nick(Nick const& src) {
	*this = src;
}

Nick::~Nick() {
}

Nick& Nick::operator=(Nick const& other) {
	ACommand::operator=(other);
	return (*this);
}

void	Nick::process(const Message& msg)
{
	std::vector<std::string> params = msg.getParams();

	if ((msg.getClient()->getFlags() & HAS_TRY_PASS) == 0)
		throw (std::domain_error("The registration must be done in that order: PASS, NICK, USER"));
	if (params.empty() || params[0].empty()) {
		Server::sendMessage(ERR_NONICKNAMEGIVEN(msg.prefix(1), msg.getClient()->getNick()), msg.getClient()->getfd().fd);
		throw (std::invalid_argument("No nickname given"));
	}
	if (params[0].size() > 9)
		params[0] = params[0].substr(0, 9);
	if (params[0] == msg.getClient()->getNick())
		return;
	if (params[0].size() == 1 || Nick::hasInvalidCharacter(params[0])) {
		Server::sendMessage(ERR_ERRONEUSNICKNAME(msg.prefix(1),msg.getNick(), params[0]), msg.getClient()->getfd().fd);
		throw (std::invalid_argument("Invalid character in Nick"));
	}
	if (isNickInServer(params[0], msg))
		throw std::invalid_argument("Nick already in use");
	msg.getClient()->setNick(params[0]);
	if ((msg.getClient()->getFlags() & HAS_NICK) == 0)
		msg.getClient()->setFlags(msg.getClient()->getFlags() | HAS_NICK);
	if (msg.getClient()->getFlags() & HAS_REGISTERED)
		msg.getClient()->broadcastToAllKnownUsers(msg.prefix(2) + " NICK :" + msg.getClient()->getNick() + "\r\n", true);
}

bool	Nick::isNickInServer(const std::string& nick, const Message& msg) {
	for (std::map<int, Client>::iterator it = msg.getClient()->getServer()->getClients().begin(); it != msg.getClient()->getServer()->getClients().end(); ++it) {
		if (it->second.getfd().fd != msg.getClient()->getfd().fd && it->second.getNick() == nick && (it->second.getFlags() & HAS_REGISTERED)) {
			if ((msg.getClient()->getFlags() & HAS_REGISTERED) == 0) {
				Server::sendMessage(ERR_NICKCOLLISION(msg.prefix(2),msg.getNick(), nick, msg.getClient()->getRealName()), msg.getClient()->getfd().fd);
				return (true);
			}
			Server::sendMessage(ERR_NICKNAMEINUSE(msg.prefix(1),msg.getNick(), nick), msg.getClient()->getfd().fd);
			return (true);
		}
	}
	return (false);
}

bool Nick::hasInvalidCharacter(const std::string& str) {
	for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
		if (it == str.begin() && !std::isalpha(*it) && !isSpecialChar(*it))
			return true;
		if (!std::isalnum(*it) && !isSpecialChar(*it) && *it != '-')
			return (true);
	}
	return (false);
}

bool	Nick::isSpecialChar(const int ch) {
	if (ch == ';' || ch == '[' || ch == ']' || ch == '\\' || ch == '`' 
			|| ch == '_' || ch == '^' || ch == '{' || ch == '}' || ch == '|')
		return true;
	return false;
}

ACommand	*Nick::clone(void) const {
	return new Nick();
}

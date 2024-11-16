//
// Created by bvasseur on 11/15/24.
//

#include "Nick.h"

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

void	Nick::process(const Message& msg) {
	std::vector<std::string> params = msg.getParams();

	if (params.empty() || params[0].empty()) {
		Server::sendMessage(ERR_NONICKNAMEGIVEN(msg.getClient()->getNick()), msg.getClient()->getfd().fd);
		return ;
	}
	if (params[0].size() > 9)
		params[0] = params[0].substr(0, 9);
	if (params[0].size() == 1 || Nick::hasInvalidCharacter(params[0])) {
		Server::sendMessage(ERR_ERRONEUSNICKNAME(msg.getClient()->getNick(), params[0]), msg.getClient()->getfd().fd);
		return ;
	}
	for (std::map<int, Client>::iterator it = msg.getClient()->getServer()->getClients().begin(); it != msg.getClient()->getServer()->getClients().end(); ++it) {
		if (it->second.getNick() == params[0]) {
			Server::sendMessage(ERR_NICKNAMEINUSE(msg.getClient()->getNick(), params[0]), msg.getClient()->getfd().fd);
			return ;
		}
	}
	msg.getClient()->setNick(params[0]);
	if ((msg.getClient()->getFlags() & HAS_REGISTERED) == 0) {
		msg.getClient()->setFlags(msg.getClient()->getFlags() | HAS_REGISTERED);
	}
}


bool Nick::hasInvalidCharacter(const std::string& str) {
	for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
		if (!std::isalnum(*it) || *it != ';' || *it != '[' || *it != ']' || *it != '\\' || *it != '`' || *it != '_' || *
			it != '^' || *it != '{' || *it != '}' || *it != '|')
			return (true);
	}
	return (false);
}

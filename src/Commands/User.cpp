//
// Created by bvasseur on 11/15/24.
//

#include "User.h"

User::User() {
}

User::User(User const& src) {
	*this = src;
}

User::~User() {
}

User& User::operator=(User const& other) {
	ACommand::operator=(other);
	return (*this);
}

void	User::process(const Message& msg)
{
	const int	clientFlags = msg.getClient()->getFlags();
	const int	nbParams = msg.getParams().size();
	std::string	realName = msg.getTrailing();

	if (clientFlags & HAS_REGISTERED)
	{
		msg.getClient()->setFlags(clientFlags);
		Server::sendMessage(ERR_ALREADYREGISTRED(msg.prefix(1), msg.getNick()), msg.getFd());
		throw std::logic_error("USER: Unauthorized command (already registered)");
	}
	if ((clientFlags & HAS_NICK) == 0)
		throw (std::domain_error("The registration must be done in that order: PASS, NICK, USER"));
	if (nbParams < 3)
		needMoreParams(msg);
	if (realName.empty())
	{
		if (nbParams < 4)
			needMoreParams(msg);
		realName = msg.getParams()[3];
	}
	msg.getClient()->setUser(msg.getParams()[0]);
	msg.getClient()->setRealName(realName);
	msg.getClient()->tryRegistration();
}

void 	User::needMoreParams(const Message& msg) const
{
	Server::sendMessage(
		ERR_NEEDMOREPARAMS(msg.prefix(1), msg.getNick(), msg.getCommand())
		, msg.getFd());
	throw std::invalid_argument
		(msg.getCommand() + ":Not enough parameters");
}

ACommand	*User::clone(void) const {
	return new User();
}

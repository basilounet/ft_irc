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
		Server::sendMessage(ERR_ALREADYREGISTRED
				(msg.prefix(1), msg.getNick()), msg.getFd());
		throw std::logic_error("USER: Unauthorized command (already registered)");
	}
	if ((clientFlags & HAS_NICK) == 0)
		throw (std::domain_error
				("The registration must be done in that order: PASS, NICK, USER"));
	if (nbParams < 2 || (realName.empty() && nbParams < 3))
		needMoreParams(msg);
	if (realName.empty())
		realName = msg.getParams()[2];
	msg.getClient()->setUser(msg.getParams()[0]);
	msg.getClient()->setRealName(realName);
	tryRegistration(*msg.getClient(), msg);
}

void 	User::needMoreParams(const Message& msg) const
{
	Server::sendMessage(
		ERR_NEEDMOREPARAMS(msg.prefix(1), msg.getNick(), msg.getCommand())
		, msg.getFd());
	throw std::invalid_argument
		(msg.getCommand() + ":Not enough parameters");
}

void	User::tryRegistration(Client &client, const Message &msg)
{
	const std::string &server_passwd = client.getServer()->getPassword();

	if (!server_passwd.empty() && server_passwd != client.getPassword())
	{
		client.setFlags(0);
		throw std::logic_error("Bad password, retry registration process");
	}
	if (Nick::isNickInServer(client.getNick(), msg))
	{
		client.setFlags(0);
		throw std::invalid_argument
			("Nick already in use, retry registration process");
	}
	client.setFlags(client.getFlags() | HAS_REGISTERED);
	//send RPL_WELCOME
}

ACommand	*User::clone(void) const {
	return new User();
}

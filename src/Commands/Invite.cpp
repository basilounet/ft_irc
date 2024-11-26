//
// Created by bvasseur on 11/15/24.
//

#include "Invite.h"

Invite::Invite() {
}

Invite::Invite(Invite const& src) {
	*this = src;
}

Invite::~Invite() {
}

Invite& Invite::operator=(Invite const& other) {
	ACommand::operator=(other);
	return (*this);
}

// INVITE <Client> <#Channel>
void	Invite::process(const Message& msg) {
	if (msg.getParams().size() < 2) {
		// 403   ERR_NOSUCHCHANNEL			"<channel> :No such channel"
		Server::sendMessage(ERR_NOSUCHCHANNEL(msg.prefix(1), msg.getNick(), "ircserv"), msg.getFd());
		throw std::invalid_argument( "ircserv :No such channel");
	}
	Client* client = getClientWithNick(msg.getParams()[0], msg);	// throw if
	Channel* chan = getChannelWithName(msg.getParams()[1], msg);	// throw if
	invite(chan, client, msg);
}

// INVITE <Client> <#Channel>
void Invite::invite(Channel *chan, Client *client, const Message &msg) {
	if (chan->isInviteOnly())
		getChanopInChannel(msg.getNick(), chan, msg); // throw if
	else
		getClientInChannel(msg.getNick(), chan, msg); // throw if
	if (chan->isClient(client)) {
		// 443   ERR_USERONCHANNE			"<user> <channel> :is already on channel"
		Server::sendMessage(ERR_USERONCHANNE(msg.prefix(1), msg.getNick(), client->getNick(), chan->getName()), msg.getFd());
		throw std::invalid_argument(msg.getCommand() + " " + chan->getName() + " " + msg.getNick());
	}
	if (!chan->isInvite(client))
		chan->addInvite(client);
	// 341   RPL_INVITING				"<channel> <nick>"
	Server::sendMessage(RPL_INVITING(msg.prefix(1), msg.getNick(), chan->getName(), client->getNick()), msg.getFd());
	// INVITE			"INVITE <nick_invited> :<channel>"
	Server::sendMessage(INVITE(msg.prefix(2), client->getNick(), chan->getName()), client->getfd().fd);
}

ACommand	*Invite::clone(void) const {
	return new Invite();
}

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

void	Invite::process(const Message& msg) {
	isMsgParamEmpty(msg); // throw if >= 2
	// getVectorInviteMessage TODO
	invite(msg);
}

// INVITE Client #Channel
void Invite::invite(const Message &msg) {
	Client* client = getClientWithNick(msg.getParams()[0], msg);	// throw if
	Channel* chan = getChannelWithName(msg.getParams()[1], msg);	// throw if
	getChanopInChannel(msg.getNick(), chan, msg);					// throw if
	if (chan->isClient(client)) {
		// 443   ERR_USERONCHANNE			"<user> <channel> :is already on channel"
		Server::sendMessage(ERR_USERONCHANNE(msg.prefix(1), msg.getNick(), client->getNick(), chan->getName()), msg.getFd());
		throw std::invalid_argument(msg.getCommand() + " " + chan->getName() + " " + msg.getNick());
	}
	chan->setInviteOnly(true);
	// 341   RPL_INVITING				"<channel> <nick>"
	Server::sendMessage(RPL_INVITING(msg.prefix(2), msg.getNick(), chan->getName(), client->getNick()), msg.getFd());
	throw std::invalid_argument(msg.getCommand() + " " + msg.getNick() + " " + msg.getNick());
}

ACommand	*Invite::clone(void) const {
	return new Invite();
}

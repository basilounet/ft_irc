//
// Created by bvasseur on 11/15/24.
//

#include "Mode.h"
#include <cstdlib>
//#include <stdlib.h>

Mode::Mode() {
}

Mode::Mode(Mode const& src) {
	*this = src;
}

Mode::~Mode() {
}

Mode& Mode::operator=(Mode const& other) {
	ACommand::operator=(other);
	return (*this);
}

void	Mode::process(const Message& msg) {
	if (msg.getParams().empty())
		Server::sendMessage(ERR_NEEDMOREPARAMS(msg.prefix(1), msg.getNick(), msg.getCommand()), msg.getFd());
	else if (msg.getParams()[0][0] == '#' || msg.getParams()[0][0] == '&') {
		Channel* chan = msg.getClient()->getServer()->getChannelWithName(msg.getParams()[0]);
		if (chan) {
			if (!chan->isInChannel(msg.getNick()))
				Server::sendMessage(ERR_NOTONCHANNEL(msg.prefix(1), msg.getNick(), chan->getName()), msg.getFd());
			else if (!chan->isChanop(msg.getNick()))
				Server::sendMessage(ERR_CHANOPRIVSNEEDED(msg.prefix(1), chan->getName(), chan->getName()), msg.getFd());
			else
				channelMode(chan, msg);
		}
		else
			Server::sendMessage(ERR_NOSUCHCHANNEL(msg.prefix(1), msg.getNick(), chan->getName()), msg.getFd());
	}
	else {
		userMode(msg);
	}
}

// CHANNEL MODE
// MODE <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>][<ban mask>]
void	Mode::channelMode(Channel* chan, const Message& msg) {
	if (msg.getParams()[1][0] != '+' && msg.getParams()[1][0] != '-')
		Server::sendMessage(ERR_NEEDMOREPARAMS(msg.prefix(1), msg.getNick(), msg.getCommand()), msg.getFd());
	else if (msg.getParams()[1] == "-i")
		setChannelInviteOnly(chan, msg, false);
	else if (msg.getParams()[1] == "+i")
		setChannelInviteOnly(chan, msg, true);
	else if (msg.getParams()[1] == "-t")
		setChannelSettableTopic(chan, msg, false);
	else if (msg.getParams()[1] == "+t")
		setChannelSettableTopic(chan, msg, true);
	else if (msg.getParams()[1] == "-k")
		setChannelKey(chan, msg, false);
	else if (msg.getParams()[1] == "+k")
		setChannelKey(chan, msg, true);
	else if (msg.getParams()[1] == "-o")
		setChannelOperatorPrivilege(chan, msg, false);
	else if (msg.getParams()[1] == "+o")
		setChannelOperatorPrivilege(chan, msg, true);
	else if (msg.getParams()[1] == "-l")
		setChannelLimit(chan, msg, false);
	else if (msg.getParams()[1] == "+l")
		setChannelLimit(chan, msg, true);
	else
		Server::sendMessage(ERR_UNKNOWNMODE(msg.prefix(1), msg.getNick(), msg.getParams()[1], msg.getParams()[0]), msg.getFd());
}

// i - toggle the invite-only channel flag
// When the channel flag 'i' is set, new members are only accepted if
// their mask matches Invite-list (See section 4.3.2) or they have been
// invited by a channel operator.  This flag also restricts the usage of
// the INVITE command (See "IRC Client Protocol" [IRC-CLIENT]) to
// channel operators.
void	Mode::setChannelInviteOnly(Channel* chan, const Message& msg, bool add) {
	chan->setInviteOnly(add);
	RPL_CHANNELMODEIS(msg.prefix(2), msg.getNick(), msg.getParams()[0], msg.getParams()[1], "");
}

// t - toggle the topic settable by channel operator only flag
// used to restrict the usage of the TOPIC command to channel operators.
void	Mode::setChannelSettableTopic(Channel* chan, const Message& msg, bool add) {
	chan->setSettableTopic(add);
	RPL_CHANNELMODEIS(msg.prefix(2), msg.getNick(), msg.getParams()[0], msg.getParams()[1], "");
}

// k - set/remove the channel key (password)
// When a channel key is set (by using the mode 'k'), servers MUST
// reject their local users request to join the channel unless this key
// is given.
// The channel key MUST only be made visible to the channel members in
// the reply sent by the server to a MODE query.
void	Mode::setChannelKey(Channel* chan, const Message& msg, bool add) {
	// TODO
	(void) chan;
	(void) msg;
	(void) add;
}

// o - give/take channel operator privilege
void	Mode::setChannelOperatorPrivilege(Channel* chan, const Message& msg, bool add) {
	// TODO
	(void) chan;
	(void) msg;
	(void) add;
}

// l - set/remove the user limit to channel
// When the limit is reached, servers MUST forbid their local users to
// join the channel.
// The value of the limit MUST only be made available to the channel
// members in the reply sent by the server to a MODE query.
void	Mode::setChannelLimit(Channel* chan, const Message& msg, bool add) {
	if (add) {
		if (msg.getParams().size() < 3){
			Server::sendMessage(ERR_NEEDMOREPARAMS(msg.prefix(1), msg.getNick(), msg.getCommand()), msg.getFd());
			return ;
		}
		int limit = atoi(msg.getParams()[2].c_str());
		if (limit == 0) {
			Server::sendMessage(ERR_NEEDMOREPARAMS(msg.prefix(1), msg.getNick(), msg.getCommand()), msg.getFd());
			return ;
		}
		chan->setLimit(limit);
		RPL_CHANNELMODEIS(msg.prefix(2), msg.getNick(), msg.getParams()[0], msg.getParams()[1], msg.getParams()[2]);
	}
}

// USER MODE
// MODE <nickname> {[+|-]|i|w|o|O|r}
void	Mode::userMode(const Message& msg) {
	// TODO
	(void) msg;
}










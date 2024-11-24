//
// Created by bvasseur on 11/15/24.
//

#include "Mode.h"
#include <cstdlib>

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
	checkNbParam(msg, 1); // throw if
	Channel* chan = getChannelWithName(msg.getParams()[0], msg); // throw if
	getChanopInChannel(msg.getClient()->getNick(), chan, msg);		// throw if
	// vector flags
	channelMode(chan, msg); // throw if
}

// CHANNEL MODE
// MODE <channel> {[+|-]|i|t|k|o|l} [<limit>] [<user>]
void	Mode::channelMode(Channel* chan, const Message& msg) {
	if (msg.getParams().size() < 2) {
		sendChannelMode(chan, msg);
		return;
	}
	if (msg.getParams()[1] == "-i")
		setChannelInviteOnly(chan, msg, false);
	else if (msg.getParams()[1] == "+i")
		setChannelInviteOnly(chan, msg, true);
	else if (msg.getParams()[1] == "-t")
		setChannelTopicProtected(chan, msg, false);
	else if (msg.getParams()[1] == "+t")
		setChannelTopicProtected(chan, msg, true);
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
	else {
		//472	ERR_UNKNOWNMODE			"<char> :is unknown mode char to me for <channel>"
		Server::sendMessage(ERR_UNKNOWNMODE(msg.prefix(1), msg.getNick(), msg.getParams()[1], chan->getName()), msg.getFd());
		throw std::invalid_argument(msg.getParams()[1] + " :is unknown mode char to me for " + chan->getName());
	}
}

void	Mode::sendChannelMode(Channel* chan, const Message& msg) {
	std::string flags;
	if (chan->isInviteOnly() || chan->isTopicProtected() || chan->isKeyProtected() || chan->isLimit()) {
		flags += "+";
		if (chan->isTopicProtected())	flags += "t";
		if (chan->isInviteOnly())		flags += "i";
		if (chan->isLimit())			flags += "l";
		if (chan->isKeyProtected())		flags += "k";
		if (chan->isLimit())			flags += " " + to_string(chan->getLimit());
		if (chan->isKeyProtected())		flags += " " + chan->getName();
	}
	// 324   RPL_CHANNELMODEIS	"<channel> <mode> <mode params>"
	Server::sendMessage(RPL_CHANNELMODEIS(msg.prefix(1), msg.getNick(), msg.getParams()[0], flags, ""), msg.getFd());
}

// :a_!~a___@rtr.23.90.210.20.unyc.it MODE #benos +i
// i - toggle the invite-only channel flag
void	Mode::setChannelInviteOnly(Channel* chan, const Message& msg, bool add) {
	chan->setInviteOnly(add);
// MODE RPL_CLIENT_MODE					"MODE <channel> <arg>"
	chan->broadcastMessage(RPL_CLIENT_MODE(msg.prefix(2), msg.getParams()[0], msg.getParams()[1]));
}

// t - toggle the topic protected channel flag
void	Mode::setChannelTopicProtected(Channel* chan, const Message& msg, bool add) {
	chan->setTopicProtected(add);
// MODE RPL_CLIENT_MODE					"MODE <channel> <arg>"
	chan->broadcastMessage(RPL_CLIENT_MODE(msg.prefix(2), msg.getParams()[0], msg.getParams()[1]));
}

// k - set/remove the channel key (password)
void	Mode::setChannelKey(Channel* chan, const Message& msg, bool add) {
	if (add) {
		if (msg.getParams().size() < 3 || msg.getParams()[2].empty())
			return ;
		chan->setKey(msg.getParams()[2]);
	} else {
		if (chan->getKey().empty())
			return;
		chan->setKey("");
	}
	// MODE RPL_CLIENT_MODE					"MODE <channel> <arg>"
	chan->broadcastMessage(RPL_CLIENT_MODE(msg.prefix(2), msg.getParams()[0], msg.getParams()[1]));
}

/*
442 nop >> :efnet.deic.eu 441 a_ c_ #benos :They aren't on that channel
>> :ben!Benjamin@localhost MODE ben #benos to to
>> :a_!~a___@rtr.23.90.210.20.unyc.it MODE #benos +o b_
*/

// o - give/take channel operator privilege
void	Mode::setChannelOperatorPrivilege(Channel* chan, const Message& msg, bool add) {
	if (msg.getParams().size() < 3 || msg.getParams()[2].empty())
		return ;
	Client* client = getClientInChannel441(msg.getParams()[2], chan, msg); // throw if
	if (add)
		chan->addChanop(client);
	else
		chan->removeChanop(client);
	// MODE	RPL_MODE	"MODE <channel> <arg> <nick>"
	chan->broadcastMessage(RPL_MODE(msg.prefix(2), msg.getNick(), chan->getName(), msg.getParams()[2], client->getNick()));
}

// l - set/remove the user limit to channel
void	Mode::setChannelLimit(Channel* chan, const Message& msg, bool add) {
	int limit = 0;
	if (add) {
		if (msg.getParams().size() >= 3)
			limit = atoi(msg.getParams()[2].c_str());
		// if (limit == 0) {
		// 	//461   ERR_NEEDMOREPARAMS	"<command> :Not enough parameters"
		// 	Server::sendMessage(ERR_NEEDMOREPARAMS(msg.prefix(1), msg.getNick(), msg.getCommand()), msg.getFd());
		// 	throw std::invalid_argument(msg.getCommand() + ":Not enough parameters");
		// }
	}
	chan->setLimit(limit);
	// MODE RPL_CLIENT_MODE					"MODE <channel> <arg>"
	chan->broadcastMessage(RPL_CLIENT_MODE(msg.prefix(2), msg.getParams()[0], msg.getParams()[1] + " " + to_string(limit)));
}

ACommand	*Mode::clone(void) const {
	return new Mode();
}

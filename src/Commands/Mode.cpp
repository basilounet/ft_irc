//
// Created by bvasseur on 11/15/24.
//

#include "Mode.h"

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
	if (msg.getCommand() != "MODE")
		return; // throw command fail
	if (msg.getParams().empty()) {
		std::string msgError = ERR_NEEDMOREPARAMS(msg.prefix(1), msg.getNick(), msg.getCommand());
		Server::sendMessage(msgError, msg.getClient()->getfd().fd);
	}
	if (msg.getParams()[0][0] == '#' || msg.getParams()[0][0] == '&')
		channelMode(msg);
	else
		userMode(msg);
}

// CHANNEL MODE
// MODE <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>][<ban mask>]
void	Mode::channelMode(const Message& msg) {
	if (msg.getParams()[1] == "-i")
		setChannelInviteOnly(msg, false);
	else if (msg.getParams()[1] == "+i")
		setChannelInviteOnly(msg, true);
	else if (msg.getParams()[1] == "-t")
		setChannelSettableTopic(msg, false);
	else if (msg.getParams()[1] == "+t")
		setChannelSettableTopic(msg, true);
	else if (msg.getParams()[1] == "-k")
		setChannelKey(msg, false);
	else if (msg.getParams()[1] == "+k")
		setChannelKey(msg, true);
	else if (msg.getParams()[1] == "-o")
		setChannelOperatorPrivilege(msg, false);
	else if (msg.getParams()[1] == "+o")
		setChannelOperatorPrivilege(msg, true);
	else if (msg.getParams()[1] == "-l")
		setChannelLimit(msg, false);
	else if (msg.getParams()[1] == "+l")
		setChannelLimit(msg, true);
	else
		return ; //throw nomode
}

// i - toggle the invite-only channel flag
void	Mode::setChannelInviteOnly(const Message& msg, bool add) {
	(void) msg;
	if (add) {

	}else {

	}
}

// t - toggle the topic settable by channel operator only flag
void	Mode::setChannelSettableTopic(const Message& msg, bool add) {
	(void) msg;
	if (add) {

	}else {

	}
}

// set/remove the channel key (password)
void	Mode::setChannelKey(const Message& msg, bool add) {
	(void) msg;
	if (add) {

	}else {

	}
}

// o - give/take channel operator privilege
void	Mode::setChannelOperatorPrivilege(const Message& msg, bool add) {
	(void) msg;
	if (add) {

	}else {

	}
}

// set/remove the user limit to channel
void	Mode::setChannelLimit(const Message& msg, bool add) {
	(void) msg;
	if (add) {

	}else {

	}
}

// USER MODE
// MODE <nickname> {[+|-]|i|w|o|O|r}
void	Mode::userMode(const Message& msg) {
	(void) msg;

}










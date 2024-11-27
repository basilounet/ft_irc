//
// Created by bvasseur on 11/15/24.
//

#include "Kick.h"

Kick::Kick() {
}

Kick::Kick(Kick const& src) {
	*this = src;
}

Kick::~Kick() {
}

Kick& Kick::operator=(Kick const& other) {
	ACommand::operator=(other);
	if (this != &other) {
        _channels = other._channels;
        _users = other._users;
        _reason = other._reason;
    }
	return (*this);
}

void	Kick::process(const Message& msg) {
	checkNbParam(msg, 2);

	_channels = split(msg.getParams()[0], ',', msg);
	_users = split(msg.getParams()[1], ',', msg);
	if (_channels.size() > 1 && _users.size() != _channels.size()) {
		Server::sendMessage(ERR_NEEDMOREPARAMS(msg.prefix(1), msg.getNick(), "KICK"), msg.getFd());
		throw std::invalid_argument("Incorrect number of users for the number of channels");
	}
	if (_channels.size() == 1)
		oneChannel(msg);
    else
		multipleChannels(msg);
}

void Kick::oneChannel(const Message& msg) {
	Channel* chan = getChannelWithName(_channels[0], msg);
	getClientInChannel(msg.getNick(), chan, msg);
	getChanopInChannel(msg.getNick(), chan, msg);
	for (size_t i = 0; i < _users.size(); ++i) {
        try {
			Client* user = getClientInChannel441(_users[i], chan, msg);
			_reason = msg.getTrailing();
			if (_reason.empty())
				_reason = user->getNick();
			chan->broadcastMessage(msg.prefix(2) + "KICK " + chan->getName() + " " + user->getNick() + " :" + _reason + CRLF);
			user->removeChannel(chan->getName());
			if (chan->removeClient(user))
				return ;
            chan->removeChanop(user);
		}
		catch (std::exception &e) {
			std::cout << C_ROSE << "Error KICK: " << e.what() << C_RESET << std::endl;
		}
	}
}

void Kick::multipleChannels(const Message& msg) {
	for (size_t i = 0; i < _channels.size(); ++i) {
        try {
			Channel* chan = getChannelWithName(_channels[i], msg);
			getClientInChannel(msg.getNick(), chan, msg);
			getChanopInChannel(msg.getNick(), chan, msg);
            Client* user = getClientInChannel441(_users[i], chan, msg);
			_reason = msg.getTrailing();
			if (_reason.empty())
				_reason = user->getNick();
            chan->broadcastMessage(msg.prefix(2) + "KICK " + chan->getName() + " " + user->getNick() + " :" + _reason + CRLF);
            user->removeChannel(chan->getName());
            if (chan->removeClient(user))
				continue ;
            chan->removeChanop(user);
        }
        catch (std::exception &e) {
            std::cout << C_ROSE << "Error KICK: " << e.what() << C_RESET << std::endl;
        }
    }
}

ACommand	*Kick::clone(void) const {
	return new Kick();
}

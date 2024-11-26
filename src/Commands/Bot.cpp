//
// Created by bvasseur on 11/26/24.
//

#include "Bot.h"

Bot::Bot() {
}

Bot::Bot(Bot const& src) {
	*this = src;
}

Bot::~Bot() {
}

Bot& Bot::operator=(Bot const& other) {
	ACommand::operator=(other);
	if (this != &other) {
	}
	return (*this);
}

void	Bot::process(const Message& msg) {
	checkNbParam(msg, 1);

	if (msg.getParams()[0] == "rr" || msg.getParams()[0] == "russianRoulette")
		russianRoulette(msg);
}

/**
 * /BOT "rr"|"russianRoulette" #channel [<user> *("," <user>)]
 */
void	Bot::russianRoulette(const Message& msg) {
	checkNbParam(msg, 2);

	Channel* chan = getChannelWithName(msg.getParams()[1], msg);

	if (msg.getParams().size() >= 3) {
		_usersNames = split(msg.getParams()[2], ',', msg);
		for (size_t i = 0; i < _usersNames.size(); ++i) {
			try {
				Client* user = getClientInChannel441(_usersNames[i], chan, msg);
				_users.push_back(user);
			}
			catch (std::exception &e) {
				std::cout << C_ROSE << "Error russianRoulette unknown player: " << e.what() << C_RESET << std::endl;
			}
		}
	}
	else
		_users = chan->getClients();
	size_t index = rand() % _users.size();
	if (chan->isChanop(_users[index]) && !chan->isChanop(msg.getClient())) {
		chan->addChanop(msg.getClient());
		chan->broadcastMessage(msg.prefix(2) + "MODE " + chan->getName() + " +o " + msg.getNick() + CRLF);
	}
	chan->broadcastMessage(msg.prefix(2) + "KICK " + chan->getName() + " " + _users[index]->getNick() + " :lost to Russian Roulette" + CRLF);
	_users[index]->removeChannel(chan->getName());
	chan->removeChanop(_users[index]);
	chan->removeClient(_users[index]);
}

ACommand	*Bot::clone(void) const {
	return (new Bot());
}

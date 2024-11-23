//
// Created by bvasseur on 11/15/24.
//

#include "Part.h"

#include "Channel.h"

Part::Part() {
}

Part::Part(Part const& src) {
	*this = src;
}

Part::~Part() {
}

Part& Part::operator=(Part const& other) {
	ACommand::operator=(other);
	return (*this);
}

void	Part::process(const Message& msg) {
	std::vector<std::string> params = msg.getParams();
	std::vector<std::string> channels;

	checkNbParam(msg, 1);
	channels = split(params[0], ',');
	for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); ++it) {
		try {
			Channel *chan = msg.getClient()->getServer()->getChannelWithName(*it);
			if (chan == NULL) {
				Server::sendMessage(ERR_NOSUCHCHANNEL(msg.prefix(1), msg.getNick(), *it), msg.getFd());
				throw std::invalid_argument("Channel not found");
			}
			if (!chan->isClient(msg.getClient())) {
				Server::sendMessage(ERR_NOTONCHANNEL(msg.prefix(1), msg.getNick(), *it), msg.getFd());
				throw std::invalid_argument("Not on Channel");
			}
			std::string reason = " :Leaving";
			if (msg.getMsg().find(' ', msg.getMsg().find('#')) != std::string::npos)
				reason = " " + msg.getMsg().substr(msg.getMsg().find(' ', msg.getMsg().find('#')) + 1);
			chan->broadcastMessage(msg.prefix(2) + "PART" + " " + *it + reason);
			chan->removeClient(msg.getClient());
		}
		catch (std::exception &e) {
			std::cout << C_ROSE << "Error part: " << e.what() << C_RESET << std::endl;
		}
	}
}

ACommand	*Part::clone(void) const {
	return new Part();
}

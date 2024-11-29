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
	channels = split(params[0], ',', msg);
	for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); ++it) {
		try {
			Channel *chan = getChannelWithName(*it, msg);
			getClientInChannel(msg.getNick(), chan, msg);
			std::string reason = "Leaving";
			if (!msg.getTrailing().empty())
				reason = msg.getTrailing();
			chan->broadcastMessage(msg.prefix(2) + "PART" + " " + *it + " :" + reason);
			msg.getClient()->removeChannel(chan->getName());
			chan->removeChanop(msg.getClient());
			chan->removePlayer(msg.getClient());
			chan->removeClient(msg.getClient());
		}
		catch (std::exception &e) {
			std::cout << C_ROUGE << "Error part: " << e.what() << C_RESET << std::endl;
		}
	}
}

ACommand	*Part::clone(void) const {
	return new Part();
}

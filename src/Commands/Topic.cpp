//
// Created by bvasseur on 11/15/24.
//

#include "Topic.h"

Topic::Topic() {
}

Topic::Topic(Topic const& src) {
	*this = src;
}

Topic::~Topic() {
}

Topic& Topic::operator=(Topic const& other) {
	ACommand::operator=(other);
	return (*this);
}

void	Topic::process(const Message& msg) {
	// TODO
	// isMsgParamEmpty(msg); // throw if
	// if(!msg.getTrailing().empty())
	// 	msg.getParams().push_back(msg.getTrailing());
	//
	// if (msg.getParams().size() == 1 || msg.getParams()[0].empty()) {
	// 	// 461   ERR_NEEDMOREPARAMS			"<command> :Not enough parameters"
	// 	Server::sendMessage(ERR_NEEDMOREPARAMS(msg.prefix(1), msg.getNick(), msg.getCommand()), msg.getFd());
	// 	throw std::invalid_argument(msg.getCommand() + ":Not enough parameters");
	// }
	// getVectorTopicMessage
	topic(msg);
}

// TOPIC #channel :subject
void Topic::topic(const Message &msg) {
	// TODO
	Channel* chan = getChannelWithName(msg.getParams()[1], msg);	// throw if
	// getChanopInChannel(msg.getNick(), chan, msg);					// throw if
	chan->setTopic(msg.getTrailing());
	// 341   RPL_INVITING				"<channel> <nick>"
	// Server::sendMessage(RPL_INVITING(msg.prefix(2), msg.getNick(), chan->getName(), client->getNick()), msg.getFd());
	// throw std::invalid_argument(msg.getCommand() + " " + msg.getNick() + " " + msg.getNick());
}

ACommand	*Topic::clone(void) const {
	return new Topic();
}

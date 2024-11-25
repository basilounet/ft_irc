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

void Topic::process(const Message& msg) {
	// checkNbParam(msg, 1); // throw if
	if (msg.getParams().size() == 0) {
		// 403   ERR_NOSUCHCHANNEL			"<channel> :No such channel"
		Server::sendMessage(ERR_NOSUCHCHANNEL(msg.prefix(1), msg.getNick(), "ircserv"), msg.getFd());
		throw std::invalid_argument( "ircserv :No such channel");
	}
	Channel* chan = getChannelWithName(msg.getParams()[0], msg);	// throw if
	// getVectorTopicMessage
	topic(chan, msg);
}

// TOPIC #channel :subject
void Topic::topic(Channel *chan, const Message &msg) {
	if (msg.getTrailing().empty()) {
		if (chan->getTopic().empty()) {
			// 331   RPL_NOTOPIC				"<channel> :No topic is set"
			Server::sendMessage(RPL_NOTOPIC(msg.prefix(1), msg.getNick(), chan->getName()), msg.getFd());
			return;
		}
		// 332   RPL_TOPIC					"<channel> :<topic>"
		Server::sendMessage(RPL_TOPIC(msg.prefix(1), msg.getNick(), chan->getName(), chan->getTopic()), msg.getFd());
		return;
	}
	getClientInChannel(msg.getNick(), chan, msg);					// throw if
	if (!chan->isTopicProtected())
		getChanopInChannel(msg.getNick(), chan, msg);				// throw if
	//topicStr = msg.getMsg().substr(msg.getMsg().find(':') + 1);
	chan->setTopic( msg.getTrailing());
	chan->broadcastMessage(TOPIC(msg.prefix(2), chan->getName(), msg.getTrailing()));
}

ACommand	*Topic::clone(void) const {
	return new Topic();
}

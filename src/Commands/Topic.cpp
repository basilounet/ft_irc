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
	isMsgParamEmpty(msg); // throw if (nb >= 1) TODO
	// getVectorTopicMessage TODO
	topic(msg);
}

// TOPIC #channel :subject
void Topic::topic(const Message &msg) {
	Channel* chan = getChannelWithName(msg.getParams()[0], msg); // throw if
	// -t ALL ou +t chanops
	if (!chan->isTopicProtected())
		getChanopInChannel(msg.getNick(), chan, msg); // throw if

	if ((msg.getMsg().size() == 1) && msg.getTrailing().empty()) {
		chan->setTopic("");
		// 331   RPL_NOTOPIC				"<channel> :No topic is set"
		Server::sendMessage(RPL_NOTOPIC(msg.prefix(2), msg.getNick(), chan->getName()), msg.getFd());
		throw std::invalid_argument(chan->getName() + " :No topic is set");
	}

	std::string topicStr;
	topicStr = msg.getMsg().substr(msg.getMsg().find(' ', msg.getMsg().find('#')) + 1);
	chan->setTopic(topicStr);
	// 332   RPL_TOPIC					"<channel> :<topic>"
	// define RPL_TOPIC(prefix, nickRes, channel, topic)
	Server::sendMessage(RPL_TOPIC(msg.prefix(2), msg.getNick(), chan->getName(), topicStr), msg.getFd());
	throw std::invalid_argument(chan->getName() + " :" + topicStr);
}

ACommand	*Topic::clone(void) const {
	return new Topic();
}

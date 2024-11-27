//
// Created by bvasseur on 11/15/24.
//

#include "Join.h"

#include <stdexcept>
#include <vector>
#include "IRC_responses.h"

Join::Join() {
}

Join::Join(Join const& src) {
	*this = src;
}

Join::~Join() {
}

Join& Join::operator=(Join const& other) {
	ACommand::operator=(other);
	if (this != &other) {
		_channels = other._channels;
		_pswds = other._pswds;
	}
	return (*this);
}

void	Join::process(const Message& msg) {
	checkNbParam(msg, 1);
	if (msg.getParams()[0] == "0")
	{
		quitAllChannels(msg);
		return ;
	}
	_channels = split(msg.getParams()[0], ',', msg);
	if (msg.getParams().size() > 1)
		_pswds = split(msg.getParams()[1], ',', msg);
	for (size_t i = 0 ; i < _channels.size(); ++i) {
		try {
			std::cout << "Looking to join channel " << _channels[i] << std::endl;
			if (msg.getClient()->getServer()->getChannelWithName(_channels[i]) != NULL)
				tryJoinExistingChannel(msg, i);
			else
				CreateChannel(msg, i);
		}
		catch (std::exception &e) {
			std::cout << C_ROSE << "Error join: " << e.what() << C_RESET << std::endl;
		}
	}
}

ACommand	*Join::clone(void) const {
	return new Join();
}

// chanstring =  %x01-07 / %x08-09 / %x0B-0C / %x0E-1F / %x21-2B
// chanstring =/ %x2D-39 / %x3B-FF
bool Join::isNameValid(const std::string& name) const {
	if (name.empty() || (name[0] != '#' && name[0] != '&') || name.size() < 2)
		return (false);
	for (std::string::const_iterator it = name.begin(); it != name.end(); ++it) {
		if (*it < 0x01 || (*it > 0x07 && *it < 0x08) || (*it > 0x09 && *it < 0x0B) || (*it > 0x0C && *it < 0x0E) || (*it
			> 0x1F && *it < 0x21) || (*it > 0x2B && *it < 0x2D) || (*it > 0x39 && *it < 0x3B))
			return (false);
	}
	return (true);
}

void Join::quitAllChannels(const Message& msg) {
	std::map<std::string, Channel*> channels = msg.getClient()->getChannels();

	for (std::map<std::string, Channel*>::iterator it = channels.begin(); it != channels.end(); ++it) {
		try {
			Message msgPart(msg.getClient(), "PART " + it->first + CRLF);
			msgPart.execCommand();
		}
		catch (std::exception &e) {
			std::cout << C_ROSE << "Error part: " + it->first << e.what() << C_RESET << std::endl;
		}
	}
}

void Join::tryJoinExistingChannel(const Message& msg, size_t i) {
	std::cout << "Trying to join existing channel" << std::endl;
	Channel* chan = getChannelWithName(_channels[i], msg);
	if (chan->isClient(msg.getClient()))
		return;
	if (chan->isLimit() && chan->isFull())
	{
		Server::sendMessage(ERR_CHANNELISFULL(msg.prefix(2), msg.getNick(), _channels[i]), msg.getFd());
		throw std::runtime_error("Channel is full");
	}
	if (chan->isInviteOnly() && !chan->isInvite(msg.getClient()))
	{
		Server::sendMessage(ERR_INVITEONLYCHAN(msg.prefix(2), msg.getNick(), _channels[i]), msg.getFd());
		throw std::runtime_error("Channel is invite only");
	}
	if (!chan->getKey().empty() && (i >= _pswds.size() || !chan->access(_pswds[i])))
	{
		Server::sendMessage(ERR_BADCHANNELKEY(msg.prefix(2), msg.getNick(), _channels[i]), msg.getFd());
		throw std::runtime_error("Bad channel key");
	}
	msg.getClient()->addChannel(*chan);
	chan->addClient(msg.getClient());
	if (chan->isInviteOnly())
		chan->removeInvite(msg.getClient());
	chan->broadcastMessage(msg.prefix(2) + "JOIN :" + chan->getName());
	if (!chan->getTopic().empty())
		Server::sendMessage(RPL_TOPIC(msg.prefix(1), msg.getNick(), chan->getName(), chan->getTopic()), msg.getFd());
	std::string names;
	for (std::vector<Client*>::const_iterator it = chan->getClients().begin(); it != chan->getClients().end(); ++it) {
		if (chan->isChanop(*it))
            names += "@";
		names += (*it)->getNick() + " ";
	}
	Server::sendMessage(RPL_NAMREPLY(msg.prefix(1), msg.getNick(), chan->getName(), names), msg.getFd());
	Server::sendMessage(RPL_ENDOFNAMES(msg.prefix(1), msg.getNick(), chan->getName()), msg.getFd());
}

void Join::CreateChannel(const Message& msg, size_t i) {
	std::cout << "Channel does not exit, creating it (" << _channels[i] << ")" << std::endl;
	if (!isNameValid(_channels[i])) {
		Server::sendMessage(ERR_NOSUCHCHANNEL(msg.prefix(2), msg.getNick(), _channels[i]), msg.getFd());
		throw std::runtime_error("No such channel");
	}
	msg.getClient()->getServer()->getChannels()[_channels[i]] = Channel(_channels[i], msg.getClient()->getServer());
	Channel* chan = getChannelWithName(_channels[i], msg);
	msg.getClient()->addChannel(*chan);
	chan->addClient(msg.getClient());
	chan->addChanop(msg.getClient());
	chan->broadcastMessage(msg.prefix(2) + "JOIN :" + chan->getName());
	Server::sendMessage(RPL_NAMREPLY(msg.prefix(1), msg.getNick(), chan->getName(), "@" + msg.getNick()), msg.getFd());
	Server::sendMessage(RPL_ENDOFNAMES(msg.prefix(1), msg.getNick(), chan->getName()), msg.getFd());
}

//
// Created by bvasseur on 11/15/24.
//

class ACommand;

#include "Quit.h"

Quit::Quit() {
}

Quit::Quit(Quit const& src) {
	(void) src;
}

Quit::~Quit() {
}

Quit& Quit::operator=(Quit const& other) {
	(void) other;
	return (*this);
}

void	Quit::process(const Message& msg) {
	std::string toSend = msg.getTrailing();

	if (toSend.empty() && msg.getParams().size() > 0)
		toSend = msg.getParams()[0];
	for (std::map<std::string, Channel *>::const_iterator it =
			msg.getClient()->getChannels().begin() ;
			it != msg.getClient()->getChannels().end() ; it++) //going into each user's channel
		addRecip(it->second);
	_recip.erase(msg.getFd());
	for (std::set<int>::const_iterator it = _recip.begin() ;
			it != _recip.end() ; it++)
		Server::sendMessage(msg.prefix(2) + "QUIT :" + toSend, *it);
	msg.getClient()->setFlags(HAS_REGISTERED | IS_RM);
}

void	Quit::addRecip(const Channel *channel)
{
	for (std::vector<Client *>::const_iterator it = channel->getClients().begin();
			it != channel->getClients().end() ; it++)
		_recip.insert((*it)->getfd().fd); //adding each user once
}

ACommand	*Quit::clone(void) const {
	return new Quit();
}

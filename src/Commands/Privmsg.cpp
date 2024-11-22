//
// Created by bvasseur on 11/15/24.
//

#include "Privmsg.h"

Privmsg::Privmsg() {
}

Privmsg::Privmsg(Privmsg const& src) {
	*this = src;
}

Privmsg::~Privmsg() {
}

Privmsg& Privmsg::operator=(Privmsg const& other) {
	ACommand::operator=(other);
	return (*this);
}

void	Privmsg::process(const Message& msg) {
	std::vector<std::string> &recip;

	if (msg.getParams().empty())
	{
		// 411   ERR_NORECIPIENT			":No recipient given (<command>)"
		Server::sendMessage(ERR_NORECIPIENT(msg.prefix(1), msg.getNick(), msg.getCommand()), msg.getFd());
		throw std::invalid_argument(" :No recipient given (PRIVMSG)");
	}
	if (msg.getTrailing().empty())
	{
		if (msg.getParams.size() == 1)
			//ERR_NOTEXTTOSEND
		recip = ACommand::split(msg.getParams()[1], ',');
	}
	else
		recip = ACommand::split(msg.getTrailing(), ',');
	for (std::vector<std::string>::iterator it = recip.begin() ;
			it != recip.end() ; it++)
	{
		try
		{
			sendToRecipient(msg.getParams[0], *it, msg);
		}
		catch (std::exception &e)
		{
			std::cerr << C_ROUGE << "PRIVMSG from fd " << msg.getFd() << ":";
			std::cerr << e.what() << C_RESET << std::endl;
		}
	}
}

void	Privmsg::sendToRecipient(const std::string &toSend, 
		const std::string &recip, const Message& msg)
{
	if (recip[0] == '#' || recip[0] == '+' || recip[0] == '&' || recip[0] == '!')
	{
		channel = ACommand::getChannelWithName(recip, msg);
		channel->broadcastMessage(toSend, *msg.getClient());
		return ;
	}

}

ACommand	*Privmsg::clone(void) const {
	return new Privmsg();
}

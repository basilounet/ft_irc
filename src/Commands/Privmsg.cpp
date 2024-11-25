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

void	Privmsg::process(const Message& msg)
{
	std::string	toSend = msg.getTrailing();

	if (msg.getParams().empty())
	{
		// 411   ERR_NORECIPIENT			":No recipient given (<command>)"
		Server::sendMessage(ERR_NORECIPIENT(
					msg.prefix(1), msg.getNick(), msg.getCommand()), msg.getFd());
		throw std::invalid_argument(" :No recipient given (PRIVMSG)");
	}
	if (toSend.empty())
	{
		if (msg.getParams().size() == 1)
		{
			// 412   ERR_NOTEXTTOSEND			":No text to send"
			Server::sendMessage(ERR_NOTEXTTOSEND(
						msg.prefix(1), msg.getNick()), msg.getFd());
			throw std::invalid_argument(" :No text to send (PRIVMSG)");
		}
		toSend = msg.getParams()[1];
	}
	splitRecipients(toSend, msg);
}

void	Privmsg::splitRecipients(const std::string &toSend, const Message &msg)
{
	const std::vector<std::string>	&recip 
		= ACommand::split(msg.getParams()[0], ',', msg);

	for (std::vector<std::string>::const_iterator it = recip.begin() ;
			it != recip.end() ; it++)
	{
		try
		{
			sendToRecipient(toSend, *it, msg);
		}
		catch (std::exception &e)
		{
			std::cerr << C_ROUGE << "PRIVMSG from fd " << msg.getFd() << ":" 
				<< e.what() << C_RESET << std::endl;
		}
	}
}

void	Privmsg::sendToRecipient(const std::string &toSend, 
		const std::string &recip, const Message& msg)
{
	Channel	*channel;
	Client	*client;

	if (recip[0] == '#' || recip[0] == '&')
	{
		channel = getChannelWithName(recip, msg);
		channel->broadcastMessage(toSend, *msg.getClient());
	}
	else
	{
		client = getClientWithNick(recip, msg);
		Server::sendMessage(toSend, client->getfd().fd);
	}
	// 301   RPL_AWAY					"<nick> :<away message>"
	Server::sendMessage(RPL_AWAY(msg.prefix(2), msg.getNick(), toSend),
			msg.getFd());
}

ACommand	*Privmsg::clone(void) const {
	return new Privmsg();
}

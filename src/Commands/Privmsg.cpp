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
		= ACommand::split(msg.getParams()[0], ',', msg); // create vector containing all recipients name

	for (std::vector<std::string>::const_iterator it = recip.begin() ;
			it != recip.end() ; it++) // iterating vector to send message to each recipient
	{
		try
		{
			sendToRecipient(toSend, *it, msg); //throw if ERR_NOSUCHNICK or ERR_NOSUCHCHANNEL
		}
		catch (std::exception &e)
		{
			std::cerr << C_ROUGE << "PRIVMSG from fd " << msg.getFd() << ":" 
				<< e.what() << C_RESET << std::endl;
		}
	}
}

void	Privmsg::sendToRecipient(std::string toSend, 
		const std::string &recip, const Message& msg)
{
	Channel	*channel;
	Client	*client;

	toSend = msg.prefix(2) + "PRIVMSG " + recip + " :" + toSend; // convert string to proper format
	if (recip[0] == '#' || recip[0] == '&') // first characters in channel name
	{
		channel = getChannelWithName(recip, msg); // throw if ERR_NOSUCHCHANNEL
		channel->broadcastMessage(toSend, *msg.getClient()); // send to all clients in the channel
		return ;
	}
	client = getClientWithNick(recip, msg); // throw if ERR_NOSUCHNICK
	Server::sendMessage(toSend, client->getfd().fd); // send to one client
}

ACommand	*Privmsg::clone(void) const {
	return new Privmsg();
}

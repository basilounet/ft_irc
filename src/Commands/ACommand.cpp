#include <ACommand.h>
#include "Message.h"

ACommand::ACommand() {
}

ACommand::ACommand(const ACommand& src) {
	*this = src;
}

ACommand& ACommand::operator=(const ACommand& right) {
	if (this != &right) {
	}
	return (*this);
}

ACommand::~ACommand() {
}

bool ACommand::checkNbParam(const Message& msg, unsigned int nbminParam, bool checkTrailing) {
	if (msg.getParams().size() < nbminParam || (checkTrailing && msg.getTrailing().empty())) {
		// 461   ERR_NEEDMOREPARAMS			"<command> :Not enough parameters"
		Server::sendMessage(ERR_NEEDMOREPARAMS(msg.prefix(1), msg.getNick(), msg.getCommand()), msg.getFd());
		throw std::invalid_argument(msg.getCommand() + ":Not enough parameters");
	}
	return (false);
}

Client* ACommand::getClientWithNick(const std::string& nick, const Message& msg) {
	Client* client = msg.getClient()->getServer()->getClientWithNick(nick);
	if (client == NULL) {
		// 401   ERR_NOSUCHNICK				"<nickname> :No such nick/channel"
		Server::sendMessage(ERR_NOSUCHNICK(msg.prefix(1), msg.getNick(), nick), msg.getFd());
		throw std::invalid_argument(nick + ":No such No such nick");
	}
	return (client);
}

Client* ACommand::getClientInChannel(const std::string& nick, Channel* chan, const Message& msg) {
	Client* client = getClientWithNick(nick, msg); // throw if
	if (!chan->isClient(client)) {
		// 442   ERR_NOTONCHANNEL			"<channel> :You're not on that channel"
		Server::sendMessage(ERR_NOTONCHANNEL(msg.prefix(1), msg.getNick(), chan->getName()), msg.getFd());
		throw std::invalid_argument(chan->getName() + ":You're not on that channel");
	}
	return (client);
}

Client* ACommand::getClientInChannel441(const std::string& nick, Channel* chan, const Message& msg) {
	Client* client = getClientWithNick(nick, msg); // throw if
	if (!chan->isClient(client)) {
		// 441   ERR_USERNOTINCHANNEL		"<nick> <channel> :They aren't on that channel"
		Server::sendMessage(ERR_USERNOTINCHANNEL(msg.prefix(1), msg.getNick(), nick, chan->getName()), msg.getFd());
		throw std::invalid_argument( nick + " " + chan->getName() + ":They aren't on that channel");
	}
	return (client);
}

Client* ACommand::getChanopInChannel(const std::string& nick, Channel* chan, const Message& msg) {
	Client* client = getClientInChannel(nick, chan, msg);				// throw if
	if (!chan->isChanop(client)) {
		// 482   ERR_CHANOPRIVSNEEDED		"<channel> :You're not channel operator"
		Server::sendMessage(ERR_CHANOPRIVSNEEDED(msg.prefix(1), msg.getNick(), chan->getName()), msg.getFd());
		throw std::invalid_argument(chan->getName() + ":You're not channel operator");
	}
	return (client);
}
Client* ACommand::getInviteInChannel(const std::string& nick, Channel* chan, const Message& msg) {
	Client* client = getClientInChannel(nick, chan, msg);				// throw if
	if (!chan->isInvite(client)) {
		// 482   ERR_CHANOPRIVSNEEDED		"<channel> :You're not channel operator"
		Server::sendMessage(ERR_CHANOPRIVSNEEDED(msg.prefix(1), msg.getNick(), chan->getName()), msg.getFd());
		throw std::invalid_argument(chan->getName() + ":You're not channel operator");
	}
	return (client);
}

Channel* ACommand::getChannelWithName(const std::string &name, const Message& msg) {
	Channel* chan = msg.getClient()->getServer()->getChannelWithName(name);
	if (chan == NULL) {
		// 403   ERR_NOSUCHCHANNEL			"<channel> :No such channel"
		Server::sendMessage(ERR_NOSUCHCHANNEL(msg.prefix(1), msg.getNick(), name), msg.getFd());
		throw std::invalid_argument(name + ":No such channel");
	}
	return (chan);
}


void ACommand::commandUnknown(const Message& msg) {
	// 421	  ERR_UNKNOWNCOMMAND		"<command> :Unknown command"
	Server::sendMessage(ERR_UNKNOWNCOMMAND(msg.prefix(1), msg.getNick(), msg.getCommand()), msg.getFd());
	throw std::invalid_argument(msg.getCommand() + ":Unknown command");
}

std::vector<std::string> ACommand::split(const std::string& str,
		const char separator, const Message &msg)
{
    std::vector<std::string>	result;
    std::string					line;
    size_t						pos0 = 0;
    size_t						pos1 = 0;
	int							i = 0;

    pos0 = str.find(separator, 0);
    line = str.substr(0, pos0);
    result.push_back(line);
    while (pos0 != std::string::npos)
    {
		pos1 = str.find(separator, pos0 + 1);
		line = str.substr(pos0 + 1, pos1 - pos0 - 1);
		pos0 = pos1;
		if (line.empty())
			continue ;
		result.push_back(line);
		if (++i > 50000)
		{
			// 407 ERR_TOOMANYTARGETS "<nick> : too many recipients. 
			// <command> interruption"
			Server::sendMessage(ERR_TOOMANYTARGETS
					(msg.prefix(1), msg.getNick(), msg.getCommand()),
					msg.getFd());
			throw std::logic_error(msg.getCommand() + ": Too many targets");
		}
    }
    return (result);
}

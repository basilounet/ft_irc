#include <ACommand.h>

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

bool ACommand::isMsgParamEmpty(const Message& msg) {
	if (msg.getParams().empty()) {
		// 461   ERR_NEEDMOREPARAMS			"<command> :Not enough parameters"
		Server::sendMessage(ERR_NEEDMOREPARAMS(msg.prefix(1), msg.getNick(), msg.getCommand()), msg.getFd());
		throw std::invalid_argument(msg.getCommand() + ":Not enough parameters");
	}
	return (false);
}

Client* ACommand::getClientWithNick(std::string &nick, const Message& msg) {
	Client* client = msg.getClient()->getServer()->getClientWithNick(nick);
	if (client == NULL) {
		// 401   ERR_NOSUCHNICK				"<nickname> :No such nick/channel"
		Server::sendMessage(ERR_NOSUCHNICK(msg.prefix(1), msg.getNick(), nick), msg.getFd());
		throw std::invalid_argument(nick + ":No such No such nick");
	}
	return (client);
}

Channel* ACommand::getChannelWithName(std::string &name, const Message& msg) {
	Channel* chan = msg.getClient()->getServer()->getChannelWithName(name);
	if (chan == NULL) {
		// 403   ERR_NOSUCHCHANNEL			"<channel> :No such channel"
		Server::sendMessage(ERR_NOSUCHCHANNEL(msg.prefix(1), msg.getNick(), name), msg.getFd());
		throw std::invalid_argument(name + ":No such channel");
	}
	return (chan);
}

bool ACommand::isInChannel(const std::string &nick, Channel* chan, const Message& msg) {
	if (!chan->isInChannel(nick)) {
		// 442   ERR_NOTONCHANNEL			"<channel> :You're not on that channel"
		Server::sendMessage(ERR_NOTONCHANNEL(msg.prefix(1), msg.getNick(), chan->getName()), msg.getFd());
		throw std::invalid_argument(chan->getName() + ":You're not on that channel");
	}
	return (true);
}

bool ACommand::isChanop(const std::string &nick, Channel* chan, const Message& msg) {
	if (!chan->isChanop(nick)) {
		// 482   ERR_CHANOPRIVSNEEDED		"<channel> :You're not channel operator"
		Server::sendMessage(ERR_CHANOPRIVSNEEDED(msg.prefix(1), msg.getNick(), chan->getName()), msg.getFd());
		throw std::invalid_argument(chan->getName() + ":You're not channel operator");
	}
	return (true);
}

void ACommand::commandUnknown(const Message& msg) {
	// 421	  ERR_UNKNOWNCOMMAND		"<command> :Unknown command"
	Server::sendMessage(ERR_UNKNOWNCOMMAND(msg.prefix(1), msg.getNick(), msg.getCommand()), msg.getFd());
	throw std::invalid_argument(msg.getCommand() + ":Unknown command");
}

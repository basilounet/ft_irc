//
// Created by bvasseur on 11/26/24.
//

#include "Bot.h"

Bot::Bot() {
}

Bot::Bot(Bot const& src) {
	*this = src;
}

Bot::~Bot() {
}

Bot& Bot::operator=(Bot const& other) {
	ACommand::operator=(other);
	if (this != &other) {
	}
	return (*this);
}

void	Bot::process(const Message& msg) {
	checkNbParam(msg, 1);

	if (msg.getParams()[0] == "rr" || msg.getParams()[0] == "russianRoulette")
		russianRoulette(msg);
}

/**
 * /BOT "rr"|"russianRoulette" #_channel [<user> *("," <user>)]
 */
void	Bot::russianRoulette(const Message& msg) {
	checkNbParam(msg, 2);
	initParams(msg);
	_chan->addNewPlayers();
	Privmsg::sendToRecipient("WARNING !!!!!!!!!!!!!! WARNING !!!!!!!!!!!!!!!",
			_chan->getName(), msg, true);
	Privmsg::sendToRecipient("THE GREATEST GAME HAS BEGUN. BE AFRAID YOU \
FREAKS, FOR THE ALMIGHTY IRC BOT HAS CHOSEN ONE AMONG YOU TO BE VANISHED FROM \
HIS PRESTIGIOUS CHANNEL", _chan->getName(), msg, true);
	broadcastBoard(_chan, msg);
	size_t index = rand() % _users.size();
	Privmsg::sendToRecipient(
			"IN HIS INFINITE WISDOM, THE ALMIGHTY IRC BOT HAS DECIDED: " +
			_users[index]->getNick() + 
			" IS NOT WORTHY OF STAYING IN THIS GLORIOUS CHANNEL",
			_chan->getName(), msg, true);
	if (removeVictim(_users[index], msg))
		return ;
	if (_OpRm)
	{
		Privmsg::sendToRecipient("THE ALMIGHTY IRC BOT HAS REMOVED AN OPERATOR \
AND GRANTS 2 POINTS TO UNWORTHY REMAINING PLAYERS", 
_chan->getName(), msg, true);
		_chan->addPoints(2);
	}
	else
	{
		Privmsg::sendToRecipient("YOU ARE LUCKY TO BE LEFT ALIVE BY ALMIGHTY \
IRC BOT, HE GRANTS YOU 1 POINT, THANK HIM FOR THE CENTURIES TO COME !!",
_chan->getName(), msg, true);
		_chan->addPoints(1);
	}
	broadcastBoard(_chan, msg);
}

bool	Bot::removeVictim(Client *victim, const Message& msg)
{
	bool	ChanRm;

	_OpRm = false;
	if (_chan->isChanop(victim))
	{
		_OpRm = true;
		if (!_chan->isChanop(msg.getClient())) 
		{
			_chan->addChanop(msg.getClient());
			_chan->broadcastMessage(msg.prefix(2) + "MODE " 
					+ _chan->getName() + " +o " + msg.getNick() + CRLF);
		}
	}
	_chan->broadcastMessage(msg.prefix(2) + "KICK " + _chan->getName() + " " +
			victim->getNick() + " :lost to Russian Roulette" + CRLF);
	victim->removeChannel(_chan->getName());
	_chan->removeChanop(victim);
	_chan->removePlayer(victim);
	ChanRm = _chan->removeClient(victim);
	return ChanRm;
}

void	Bot::initParams(const Message& msg)
{
	const std::string chanName = msg.getParams()[1];

	_chan = getChannelWithName(chanName, msg);
	if (!_chan->isClient(msg.getClient())) 
	{
		Server::sendMessage(
				ERR_NOTONCHANNEL(msg.prefix(1), msg.getNick(), chanName),
				msg.getFd());
		throw std::invalid_argument("Not on Channel");
	}
	if (msg.getParams().size() >= 3) {
		_usersNames = split(msg.getParams()[2], ',', msg);
		for (size_t i = 0; i < _usersNames.size(); ++i) {
			try {
				Client* user = getClientInChannel441(_usersNames[i], _chan, msg);
				_users.push_back(user);
			}
			catch (std::exception &e) {
				std::cout << C_ROUGE << "Error russianRoulette unknown player: "
					<< e.what() << C_RESET << std::endl;
			}
		}
	}
	else
		_users = _chan->getClients();
}

void	Bot::broadcastBoard(const Channel *_chan, const Message &msg) const
{
	const std::map<const Client *, int>	&GameBoard = _chan->getGameBoard();
	std::string							tmpNick;

	Privmsg::sendToRecipient("MISERABLES FOOLS AT ALMIGHTY IRC BOT MERCY:",
			_chan->getName(), msg, true);
	for (std::map<const Client *, int>::const_iterator it = GameBoard.begin() ;
			it != GameBoard.end() ; it++)
	{
		tmpNick = it->first->getNick();
		tmpNick.resize(10, ' ');
		std::stringstream stream;
		stream << it->second;
		Privmsg::sendToRecipient(tmpNick + "- " + stream.str(), 
				_chan->getName(), msg, true);
	}
}

ACommand	*Bot::clone(void) const {
	return (new Bot());
}

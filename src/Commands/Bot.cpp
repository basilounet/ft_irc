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

void	Bot::process(const Message &msg) {
	_msg = msg;
	checkNbParam(_msg, 1);
	if (_msg.getParams()[0] == "rr" || _msg.getParams()[0] == "russianRoulette")
		russianRoulette();
	if (_msg.getParams()[0] == "shop")
		displayShop();
	if (_msg.getParams()[0] == "buy")
		buy();
}

/**
 * /BOT "rr"|"russianRoulette" #_channel [<user> *("," <user>)]
 */
void	Bot::russianRoulette(void) {
	checkNbParam(msg, 2);
	initParams();
	_chan->addNewPlayers();
	Privmsg::sendToRecipient("WARNING !!!!!!!!!!!!!! WARNING !!!!!!!!!!!!!!!",
			_chan->getName(), _msg, true);
	Privmsg::sendToRecipient("THE GREATEST GAME HAS BEGUN. BE AFRAID YOU \
FREAKS, FOR THE ALMIGHTY IRC BOT HAS CHOSEN ONE AMONG YOU TO BE VANISHED FROM \
HIS PRESTIGIOUS CHANNEL", _chan->getName(), _msg, true);
	broadcastBoard();
	size_t index = rand() % _users.size();
	if (_chan->getPlayer(_users[index]).immunity)
	{
		Privmsg::sendToRecipient(""
	}
	Privmsg::sendToRecipient(
			"IN HIS INFINITE WISDOM, THE ALMIGHTY IRC BOT HAS DECIDED: " +
			_users[index]->getNick() + 
			" IS NOT WORTHY OF STAYING IN THIS GLORIOUS CHANNEL",
			_chan->getName(), _msg, true);
	if (removeVictim(_users[index]))
		return ;
	if (_OpRm)
	{
		Privmsg::sendToRecipient("THE ALMIGHTY IRC BOT HAS REMOVED AN OPERATOR \
AND GRANTS 2 POINTS TO UNWORTHY REMAINING PLAYERS", 
_chan->getName(), _msg, true);
		_chan->addPoints(2);
	}
	else
	{
		Privmsg::sendToRecipient("YOU ARE LUCKY TO BE LEFT ALIVE BY ALMIGHTY \
IRC BOT, HE GRANTS YOU 1 POINT, THANK HIM FOR THE CENTURIES TO COME !!",
_chan->getName(), _msg, true);
		_chan->addPoints(1);
	}
	broadcastBoard();
}

bool	Bot::removeVictim(Client *victim)
{
	bool	ChanRm;

	_OpRm = false;
	if (_chan->isChanop(victim))
	{
		_OpRm = true;
		if (!_chan->isChanop(_msg.getClient())) 
		{
			_chan->addChanop(_msg.getClient());
			_chan->broadcastMessage(_msg.prefix(2) + "MODE " 
					+ _chan->getName() + " +o " + _msg.getNick() + CRLF);
		}
	}
	_chan->broadcastMessage(_msg.prefix(2) + "KICK " + _chan->getName() + " " +
			victim->getNick() + " :lost to Russian Roulette" + CRLF);
	victim->removeChannel(_chan->getName());
	_chan->removeChanop(victim);
	_chan->removePlayer(victim);
	ChanRm = _chan->removeClient(victim);
	return ChanRm;
}

void	Bot::initParams(void)
{
	const std::string chanName = _msg.getParams()[1];

	_chan = getChannelWithName(chanName, _msg);
	getClientInChannel(getNick(), _chan, _msg); //throw if ERR_NOTONCHANNEL
	if (_msg.getParams().size() >= 3) {
		_usersNames = split(_msg.getParams()[2], ',', _msg);
		for (size_t i = 0; i < _usersNames.size(); ++i) {
			try {
				Client* user = getClientInChannel441(_usersNames[i], _chan, _msg);
				_users.push_back(user);
			}
			catch (std::exception &e) {
				std::cout << C_ROSE << "Error russianRoulette unknown player: " 
					<< e.what() << C_RESET << std::endl;
			}
		}
	}
	else
		_users = _chan->getClients();
}

void	Bot::broadcastBoard(void) const
{
	const std::map<const Client *, int>	&GameBoard = _chan->getGameBoard();
	std::string							tmpNick;

	Privmsg::sendToRecipient("MISERABLES FOOLS AT ALMIGHTY IRC BOT MERCY:",
			_chan->getName(), _msg, true);
	for (std::map<const Client *, int>::const_iterator it = GameBoard.begin() ;
			it != GameBoard.end() ; it++)

		tmpNick = it->first->getNick();
		tmpNick.resize(10, ' ');
		Privmsg::sendToRecipient(tmpNick + "- " + to_string(it->second.points) 
				+ " POINTS", _chan->getName(), _msg, true);
	}
}

void	Bot::displayShop(void) const
{
	Privmsg::sendToRecipient("IN HIS INFINITE KINDNESS ALMIGHTY IRC BOT MAY \
GRANT YOU SPECIAL APTITUDES IN EXCHANGE OF YOUR POINTS:", _msg.getNick(), _msg);
	Privmsg::sendToRecipient("", _msg.getNick(), _msg);
	Privmsg::sendToRecipient("ROBBERY OF WEALTHIEST: row       - 1 POINT", _msg.getNick(), _msg);
	Privmsg::sendToRecipient("IMMUNITY TO NEXT VANISHING: inv  - 2 POINTS", _msg.getNick(), _msg);
	Privmsg::sendToRecipient("TRANSCENDANCE OF THE MORTAL: ttm - " + to_string(10 + 5 * power(2, _chan->getPlayer(_msg.getClient()).gain)) + " POINTS", _msg.getNick(), _msg);
	Privmsg::sendToRecipient("LUCK OF THE UNGRATFUL: ltu       - 20 POINTS", _msg.getNick(), _msg);
}

void	Bot::buy()
{
	checkNbParam(_msg, 3);
	_chan = getChannelWithName(_msg.getParams()[2], _msg);
	getClientInChannel(_msg.getNick(), _chan, _msg); //throw if ERR_NOTONCHANNEL
	if (_msg.getParams()[1] == "row")
		row();
	if (_msg.getParams()[1] == "inv")
		inv();
	if (_msg.getParams()[1] == "ttm")
		ttm();
	if (_msg.getParams()[1] == "ltu")
		ltu();
}

bool	Bot::HasNotEnoughPoints(int price)
{
	if (_chan->getPlayer(msg.getClient()).points >= price)
		return false;
	Privmsg::sendToRecipient("YOU FOOL !!! HOW DARE YOU DISTURB THE ALMIGHTY IRC BOT !!! GO BACK TO THE ABYSS WHERE YOU BELONG !!!", _msg.getNick(), _msg);
	return true;
}

void	Bot::inv()
{
	checkPoints(2);
	_chan->getPlayer(_msg.getClient()).immunity = true;
}

ACommand	*Bot::clone(void) const {
	return (new Bot());
}

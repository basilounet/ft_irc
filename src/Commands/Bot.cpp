//
// Created by bvasseur on 11/26/24.
//

#include "Bot.h"

Bot::Bot() :
	_msg(__nullptr),
    _chan(__nullptr),
    _OpRm(false) {
}

Bot::Bot(Bot const& src) {
	*this = src;
}

Bot::~Bot() {
}

Bot& Bot::operator=(Bot const& other) {
	ACommand::operator=(other);
	if (this != &other) {
	    _msg = other._msg;
        _chan = other._chan;
        _usersNames = other._usersNames;
        _users = other._users;
        _OpRm = other._OpRm;
	}
	return (*this);
}

void	Bot::process(const Message &msg) {
	_msg = &msg;
	checkNbParam(*_msg, 1);
	if (_msg->getParams()[0] == "russianRoulette" || _msg->getParams()[0] == "rr")
		russianRoulette();
	if (_msg->getParams()[0] == "shop" || _msg->getParams()[0] == "s")
		displayShop();
	if (_msg->getParams()[0] == "buy" || _msg->getParams()[0] == "b")
		buy();
	if (_msg->getParams()[0] == "leaderboard" || _msg->getParams()[0] == "lb")
		leaderBoard();
	if (_msg->getParams()[0] == "stats")
        stats();
}

/**
 * /BOT "rr"|"russianRoulette" #_channel
 */
void	Bot::russianRoulette(void) {
	checkNbParam(*_msg, 2);
    _chan = getChannelWithName(_msg->getParams()[1], *_msg);
    if (_chan->getLastPlayer() == _msg->getClient()) {
        Privmsg::sendToRecipient("YOU FOOL !!! YOU CAN'T PLAY TWICE IN A ROW !!!", _msg->getNick(), *_msg);
        return ;
    }
    if (_chan->getPlayer(_msg->getClient()).getLTUShot() != true)
	    _chan->setLastPlayer(_msg->getClient());
	_users = _chan->getClients();
	Privmsg::sendToRecipient("WARNING !!!!!!!!!!!!!! WARNING !!!!!!!!!!!!!!!",
			_chan->getName(), *_msg, true);
	Privmsg::sendToRecipient("THE GREATEST GAME HAS BEGUN. BE AFRAID YOU \
FREAKS, FOR THE ALMIGHTY IRC BOT HAS CHOSEN ONE AMONG YOU TO BE VANISHED FROM \
HIS PRESTIGIOUS CHANNEL", _chan->getName(), *_msg, true);
	showBoard(_chan->getName());
	size_t index = rand() % _users.size();
	if (_chan->getPlayer(_users[index]).hasImmunity()) {
		_chan->getPlayer(_users[index]).setImmunity(0);
		Privmsg::sendToRecipient("TODAY THE ALMIGHTY IRC BOT CHOOSE TO BE MERCIFUL. " +
				_users[index]->getNick() + " HAS BEEN GRANTED IMMUNITY FOR THIS ROUND",
				_chan->getName(), *_msg, true);
		_chan->addPoints(1);
		if (_chan->getPlayer(_users[index]).hasLTU()) {
			_chan->getPlayer(_users[index]).setLTU(0);
			_chan->getPlayer(_users[index]).setLTUShot(true);
			Privmsg::sendToRecipient("ALTHOUGH, " + _users[index]->getNick() + " IS REATTACKING", _chan->getName(), *_msg, true);
			_chan->setLastPlayer(__nullptr);
			_chan->removeNbImmunity(1);
			try {
				Message msg(_users[index], "BOT rr " + _chan->getName() + CRLF);
				msg.execCommand();
			}
			catch (std::exception &e) {
				std::cout << C_ROSE << "Error BOT: " << e.what() << C_RESET << std::endl;
			}
			return ;
	    }
		_chan->removeNbImmunity(1);
		return ;
	}
	_chan->removeNbImmunity(1);
	Privmsg::sendToRecipient(
			"IN HIS INFINITE WISDOM, THE ALMIGHTY IRC BOT HAS DECIDED: " +
			_users[index]->getNick() + 
			" IS NOT WORTHY OF STAYING IN THIS GLORIOUS CHANNEL",
			_chan->getName(), *_msg, true);
	if (removeVictim(_users[index]))
		return ;
	std::string msg = "YOU ARE LUCKY TO BE LEFT ALIVE BY ALMIGHTY \
IRC BOT, HE GRANTS YOU 1 POINT, THANK HIM FOR THE CENTURIES TO COME !!";
	if (_OpRm)
		msg = "THE ALMIGHTY IRC BOT HAS REMOVED AN OPERATOR \
AND GRANTS 2 POINTS TO UNWORTHY REMAINING PLAYERS";
	Privmsg::sendToRecipient(msg, _chan->getName(), *_msg, true);
	_chan->addPoints(1 + _OpRm);
	showBoard(_chan->getName());
}

bool	Bot::removeVictim(Client *victim)
{
	bool	ChanRm = false;
	Player& player = _chan->getPlayer(_msg->getClient());

	_chan->getPlayer(victim).setImmunity(0);
	_OpRm = false;
	if (_chan->isChanop(victim))
	{
		_OpRm = true;
		if (!_chan->isChanop(_msg->getClient()))
		{
			_chan->addChanop(_msg->getClient());
			_chan->broadcastMessage(_msg->prefix(2) + "MODE "
					+ _chan->getName() + " +o " + _msg->getNick() + CRLF);
		}
	}
	if (player.getLTUShot() == true)
	{
		Privmsg::sendToRecipient("NOT ONLY HAVE YOU DIED BY THE HAND OF " +  _msg->getNick() + " BUT YOU HAVE ALSO LOST YOUR POINTS", _chan->getName(), *_msg, true);
		player.setLTUShot(false);
		if (victim != _msg->getClient())
			player.addPoints(_chan->getPlayer(victim).getPoints());
		_chan->getPlayer(victim).setPoints(0);
	}
	_chan->broadcastMessage(_msg->prefix(2) + "KICK " + _chan->getName() + " " +
			victim->getNick() + " :lost to Russian Roulette" + CRLF);
	victim->removeChannel(_chan->getName());
	_chan->removeChanop(victim);
	_chan->removePlayer(victim);
	ChanRm = _chan->removeClient(victim);
	return ChanRm;
}

void	Bot::showBoard(const std::string& at) const
{
	const std::map<const Client *, Player>	&gameBoard = _chan->getGameBoard();
	std::string							tmpNick;

	Privmsg::sendToRecipient("MISERABLES FOOLS AT ALMIGHTY IRC BOT MERCY:",
			at, *_msg, true);
	for (std::map<const Client *, Player>::const_iterator it = gameBoard.begin() ;
			it != gameBoard.end() ; it++)
	{
		tmpNick = it->first->getNick();
		tmpNick.resize(10, ' ');
		Privmsg::sendToRecipient(tmpNick + "- " + to_string(it->second.getPoints())
				+ " POINTS", at, *_msg, true);
	}
}

void	Bot::displayShop(void) const
{
	Channel *chan = __nullptr;

	if (_msg->getParams().size() >= 2)
	{
		chan = getChannelWithName(_msg->getParams()[1], *_msg);
	    getClientInChannel(_msg->getNick(), chan, *_msg); //throw if ERR_NOTONCHANNEL
	}
	Privmsg::sendToRecipient("IN HIS INFINITE KINDNESS ALMIGHTY IRC BOT MAY \
GRANT YOU SPECIAL APTITUDES IN EXCHANGE OF YOUR POINTS:", _msg->getNick(), *_msg);
	Privmsg::sendToRecipient("", _msg->getNick(), *_msg);
	Privmsg::sendToRecipient("ROBBERY OF WEALTHIEST: row       - 1 POINT", _msg->getNick(), *_msg);
	Privmsg::sendToRecipient("+1 ROUND OF IMMUNITY FROM VANISHING: inv  - 2 POINTS", _msg->getNick(), *_msg);
	if (!chan)
		Privmsg::sendToRecipient("TRANSCENDANCE OF THE MORTAL: ttm - 10 POINTS (Increasing)", _msg->getNick(), *_msg);
	else
		Privmsg::sendToRecipient("TRANSCENDANCE OF THE MORTAL: ttm - " + to_string(5 + 5 * (1 << chan->getPlayer(_msg->getClient()).getGain())) + " POINTS", _msg->getNick(), *_msg);
	Privmsg::sendToRecipient("LUCK OF THE UNGRATFUL: ltu       - 5 POINTS", _msg->getNick(), *_msg);
}

void	Bot::leaderBoard() {
	checkNbParam(*_msg, 2);
	_chan = getChannelWithName(_msg->getParams()[1], *_msg);
	showBoard(_msg->getNick());
}

void	Bot::stats() {
    checkNbParam(*_msg, 2);
    _chan = getChannelWithName(_msg->getParams()[1], *_msg);
    getClientInChannel(_msg->getNick(), _chan, *_msg);
	Player& player = _chan->getPlayer(_msg->getClient());
	Privmsg::sendToRecipient("STATS OF THE GLORIOUS " + _msg->getNick() + " on " + _chan->getName(), _msg->getNick(), *_msg);
	Privmsg::sendToRecipient("Points : " + to_string(player.getPoints()), _msg->getNick(), *_msg);
	Privmsg::sendToRecipient("Bonus point per vanishing : " + to_string(player.getGain()), _msg->getNick(), *_msg);
	Privmsg::sendToRecipient("Turns of invulnerability : " + to_string(player.getImmunity()) + " (" + to_string(player.getLTU()) + ")", _msg->getNick(), *_msg);
}


void	Bot::buy()
{
	checkNbParam(*_msg, 3);
	_chan = getChannelWithName(_msg->getParams()[2], *_msg);
	getClientInChannel(_msg->getNick(), _chan, *_msg); //throw if ERR_NOTONCHANNEL
	if (_msg->getParams()[1] == "row")
		roberryOfTheWealth();
	if (_msg->getParams()[1] == "inv")
		immunityToVanishing();
	if (_msg->getParams()[1] == "ttm")
		TranscendanceOfTheMortal();
	if (_msg->getParams()[1] == "ltu")
		LuckOfTheUngratful();
}

bool	Bot::HasNotEnoughPoints(int price)
{
	if (_chan->getPlayer(_msg->getClient()).getPoints() >= price)
		return false;
	Privmsg::sendToRecipient("YOU FOOL !!! HOW DARE YOU DISTURB THE ALMIGHTY IRC BOT !!! GO BACK TO THE ABYSS WHERE YOU BELONG !!!", _msg->getNick(), *_msg);
	return true;
}

void	Bot::roberryOfTheWealth() {
	if (HasNotEnoughPoints(1))
        return ;
	Player player = _chan->getPlayer(_msg->getClient());
	Player* wealthiest = const_cast<Player*>(&_chan->getGameBoard().begin()->second);
	for (std::map<const Client *, Player>::const_iterator it = _chan->getGameBoard().begin(); it != _chan->getGameBoard().end() ; ++it) {
        if (it->second.getPoints() > wealthiest->getPoints() && wealthiest == &player)
            wealthiest = const_cast<Player*>(&(it->second));
    }
	if (&player == wealthiest) {
        Privmsg::sendToRecipient("YOU FOOL !!! YOU ARE ALREADY THE WEALTHIEST !!!", _msg->getNick(), *_msg);
        return ;
    }
	int	removed = wealthiest->getPoints() > 2 ? 2 : wealthiest->getPoints();
    player.addPoints(-1);
	wealthiest->addPoints(-removed);
	Privmsg::sendToRecipient("YOU HAVE SUCCESSFULLY STOLE THE WEALTHIEST", _msg->getNick(), *_msg);
	if (std::rand() % 3 == 0) {
	    Privmsg::sendToRecipient("AND KEPT THE " + to_string(removed) + " POINTS", _msg->getNick(), *_msg);
		player.addPoints(removed);
	}
}

/*
    * /BOT buy "inv" #_channel [nbOfTurns]
*/
void	Bot::immunityToVanishing()
{
	int nbOfTurns = 1;
	if (_msg->getParams().size() >= 4)
		nbOfTurns = std::abs(std::atoi(_msg->getParams()[3].c_str()));
	if (HasNotEnoughPoints(2 * nbOfTurns))
		return ;
	Player &player = _chan->getPlayer(_msg->getClient());
	Privmsg::sendToRecipient("CONSIDER YOURSELF LUCKY, THE ALMIGHTY IRC BOT HAS GRANTED YOU IMMUNITY TO THE NEXT TIME HE WILL VANISH SOMEONE", _msg->getNick(), *_msg);
	player.addPoints(-2 * nbOfTurns);
	player.addImmunity(nbOfTurns);
}

/*
    * /BOT buy "ttm" #_channel [nbOfTurns]
*/
void	Bot::TranscendanceOfTheMortal() {
	Player &player = _chan->getPlayer(_msg->getClient());
	int price = 5 + 5 * (1 << player.getGain());
	if (HasNotEnoughPoints(price))
		return ;
	Privmsg::sendToRecipient("YOU HAVE LEARNED FROM THE MISTAKES OF THE OTHERS. GOOD", _msg->getNick(), *_msg);
	player.addPoints(-price);
	player.addGain(1);
}

/*
    * /BOT buy "ltu" #_channel [nbOfTurns]
*/
void	Bot::LuckOfTheUngratful() {
 	int nbOfTurns = 1;
	if (_msg->getParams().size() >= 4)
		nbOfTurns = std::abs(std::atoi(_msg->getParams()[3].c_str()));
	if (HasNotEnoughPoints(5 * nbOfTurns))
		return ;
    Player &player = _chan->getPlayer(_msg->getClient());
	Privmsg::sendToRecipient("YOU HAVE BEEN GRANTED THE LUCK OF THE UNGRATFUL FOR " + to_string(nbOfTurns * 5) + " MORE ROUNDS", _msg->getNick(), *_msg);
	Privmsg::sendToRecipient("BEWARE, IT WILL ONLY WORK IF YOU HAVE INVULNERABILITY", _msg->getNick(), *_msg);
	player.addPoints(-5 * nbOfTurns);
	player.addLTU(5 * nbOfTurns);
}

ACommand	*Bot::clone(void) const {
	return (new Bot());
}

//
// Created by bvasseur on 11/28/24.
//

#include "Player.h"

Player::Player() :
		_points(0),
		_gain(0),
		_turnOfImmunityLeft(0),
		_isLTU(false) {
}


Player::~Player() {
}

Player::Player(const Player& src) {
	*this = src;
}

Player& Player::operator=(const Player& src) {
	if (this != &src) {
		_points = src._points;
		_gain = src._gain;
		_turnOfImmunityLeft = src._turnOfImmunityLeft;
		_isLTU = src._isLTU;
	}
	return (*this);
}


void		Player::setPoints(int points) 		{ _points = points; }
int			Player::getPoints( void )	const	{ return (_points); }
void		Player::addPoints(int toAdd)		{ _points += toAdd; }
void		Player::gainPoints(int toAdd)		{ _points += toAdd + _gain; }

void		Player::setGain(int gain)			{ _gain = gain; }
int			Player::getGain( void )		const	{ return (_gain); }
void		Player::addGain(int toAdd)			{ _gain += toAdd; }

void		Player::setImmunity(int nbOfTurns)	{ _turnOfImmunityLeft = nbOfTurns; }
int			Player::getImmunity( void )	const	{ return (_turnOfImmunityLeft); }
bool		Player::hasImmunity( void ) const	{ return (_turnOfImmunityLeft >= 1); }

void		Player::addImmunity(int toAdd) {
 	_turnOfImmunityLeft += toAdd;
	if (_turnOfImmunityLeft <= 0) {
		_turnOfImmunityLeft = 0;
		_isLTU = false;
	}
}

bool	Player::isLTU( void ) const	{ return (_isLTU); }

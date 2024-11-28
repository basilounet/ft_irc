//
// Created by bvasseur on 11/28/24.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

class Player {
public:
	Player();
	Player(Player const& src);
	~Player();
	Player& operator=(Player const& other);

	void		setPoints(int points);
	int			getPoints( void )	const;
	void		addPoints(int toAdd);

	void		setGain(int gain);
	int			getGain( void )		const;
	void		addGain(int toAdd);

	void		setImmunity(int nbOfTurns);
	int			getImmunity( void )	const;
	void		addImmunity(int toAdd);
	bool		hasImmunity( void )	const;

private:
	int		_points;
	int		_gain;
	int		_turnOfImmunityLeft;
	bool	_isLTU;
};



#endif //PLAYER_H

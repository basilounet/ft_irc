//
// Created by bvasseur on 11/26/24.
//

#ifndef BOT_H
#define BOT_H

# include "ACommand.h"
# include <cmath>

class Bot : public ACommand {
	public:
		Bot();
		Bot(Bot const& src);
		~Bot();
		Bot& operator=(Bot const& other);

		void		process(const Message& msg);
		ACommand	*clone(void) const;

	private:
		const Message				*_msg;
		Channel						*_chan;
//		Client						*_victim;
		std::vector<std::string>	_usersNames;
		std::vector<Client *>		_users;
		bool						_OpRm;

		void	russianRoulette();
		void	initParams();
		bool	removeVictim(Client *victim);
		void	showBoard(const std::string& at) const;
		void	displayShop(void) const;
		bool	HasNotEnoughPoints(int price);
		void	leaderBoard();
		void	stats();
		void	buy();

		void	roberryOfTheWealth();
		void	immunityToVanishing();
		void	TranscendanceOfTheMortal();
		void	LuckOfTheUngratful();
};

#endif //BOT_H

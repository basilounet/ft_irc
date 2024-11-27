//
// Created by bvasseur on 11/26/24.
//

#ifndef BOT_H
#define BOT_H

#include "ACommand.h"

typedef struct s_player {
	int		points;
	int		gain;
	bool	immunity;
}		t_player;

class Bot : public ACommand {
	public:
		Bot();
		Bot(Bot const& src);
		~Bot();
		Bot& operator=(Bot const& other);

		void		process(const Message& msg);
		ACommand	*clone(void) const;

	private:
		const Message				&_msg
		Channel						*_chan;
		Client						&_victim;
		std::vector<std::string>	_usersNames;
		std::vector<Client *>		_users;
		bool						_OpRm;

		void	russianRoulette();
		void	initParams();
		bool	removeVictim(Client *victim);
		void	broadcastBoard() const;
};

#endif //BOT_H

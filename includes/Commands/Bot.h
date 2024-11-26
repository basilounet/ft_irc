//
// Created by bvasseur on 11/26/24.
//

#ifndef BOT_H
#define BOT_H

#include "ACommand.h"

class Bot : public ACommand {
public:
	Bot();
	Bot(Bot const& src);
	~Bot();
	Bot& operator=(Bot const& other);

	void	process(const Message& msg);
	ACommand	*clone(void) const;

private:
	std::vector<std::string>	_usersNames;
	std::vector<Client *>		_users;

	void	russianRoulette(const Message& msg);

};



#endif //BOT_H

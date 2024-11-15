//
// Created by bvasseur on 11/15/24.
//

#ifndef KICK_H
#define KICK_H

# include <ACommand.h>

class Kick : public ACommand {
public:
	Kick( void );
	Kick(Kick const &src);
	~Kick( void );
	Kick &operator=(Kick const &other);

	void	executeCommand(const Message& msg);
};



#endif //KICK_H

//
// Created by bvasseur on 11/15/24.
//

#ifndef INVITE_H
#define INVITE_H

# include <ACommand.h>

class Invite : public ACommand {
public:
	Invite( void );
	Invite(Invite const &src);
	~Invite( void );
	Invite &operator=(Invite const &other);

	void	process(const Message& msg);
};

#endif //INVITE_H

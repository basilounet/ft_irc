//
// Created by bvasseur on 11/15/24.
//

#ifndef PASS_H
#define PASS_H

# include <ACommand.h>

class Pass : public ACommand {
public:
	Invite( void );
	Invite(Invite const &src);
	~Invite( void );
	Invite &operator=(Invite const &other);

	void	executeCommand(const Message& msg);
};



#endif //PASS_H

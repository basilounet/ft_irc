//
// Created by bvasseur on 11/15/24.
//

#ifndef INVITE_H
#define INVITE_H

# include <ACommand.h>

class Invite : public ACommand {
public:
	Invite();
	Invite(Invite const &src);
	~Invite();
	Invite &operator=(Invite const &other);

	void		process(const Message& msg);

	void		invite(const Message &msg);

	ACommand	*clone() const;

};

#endif //INVITE_H

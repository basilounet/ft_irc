//
// Created by bvasseur on 11/15/24.
//

#ifndef PRIVMSG_H
#define PRIVMSG_H

# include <ACommand.h>

class Privmsg : public ACommand {
public:
	Privmsg( void );
	Privmsg(Privmsg const &src);
	~Privmsg( void );
	Privmsg &operator=(Privmsg const &other);

	void		process(const Message& msg);
	ACommand	*clone(void) const;

};



#endif //PRIVMSG_H

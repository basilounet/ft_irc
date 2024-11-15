//
// Created by bvasseur on 11/15/24.
//

#ifndef NICK_H
#define NICK_H

# include <ACommand.h>

class Nick : public ACommand {
public:
	Nick( void );
	Nick(Nick const &src);
	~Nick( void );
	Nick &operator=(Nick const &other);

	void	executeCommand(const Message& msg);

};

#endif //NICK_H

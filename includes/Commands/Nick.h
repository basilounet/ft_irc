//
// Created by bvasseur on 11/15/24.
//

#ifndef NICK_H
#define NICK_H

# include <ACommand.h>
# include <iostream>

class Nick : public ACommand {
public:
	Nick( void );
	Nick(Nick const &src);
	~Nick( void );
	Nick &operator=(Nick const &other);

	void	process(const Message& msg);

private:
	static bool	hasInvalidCharacter(const std::string& str);

};

#endif //NICK_H

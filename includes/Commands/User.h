//
// Created by bvasseur on 11/15/24.
//

#ifndef USER_H
#define USER_H

# include <ACommand.h>

class User : public ACommand {
public:
	User( void );
	User(User const &src);
	~User( void );
	User &operator=(User const &other);

	void	process(const Message& msg);

};


#endif //USER_H

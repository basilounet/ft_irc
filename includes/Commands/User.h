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

	void		process(const Message& msg);
	void 		needMoreParams(const Message& msg) const;
	ACommand	*clone(void) const;

};


#endif //USER_H

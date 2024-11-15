//
// Created by bvasseur on 11/15/24.
//

#ifndef PASS_H
#define PASS_H

# include <ACommand.h>

class Pass : public ACommand {
public:
	Pass( void );
	Pass(Pass const &src);
	~Pass( void );
	Pass &operator=(Pass const &other);

	void	process(const Message& msg);
};



#endif //PASS_H

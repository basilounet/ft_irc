//
// Created by bvasseur on 11/15/24.
//

#ifndef MOD_H
#define MOD_H

# include <ACommand.h>

class Mode : public ACommand {
public:
	Mode( void );
	Mode(Mode const &src);
	~Mode( void );
	Mode &operator=(Mode const &other);

	void	executeCommand(const Message& msg);
};



#endif //MOD_H

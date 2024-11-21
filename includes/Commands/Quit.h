//
// Created by bvasseur on 11/15/24.
//

#ifndef QUIT_H
#define QUIT_H

# include <ACommand.h>

class Quit : public ACommand 
{
	public:
		Quit(void);
		Quit(Quit const &src);
		~Quit(void);
		Quit		&operator=(Quit const &other);

		void		process(const Message& msg);
		ACommand	*clone(void) const;
};

#endif //QUIT_H

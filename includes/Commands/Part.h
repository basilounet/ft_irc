//
// Created by bvasseur on 11/15/24.
//

#ifndef PART_H
#define PART_H

# include <ACommand.h>

class Part : public ACommand {
public:
	Part( void );
	Part(Part const &src);
	~Part( void );
	Part &operator=(Part const &other);

	void	executeCommand(const Message& msg);
};



#endif //PART_H

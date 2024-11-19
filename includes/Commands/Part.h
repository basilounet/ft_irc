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

	void		process(const Message& msg);
	ACommand	*clone(void) const;
};



#endif //PART_H

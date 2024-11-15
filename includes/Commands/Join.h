//
// Created by bvasseur on 11/15/24.
//

#ifndef JOIN_H
#define JOIN_H

# include <ACommand.h>

class Join : public ACommand {
public:
	Join( void );
	Join(Join const &src);
	~Join( void );
	Join &operator=(Join const &other);

	void	executeCommand(const Message& msg);
};



#endif //JOIN_H

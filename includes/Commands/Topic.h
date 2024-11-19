//
// Created by bvasseur on 11/15/24.
//

#ifndef TOPIC_H
#define TOPIC_H

# include <ACommand.h>

class Topic : public ACommand {
public:
	Topic( void );
	Topic(Topic const &src);
	~Topic( void );
	Topic &operator=(Topic const &other);

	void		process(const Message& msg);
	ACommand	*clone(void) const;

};



#endif //TOPIC_H

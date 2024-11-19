//
// Created by bvasseur on 11/15/24.
//

#ifndef TOPIC_H
#define TOPIC_H

# include <ACommand.h>

class Topic : public ACommand {
public:
	Topic();
	Topic(Topic const &src);
	~Topic();
	Topic &operator=(Topic const &other);

	void		process(const Message& msg);

	void		topic(const Message &msg);

	ACommand	*clone() const;

};

#endif //TOPIC_H

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

		ACommand	*clone() const;

	private:
		static void	topic(Channel *chan, const Message &msg);

};

#endif //TOPIC_H

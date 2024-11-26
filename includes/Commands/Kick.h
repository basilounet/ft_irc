//
// Created by bvasseur on 11/15/24.
//

#ifndef KICK_H
#define KICK_H

# include <ACommand.h>

class Kick : public ACommand {
public:
	Kick( void );
	Kick(Kick const &src);
	~Kick( void );
	Kick &operator=(Kick const &other);

	void		process(const Message& msg);
	ACommand	*clone(void) const;

private:
	std::vector<std::string>	_channels;
	std::vector<std::string>	_users;
	std::string					_reason;

	void	oneChannel(const Message& msg);
	void	multipleChannels(const Message& msg);
};



#endif //KICK_H

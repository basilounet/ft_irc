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

	void	process(const Message& msg);

private:
	static void	channelMode(const Message& msg);
	static void	userMode(const Message& msg);

	static void setChannelInviteOnly(const Message &msg, bool add);
	static void setChannelSettableTopic(const Message &msg, bool add);
	static void setChannelKey(const Message &msg, bool add);
	static void setChannelOperatorPrivilege(const Message &msg, bool add);
	static void setChannelLimit(const Message &msg, bool add);

};
#endif //MOD_H

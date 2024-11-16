//
// Created by bvasseur on 11/15/24.
//

#ifndef MOD_H
#define MOD_H

# include <ACommand.h>

class Mode : public ACommand {

public:
	Mode();
	Mode(Mode const &src);
	~Mode();
	Mode &operator=(Mode const &other);

	void	process(const Message& msg);

private:
	static void	channelMode(Channel* chan, const Message& msg);

	static void setChannelInviteOnly(Channel* chan, const Message &msg, bool add);
	static void setChannelSettableTopic(Channel* chan, const Message &msg, bool add);
	static void setChannelKey(Channel* chan, const Message &msg, bool add);
	static void setChannelOperatorPrivilege(Channel* chan, const Message &msg, bool add);
	static void setChannelLimit(Channel* chan, const Message &msg, bool add);

	static void	userMode(const Message& msg);

};
#endif //MOD_H

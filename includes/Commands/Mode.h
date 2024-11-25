//
// Created by bvasseur on 11/15/24.
//

#ifndef MODE_H
#define MODE_H

# include <ACommand.h>

class Mode : public ACommand {

public:
	Mode();
	Mode(Mode const &src);
	~Mode();
	Mode &operator=(Mode const &other);

	void		process(const Message& msg);
	ACommand	*clone(void) const;

private:
	static void	channelMode(Channel* chan, const Message& msg);

	static void channelModeI(Channel* chan, const Message &msg, bool add);
	static void channelModeT(Channel* chan, const Message &msg, bool add);
	static void channelModeK(Channel* chan, const Message &msg, bool add);
	static void channelModeO(Channel* chan, const Message &msg, bool add);
	static void channelModeL(Channel* chan, const Message &msg, bool add);

};
#endif //MODE_H

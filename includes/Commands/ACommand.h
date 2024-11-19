#pragma once

class Message;
class Client;
class Channel;

# include <string>
# include <vector>

class ACommand
{
	public:
		ACommand(void);
		ACommand(std::vector<std::string> &params);
		ACommand(const ACommand &src);
		ACommand	&operator=(const ACommand &right);
		virtual	~ACommand(void);

		virtual void process(const Message& msg) = 0;
		virtual ACommand *clone(void) const = 0;

		static void			isMsgParamEmpty(const Message& msg);
		static Client*		getClientWithNick(std::string &nick, const Message& msg);
		static Channel*		getChannelWithName(std::string &name, const Message& msg);
};

# include <Message.h>
# include <Server.h>

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

		static bool			isMsgParamEmpty(const Message& msg);

		static Client*		getClientWithNick(const std::string &nick, const Message& msg);
		static Client*		getClientInChannel(const std::string &nick, Channel* chan, const Message& msg);
		static Client*		getChanopInChannel(const std::string &nick, Channel* chan, const Message& msg);
		static Client*		getInviteInChannel(const std::string &nick, Channel* chan, const Message& msg);

		static Channel*		getChannelWithName(const std::string &name, const Message& msg);

		static void						commandUnknown(const Message& msg);
		static std::vector<std::string>	split(const std::string& str,
										const char separator, const Message &msg);

};

# include <Message.h>
# include <Server.h>

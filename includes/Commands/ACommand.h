#pragma once

class Message;
class Client;
class Channel;

# include <iostream>
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

	protected:
		static bool					checkNbParam(const Message& msg, unsigned int nbminParam, bool checkTrailing = false);

		static Client*				getClientWithNick(const std::string &nick, const Message& msg);
		static Client*				getClientInChannel(const std::string &nick, Channel* chan, const Message& msg);
		static Client*				getClientInChannel441(const std::string& nick, Channel* chan, const Message& msg);
		static Client*				getChanopInChannel(const std::string &nick, Channel* chan, const Message& msg);
		static Client*				getInviteInChannel(const std::string &nick, Channel* chan, const Message& msg);

		static Channel*				getChannelWithName(std::string &name, const Message& msg);

		static void					commandUnknown(const Message& msg);
		std::vector<std::string>	split(const std::string& str, const char separator);
};

# include <Message.h>
# include <Server.h>

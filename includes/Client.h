#ifndef CLIENT_H
#define CLIENT_H

class Server;
class Client;
class Channel;
class Message;

# include <Server.h>
# include <Channel.h>
# include <Message.h>
# include "IRC_responses.h"

# define HAS_TRY_PASS 0b1
# define HAS_NICK 0b10
# define HAS_REGISTERED 0b100
# define IS_RM 0b1000

class Client {
	public:
		Client();
		Client(const int fd, const std::string& name, const std::string& nick, Server* server);
		~Client();
		Client(const Client &src);
		Client &operator=(const Client &src);

		void									addChannel(Channel& channel);
		void									removeChannel(const std::string& name);
		void									quitAllChannels( void );
		void									broadcastToAllKnownUsers(const std::string& msg, bool shouldSendToSender = false);

		Server*									getServer()		const;
		pollfd									getfd()			const;
		std::string								getRealName()	const;
		const std::map<std::string, Channel*>&	getChannels()	const;
		std::string								getNick()		const;
		std::string								getUser()		const;
		std::string								getBuffer()		const;
		short									getFlags()		const;
		std::string								getPassword()	const;

		void									setRealName(const std::string& name);
		void									setNick(const std::string& name);
		void									setUser(const std::string& name);
		void									setBuffer(const std::string& buf);
		void									setFlags(short flags);
		void									setPassword(const std::string& pass);
		void									reset(void);

		void									appendBuffer(const std::string& buf);
		void									parseBuffer(); // split messages

	private:
		Server*									_server;
		std::string								_nick;
		std::string								_user;
		std::string								_realName;
		std::string								_password;
		std::map<std::string, Channel*>			_channels;
		pollfd									_fd;
		std::string								_buffer;
		short									_flags;
};

std::ostream &operator<<(std::ostream &out, const Client &client);

#endif //CLIENT_H

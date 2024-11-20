#ifndef MESSAGE_H
#define MESSAGE_H

class Server;
class Client;
class Channel;
class Message;
class ACommand;

# include <Server.h>
# include <ACommand.h>
# include <Invite.h>
# include <Join.h>
# include <Kick.h>
# include <Mode.h>
# include <Nick.h>
# include <Part.h>
# include <Pass.h>
# include <Privmsg.h>
# include <Topic.h>
# include <User.h>
// # include <Channel.h>
// # include <Client.h>
class Message {

public:
	Message();
	Message(Client* client, const std::string &msg );
	~Message();
	Message(const Message& src);
	Message &operator=(const Message& src);

	Client*						getClient()		const ;
	std::string					getMsg()		const ;
	std::string					prefix(int type) const ;
	std::string					getNick() const ;
	std::string					getServerName() const ;
	std::string					getCommand()	const ;
	std::vector<std::string>	getParams()		const ;
	std::string					getTrailing()	const ;
	int							getFd()			const ;

	void						execCommand();

private:
	ACommand*					_cmd;
	Client*						_client;
	std::string					_msg;
	std::string					_nick;
	std::string					_serverName;
	std::string					_command;
	std::vector<std::string>	_params;
	std::string					_trailing;


	void		parsePrefix(const std::string& str);
	void		parseCommand(const std::string& str);
	void		parseParams(const std::string& str);
	void		parseMsg();
	void		createCommand();
};


#endif //MESSAGE_H

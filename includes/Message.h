#ifndef MESSAGE_H
#define MESSAGE_H

class Server;
class Client;
class Channel;
class Message;

# include <Server.h>
// # include <Channel.h>
// # include <Client.h>

class Message {

	public:
		Message();
		Message(Client* client, const std::string &msg);
		~Message();
		Message(const Message& src);
		Message &operator=(const Message& src);

		Client*						getClient()		const ;
		std::string					getMsg()		const ;
		std::string					getNick()		const ;
		std::string					getServerName() const ;
		std::string					getCommand()	const ;
		std::vector<std::string>	getParams()		const ;
		std::string					getTrailing()	const ;

	private:
		Client*						_client;
		std::string					_msg;
		std::string					_nick;
		std::string					_server_name;
		std::string					_command;
		std::vector<std::string>	_params;
		std::string					_trailing;

		void		parseMsg();
		void		parsePrefix(const std::string& str);
		void		parseCommand(const std::string& str);
		void		parseParams(const std::string& str);

		bool		isnospcrlfcl(const std::string& str);
		bool		isCrlfEnding(const std::string& str);

};

#endif //MESSAGE_H

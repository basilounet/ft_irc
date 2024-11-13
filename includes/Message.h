#ifndef MESSAGE_H
#define MESSAGE_H

class Server;
class Client;
class Channel;
class Message;

# include "../includes/Server.h"
# include "../includes/Channel.h"
# include "../includes/Client.h"

class Message {
	public:
		Message();
		Message(Client* client, std::string msg);
		~Message();
		Message(const Message& src);
		Message &operator=(const Message& src);

		Client*						getClient()		const {return _client;}
		std::string					getStr()		const {return _str;}
		std::string					getNick()		const {return _nick;}
		std::string					getServerName() const {return _server_name;}
		std::string					getCommand()	const {return _command;}
		std::vector<std::string>	getParams()		const {return _params;}
		std::string					getTrailing()	const {return _trailing;}

	private:
		Client*						_client;
		std::string					_str;
		std::string					_nick;
		std::string					_server_name;
		std::string					_command;
		std::vector<std::string>	_params;
		std::string					_trailing;

		void			parseMessageStr();
		static void		parsePrefix(const std::string& str);
		static void		parseCommand(const std::string& str);
		static void		parseParams(const std::string& str);
		static void		removeSpaces(const std::string str);
		static bool		isnospcrlfcl(const std::string str);
		static bool		isCrlfEnding(const std::string str);

};

#endif //MESSAGE_H

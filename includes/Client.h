#ifndef CLIENT_H
#define CLIENT_H

class Server;
class Client;
class Channel;

# include <Server.h>
# include <Channel.h>

class Client {
public:
	Client();
	Client(const int fd, const std::string& name, const std::string& nick, Server* server);
	~Client();
	Client(const Client &src);
	Client &operator=(const Client &src);

	void		addChannel(Channel& channel);
	void		removeChannel(const std::string& name);
	void		quitAllChannels( void );

	pollfd		getfd() const;
	std::string	getRealName() const;
	std::string	getNick() const;
	std::string	getUser() const;
	std::string	getBuffer() const;

	void		setRealName(const std::string& name);
	void		setNick(const std::string& name);
	void		setUser(const std::string& name);
	void		setBuffer(const std::string& buf);

	void		appendBuffer(const std::string& buf);
	void		parseBuffer(); // split messages

private:
	Server*							_server;
	std::string						_nick;
	std::string						_user;
	std::string						_realName;
	std::map<std::string, Channel*>	_channels;
	pollfd							_fd;
	std::string						_buffer;
};

std::ostream &operator<<(std::ostream &out, const Client &client);

#endif //CLIENT_H

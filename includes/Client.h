#ifndef CLIENT_H
#define CLIENT_H

class Client;

# include <Server.h>
# include <Channel.h>

class Client {
public:
	Client();
	Client(const int fd, const std::string& name = "default", const std::string& nick = "default nick");
	~Client();
	Client(const Client &src);
	Client &operator=(const Client &src);

	pollfd		getfd() const;
	std::string	getRealName() const;
	std::string	getNick() const;
	std::string	getIpAddress() const;
	void		setRealName(const std::string& name);
	void		setNick(const std::string& name);
	void		setIpAddress(const std::string& ipaddress);

private:
	std::string				_nick;
	std::string				_realName;
	std::vector<Channel>	_channels;
	pollfd					_fd;
};

std::ostream &operator<<(std::ostream &out, const Client &client);

#endif //CLIENT_H

#ifndef CHANNEL_H
#define CHANNEL_H

class Channel;

# include <Server.h>
# include <Client.h>

class Channel {
public:
	Channel(const std::string& name = "default");
	~Channel();
	Channel(const Channel &src);
	Channel &operator=(const Channel &src);

private:
	std::string			_name;
	std::vector<Client>	_clients;
};



#endif //CHANNEL_H

#ifndef CHANNEL_H
#define CHANNEL_H

class Server;
class Client;
class Channel;

# include <Server.h>
# include <Client.h>

class Channel {
public:
	Channel();
	Channel(const std::string& name, Server* server);
	~Channel();
	Channel(const Channel &src);
	Channel &operator=(const Channel &src);

	void							broadcastMessage(const std::string& msg);
	void							broadcastMessage(const std::string& msg, const Client& sender, bool shouldSendToSender = false);
	void							addClient(Client& client);
	void						    removeClient(const Client& client);

	std::string						getName()	const;
	const std::map<int, Client*>&	getClients()	const;

private:
	Server*							_server;
	std::string						_name;
	std::map<int, Client*>			_clients;
};

#endif //CHANNEL_H

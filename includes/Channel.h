#ifndef CHANNEL_H
#define CHANNEL_H

class Server;
class Client;
class Channel;

# include <Server.h>
# include <Client.h>
# include <algorithm>

class Channel {
public:
	Channel();
	Channel(const std::string& name, Server* server);
	~Channel();
	Channel(const Channel &src);
	Channel &operator=(const Channel &src);

	void							broadcastMessage(const std::string& msg);
	void							broadcastMessage(const std::string& msg, const Client& sender, bool shouldSendToSender = false);

	void 							addClient(std::string &nick);
	void							addClient(Client& client);
	void 							removeClient(std::string &nick);
	void							removeClient(const Client& client);

	std::string						getName()	const;

	const std::vector<Client *> &getClients() const;

	bool		isInChannel(const std::string& nick)	const;
	bool		isChanop(std::string nick)		const;
	bool		isKey()							const;
	std::string	getKey()						const;
	bool		access(const std::string &pwd)	const;
	bool		isLimit()						const;
	int			getLimit()						const;
	bool		isFull()						const;
	bool		isInviteOnly()					const;
	bool		isSettableTopic()				const;

	bool 		addChanop(std::string &nick);
	bool 		removeChanop(std::string &nick);
	void		setKey(std::string key);
	void		setLimit(int limit);
	void		setInviteOnly(bool state);
	void		setSettableTopic(bool state);

private:
	Server*						_server;
	std::string					_name;
	std::vector<Client*>		_clients;
	std::vector<Client*>		_chanops;
	std::vector<std::string>	_invite;
	std::string					_key;
	int							_limit;
	bool						_inviteOnly;
	bool						_settableTopic;

};

#endif //CHANNEL_H

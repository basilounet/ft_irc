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

	void	broadcastMessage(const std::string& msg);
	void	broadcastMessage(const std::string& msg, const Client& sender);

	void 	addClient(std::string &nick);
	void    addClient(Client& client);
	void 	removeClient(std::string &nick);
	void    removeClient(const Client& client);

	std::string	getName() const;

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



	void 		addChanop(std::string &nick);
	void 		removeChanop(std::string &nick);
	void		setKey(std::string &key);
	void		setLimit(int limit);
	void		setInviteOnly(bool state);
	void		setSettableTopic(bool state);

private:
	Server*					_server;
	std::string				_name;
	std::map<int, Client*>	_clients;
	std::map<int, Client*>	_chanops;
	std::string				_key;
	int						_limit;
	bool					_inviteOnly;
	bool					_settableTopic;

};

#endif //CHANNEL_H

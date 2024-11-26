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

		void		broadcastMessage(const std::string& msg) const;
		void		broadcastMessage(const std::string& msg, const Client& sender, bool shouldSendToSender = false) const;

		Server*		getServer()	const;
		std::string	getName()	const;

		const std::vector<Client *> &getClients()	const;
		const std::vector<Client *> &getChanops()	const;
		const std::vector<Client*>	&getInvites()	const;

		bool		addClient(Client* client);
		bool		addChanop(Client* client);
		bool		addInvite(Client* client);

		bool		removeClient(Client* client);
		bool		removeChanop(Client* client);
		bool		removeInvite(Client* client);

		bool		isClient(Client* client)	const;
		bool		isChanop(Client* client)	const;
		bool		isInvite(Client* client)	const;

		bool		isInviteOnly()	const;
		bool		setInviteOnly(bool state);

		std::string	getTopic()						const;
		void		setTopic(const std::string& str);
		bool		isTopicProtected()				const;
		bool		setTopicProtected(bool state);

		std::string	getKey()							const;
		void		setKey(std::string key);
		bool		isKeyProtected()					const;
		bool		access(const std::string &pwd)		const;

		int			getLimit()				const;
		void		setLimit(int limit);
		bool		isLimit()				const;
		bool		isFull()				const;

		std::string	getFlagString(bool inChan = true)	const;

		const std::map<const Client *, int>	&getGameBoard(void)	const;
		void							addNewPlayers(void);
		void							addPoints(int toAdd);
		void							removePlayer(const Client *toRm);

	private:
		Server*						_server;
		std::string					_name;
		std::vector<Client*>		_clients;
		std::vector<Client*>		_chanops;
		std::vector<Client*>		_invites;
		bool						_inviteOnly;
		std::string					_topic;
		bool						_topicProtected;
		std::string					_key;
		int							_limit;
		std::map<const Client *, int>		_gameBoard;
};

#endif //CHANNEL_H

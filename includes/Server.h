#ifndef SERVER_H
# define SERVER_H

class Server;
class Client;
class Channel;

# include <iostream>
# include <fcntl.h>
# include <algorithm>
# include <csignal>
# include <unistd.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netdb.h>
# include <cerrno>
# include <map>
# include <arpa/inet.h>
# include <poll.h>
# include <vector>

# include <Channel.h>
# include <Client.h>
# include <Message.h>
# include <IRC_responses.h>

# ifndef DEBUG
#  define DEBUG 0
# endif

class Server {
public:
	Server();
	Server(int port = 8080, const std::string& password = "");
	~Server();
	Server(const Server &src);
	Server &operator=(const Server &src);

	void createServer();
	void runServer();

	static void	sendMessage(std::string msg, const Client& sender, const int to, const std::string& type);
	void		broadcast(const std::string& msg);
	void		removeClient(const int fd);

private:
	int								_port;
	std::string						_password;
	int								_socket;
	sockaddr_in						_addr;
	std::vector<pollfd>				_fds;
	std::map<int, Client>			_clients;
	std::map<std::string, Channel>	_channels;

	static int				_sig;

	void		acceptClient();
	void		handleClient(const pollfd &pollfd);

	static void sigHandler(int signal);
};

#endif //SERVER_H

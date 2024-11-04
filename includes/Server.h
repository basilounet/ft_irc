#ifndef SERVER_H
# define SERVER_H

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

# ifndef DEBUG
#  define DEBUG 0
# endif

class Server {
public:
	Server(int port = 8080, const std::string& password = "");
	~Server();
	Server(const Server &src);
	Server &operator=(const Server &src);

	void createServer();
	void runServer();

private:
	int						_port;
	std::string				_password;
	int						_socket;
	sockaddr_in				_addr;
	std::vector<pollfd>		_fds;
	std::map<int, Client>	_clients;
	std::map<int, Channel>	_channels;

	static int				_sig;

	void		acceptClient();
	void		handleClient(const pollfd &fd, const size_t i);
	void		sendMessage(std::string msg, const int fd);
	void		sendMessage(const char *msg, const int fd);

	static void sigHandler(int signal);
};

#endif //SERVER_H

#include <Server.h>
#include <cstdlib>

int	main(int ac, char **av)
{
	if (ac != 3) {
		std::cerr << "\033[31mUsage: ./server port password\033[0m" << std::endl;
		return (1);
	}
	srand(time(__nullptr));
	Server server(std::atoi(av[1]), av[2]);
	try
	{
		server.createServer();
		server.runServer();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}
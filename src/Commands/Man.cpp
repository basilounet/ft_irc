//
// Created by bvasseur on 11/15/24.
//

#include "Man.h"

Man::Man() {
}

Man::Man(Man const& src) {
	*this = src;
}

Man::~Man() {
}

Man& Man::operator=(Man const& other) {
	ACommand::operator=(other);
	return (*this);
}

// MAN <Command>
void	Man::process(const Message& msg) {
	std::vector<std::string>	params = msg.getParams();
	std::vector<std::string>	splittedCmds;
	t_cmd						cmdId = BOT;

	if (params.empty())
	{
		//371	RPL_INFO					":<string>"
		Server::sendMessage(RPL_INFO(msg.prefix(1), "Manual entries:"), msg.getFd());
		Server::sendMessage(RPL_INFO(msg.prefix(1), "Bot"), msg.getFd());
		Server::sendMessage(RPL_INFO(msg.prefix(1), "Invite"), msg.getFd());
		Server::sendMessage(RPL_INFO(msg.prefix(1), "Join"), msg.getFd());
		Server::sendMessage(RPL_INFO(msg.prefix(1), "Kick"), msg.getFd());
		Server::sendMessage(RPL_INFO(msg.prefix(1), "Mode"), msg.getFd());
		Server::sendMessage(RPL_INFO(msg.prefix(1), "Nick"), msg.getFd());
		Server::sendMessage(RPL_INFO(msg.prefix(1), "Part"), msg.getFd());
		Server::sendMessage(RPL_INFO(msg.prefix(1), "Pass"), msg.getFd());
		Server::sendMessage(RPL_INFO(msg.prefix(1), "Privmsg"), msg.getFd());
		Server::sendMessage(RPL_INFO(msg.prefix(1), "Quit"), msg.getFd());
		Server::sendMessage(RPL_INFO(msg.prefix(1), "Topic"), msg.getFd());
		Server::sendMessage(RPL_INFO(msg.prefix(1), "User"), msg.getFd());
	}
	for (std::vector<std::string>::iterator it = params.begin() ;
			it != params.end() ; it++)
	{
		splittedCmds = split(*it, ',', msg);
		for (std::vector<std::string>::iterator cmd = splittedCmds.begin() ;
				cmd != splittedCmds.end() ; cmd++)
		{
			try
			{
				for (std::string::iterator ch = cmd->begin() ; ch != cmd->end() ;
						ch++)
					*ch = std::toupper(*ch);
				cmdId = findCmd(*cmd); // throw if unknown command
				displayMan(msg, cmdId);
			}
			catch (std::exception &e)
			{
				std::cout << C_ROUGE << "Error man: " << e.what() << C_RESET 
					<< std::endl;
			}
		}
	}
}

void	Man::displayMan(const Message& msg, t_cmd cmdId)
{
	switch (cmdId)
	{
		case BOT:
			Server::sendMessage(RPL_INFO(msg.prefix(1), "Bot:"), msg.getFd());
			Server::sendMessage(RPL_INFO(msg.prefix(1), MAN_BOT), msg.getFd());
			break ;
		case INVITE:
			Server::sendMessage(RPL_INFO(msg.prefix(1), "Invite:"), msg.getFd());
			Server::sendMessage(RPL_INFO(msg.prefix(1), MAN_INVITE), msg.getFd());
			break ;
		case JOIN:
			Server::sendMessage(RPL_INFO(msg.prefix(1), "Join:"), msg.getFd());
			Server::sendMessage(RPL_INFO(msg.prefix(1), MAN_JOIN), msg.getFd());
			break ;
		case KICK:
			Server::sendMessage(RPL_INFO(msg.prefix(1), "Kick:"), msg.getFd());
			Server::sendMessage(RPL_INFO(msg.prefix(1), MAN_KICK), msg.getFd());
			break ;
		case MODE:
			Server::sendMessage(RPL_INFO(msg.prefix(1), "Mode:"), msg.getFd());
			Server::sendMessage(RPL_INFO(msg.prefix(1), MAN_MODE), msg.getFd());
			break ;
		case NICK:
			Server::sendMessage(RPL_INFO(msg.prefix(1), "Nick:"), msg.getFd());
			Server::sendMessage(RPL_INFO(msg.prefix(1), MAN_NICK), msg.getFd());
			break ;
		case PART:
			Server::sendMessage(RPL_INFO(msg.prefix(1), "Part:"), msg.getFd());
			Server::sendMessage(RPL_INFO(msg.prefix(1), MAN_PART), msg.getFd());
			break ;
		case PASS:
			Server::sendMessage(RPL_INFO(msg.prefix(1), "Pass:"), msg.getFd());
			Server::sendMessage(RPL_INFO(msg.prefix(1), MAN_PASS), msg.getFd());
			break ;
		case PRIVMSG:
			Server::sendMessage(RPL_INFO(msg.prefix(1), "Privmsg:"), msg.getFd());
			Server::sendMessage(RPL_INFO(msg.prefix(1), MAN_PRIVMSG), msg.getFd());
			break ;
		case QUIT:
			Server::sendMessage(RPL_INFO(msg.prefix(1), "Quit:"), msg.getFd());
			Server::sendMessage(RPL_INFO(msg.prefix(1), MAN_QUIT), msg.getFd());
			break ;
		case TOPIC:
			Server::sendMessage(RPL_INFO(msg.prefix(1), "Topic:"), msg.getFd());
			Server::sendMessage(RPL_INFO(msg.prefix(1), MAN_TOPIC), msg.getFd());
			break ;
		case USER:
			Server::sendMessage(RPL_INFO(msg.prefix(1), "User:"), msg.getFd());
			Server::sendMessage(RPL_INFO(msg.prefix(1), MAN_USER), msg.getFd());
			break ;
		default:
			std::cout << C_ROUGE << "Man: " << "no entry for command"
				<< C_RESET << std::endl;
	}
}

ACommand	*Man::clone(void) const {
	return new Man();
}

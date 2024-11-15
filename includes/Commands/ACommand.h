#pragma once

# include <string>
# include <Message.h>

class ACommand
{
	public:
		ACommand(void);
		ACommand(std::vector<std::string> &params);
		ACommand(const ACommand &src);
		ACommand	&operator=(const ACommand &right);
		virtual	~ACommand(void);

		virtual void executeCommand(const Message& msg) = 0;

	protected:
		std::vector<std::string>	_params;
};

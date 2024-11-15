#pragma once

class Command
{
	public:
		Command(void);
		Command(std::vector<std::string> &params);
		Command(const Command &src);
		Command	&operator=(const Command &right);
		virtual	~Command(void);
	
	private:
		std::vector<std::string>	_params;
};

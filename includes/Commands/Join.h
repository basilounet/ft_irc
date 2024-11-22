//
// Created by bvasseur on 11/15/24.
//

#ifndef JOIN_H
#define JOIN_H

# include <ACommand.h>

class Join : public ACommand {
public:
	Join( void );
	Join(Join const &src);
	~Join( void );
	Join &operator=(Join const &other);

	void		process(const Message& msg);
	ACommand	*clone(void) const;

private:
	std::vector<std::string>	_channels;
	std::vector<std::string>	_pswds;

	std::vector<std::string>	split(const std::string& str, const char separator);
	bool						isNameValid(const std::string& name) const;
	void						tryJoinExistingChannel(const Message& msg, size_t i);
	void						CreateChannel(const Message& msg, size_t i);
};


#endif //JOIN_H

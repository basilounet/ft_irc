//
// Created by bvasseur on 11/15/24.
//

#ifndef NICK_H
#define NICK_H

# include <ACommand.h>
# include <iostream>

class Nick : public ACommand {
	public:
		Nick( void );
		Nick(Nick const &src);
		~Nick( void );
		Nick &operator=(Nick const &other);

		void		process(const Message& msg);
		ACommand	*clone(void)							const;
		static bool	isNickInServer(const std::string& nick, const Message &msg);

	private:
		bool	hasInvalidCharacter(const std::string& str);
		bool	isSpecialChar(const int ch);
};

#endif //NICK_H

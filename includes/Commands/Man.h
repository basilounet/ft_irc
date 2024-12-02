//
// Created by bvasseur on 11/15/24.
//

#ifndef MAN_H
# define MAN_H

# include <ACommand.h>

# define MAN_INVITE ""
# define MAN_JOIN ""
# define MAN_KICK ""
# define MAN_MODE ""
# define MAN_NICK "Sets the user nickname in parameter. The nickname is used for all commands targeting a user. It must be less than nine characters, only alphanumeric or '_'. The nickname can be the same as another registered user. The NICK command is required for registration process and cannot be processed if PASS have not be done before."
# define MAN_PART ""
# define MAN_PASS "Sets the user connection password to be tried in registration in parameter. The registration must be done by completing PASS, NICK and USER commands, and then the server will check if the given password matches the server one. The PASS command can be redone and doing will reset the user connection password. The command cannot be processed if user is already registered."
# define MAN_PRIVMSG "Sends a message to recipients. The recipients are given in the first parameter and must be separated by ','. If the recipient is another user, its nickname must be given. If the recipient is a channel, its first character must be '#' or '&' and the message will be send to all users in the channel apart from the sender. The message is given in trailing or second parameter."
# define MAN_QUIT "Terminates connection between user and server. A message to be send to everyone in user's channels can be given in trailing or parameter."
# define MAN_USER "Defines the user name (first parameter) and realname (trailing or last parameter). There is no restrictions to them. The command must be called after a PASS and a NICK call. Then it tries to register the user, if it fails the user must redo the registration process from the beginning. The command cannot be processed if user is already registered."

class Man : public ACommand {

	public:
		Man();
		Man(Man const &src);
		~Man();
		Man &operator=(Man const &other);

		void		process(const Message& msg);
		void		displayMan(const Message& msg, t_cmd cmdId);

		ACommand	*clone() const;
};

#endif //MAN_H

//
// Created by bvasseur on 11/15/24.
//

#ifndef MAN_H
# define MAN_H

# include <ACommand.h>

# define MAN_BOT "Bot de roulette russe \nBOT russianRoulette | rr <channel> : Lance la roulette russe sur le channel, kick le perdant. \nBOT shop|s [<channel>] : Montre le shop disponible \nBOT buy|b <upgrade> <channel> [<amount>] : Achete n ameliorations de <upgrade> \nBOT leaderboard|lb <channel> : Affiche le leaderboard contenant les points des joueurs du channel \nBOT stats <channel> : Affiche les statistiques du joueur dans le channel <channel>"

# define MAN_INVITE "The INVITE message is used to invite users to a channel. \nThe parameter <nickname> is the nickname of the person to be invited to	the target channel <channel>. \nThere is no requirement that the channel the target user is being invited to must exist or be a valid channel. \nTo invite a user to a channel which is invite only (MODE +i), the client sending the invite must be recognised as being a channel operator on the given channel."

# define MAN_JOIN "The JOIN command is used by a user to request to start listening to the specific channel. \nOnce a user has joined a channel, he receives information about all commands his server receives affecting the channel. \nThis includes JOIN, MODE, KICK, PART, QUIT and of course PRIVMSG/NOTICE. \nThis allows channel members to keep track of the other channel members, as well as channel modes."

# define MAN_KICK "The KICK command can be used to request the forced removal of a user from a channel. \nIt causes the <user> to PART from the <channel> by force. \nFor the message to be syntactically correct, there MUST be either one channel parameter and multiple user parameter, or as many channel parameters as there are user parameters. \nIf a comment is given, this will be sent instead of the default message, the nickname of the user issuing the KICK."

# define MAN_MODE "The MODE command is provided so that channel operators may change the characteristics of their channel. \nThe various modes available for channels are as follows: \n    o - give/take channel operator privileges, \n    i - invite-only channel flag, \n    t - topic settable by channel operator only flag, \n    l - set the user limit to channel"

# define MAN_NICK "Sets the user nickname in parameter. The nickname is used for all commands targeting a user. \nIt must be less than nine characters, only alphanumeric or _. \nThe nickname can be the same as another registered user. \nThe NICK command is required for registration process and cannot be processed if PASS have not be done before."

# define MAN_PART "The PART command causes the user sending the message to be removed from the list of active members for all given channels listed in the parameter string. \nIf a Part Message is given, this will be sent instead of the default message, the nickname. \nThis request is always granted by the server."

# define MAN_PASS "Sets the user connection password to be tried in registration in parameter. \nThe registration must be done by completing PASS, NICK and USER commands, and then the server will check if the given password matches the server one. \nThe PASS command can be redone and doing will reset the user connection password. \nThe command cannot be processed if user is already registered."

# define MAN_PRIVMSG "Sends a message to recipients. The recipients are given in the first parameter and must be separated by ,. \nIf the recipient is another user, its nickname must be given. \nIf the recipient is a channel, its first character must be # or & and the message will be send to all users in the channel apart from the sender. \nThe message is given in trailing or second parameter."

# define MAN_QUIT "Terminates connection between user and server. \nA message to be send to everyone in user's channels can be given in trailing or parameter."

# define MAN_TOPIC "The TOPIC message is used to change or view the topic of a channel. \nThe topic for channel <channel> is returned if there is no <topic> given. \nIf the <topic> parameter is present, the topic for that channel will be changed, if the channel modes permit this action."

# define MAN_USER "Defines the user name (first parameter) and realname (trailing or last parameter). \nThere is no restrictions to them. \nThe command must be called after a PASS and a NICK call. \nThen it tries to register the user, if it fails the user must redo the registration process from the beginning. \nThe command cannot be processed if user is already registered."

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

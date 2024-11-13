#pragma once

# define SERVER_NAME "irc.cri"
# define PREFIX ":" + SERVER_NAME
# define CRLF "\r\n"

# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// COMMAMD REPONSES

// 001   RPL_WELCOME				"Welcome to the Internet Relay Network <nick>!<user>@<host>"
# define RPL_WELCOME(nickRes, nick, user, host) \
PREFIX + " 001 " + nickRes + " " + nick + " :Welcome to the Internet Relay Network " + nick + "!" + user + "@" + host + CRLF

// 221   RPL_UMODEIS				"<user mode string>"
# define RPL_UMODEIS(nickRes, user_mode_string) \
PREFIX + " 221 " + nickRes + " " + user_mode_string + CRLF

// 300   RPL_NONE	

// 301   RPL_AWAY					"<nick> :<away message>"
# define RPL_AWAY(nickRes, nick, away_message) \
PREFIX + " 301 " + nickRes + " " + nick + " :" + away_message + CRLF

// 322   RPL_LIST					"<channel> <# visible> :<topic>"
# define RPL_LIST(nickRes, channel, visible, topic) \
PREFIX + " 322 " + nickRes + " " + channel + " " + visible + " :" + topic + CRLF

// 323   RPL_LISTEND				":End of LIST"
# define RPL_LISTEND(nickRes, user_mode_string) \
PREFIX + " 323 " + nickRes + " :End of LIST" + CRLF

// 324   RPL_CHANNELMODEIS			"<channel> <mode> <mode params>"
# define RPL_CHANNELMODEIS(nickRes, channel, mode, mode_params) \
PREFIX + " 324 " + nickRes + " " + channel + " " + mode + " " + mode_params + CRLF

// 325   RPL_UNIQOPIS				"<channel> <nickname>"
# define RPL_UNIQOPIS(nickRes, channel, nickname) \
PREFIX + " 325 " + nickRes + " " + channel + " " + nickname + CRLF

// 331   RPL_NOTOPIC				"<channel> :No topic is set"
# define RPL_NOTOPIC(nickRes, channel) \
PREFIX + " 331 " + nickRes + " " + channel + " :No topic is set" + CRLF

// 332   RPL_TOPIC					"<channel> :<topic>"
# define RPL_TOPIC(nickRes, channel, topic) \
PREFIX + " 332 " + nickRes + " " + channel + " :" + topic + CRLF

// 341   RPL_INVITING				"<channel> <nick>"
# define RPL_INVITING(nickRes, channel, nick) \
PREFIX + " 341 " + nickRes + " " + channel + " " + nick + CRLF

// 346   RPL_INVITELIST				"<channel> <invitemask>"
# define RPL_INVITELIST(nickRes, channel, invitemask) \
PREFIX + " 346 " + nickRes + " " + channel + " " + invitemask + CRLF

// 347   RPL_ENDOFINVITELIST		"<channel> :End of channel invite list"
# define RPL_ENDOFINVITELIST(nickRes, channel) \
PREFIX + " 347 " + nickRes + " " + channel + " :End of channel invite list" + CRLF

// 348   RPL_EXCEPTLIST				"<channel> <exceptionmask>"
# define RPL_EXCEPTLIST(nickRes, channel, exceptionmask) \
PREFIX + " 348 " + nickRes + " " + channel + " " + exceptionmask + CRLF

// 349   RPL_ENDOFEXCEPTLIST		"<channel> :End of channel exception list"
# define RPL_ENDOFEXCEPTLIST(nickRes, channel) \
PREFIX + " 349 " + nickRes + " " + channel + " :End of channel exception list" + CRLF

// 353   RPL_NAMREPLY				"( "=" / "*" / "@" ) <channel>
# define RPL_NAMREPLY(nickRes, name, channel) \
PREFIX + " 353 " + nickRes + " " + name + " " + channel + CRLF

// 366   RPL_ENDOFNAMES				"<channel> :End of NAMES list"
# define RPL_ENDOFNAMES(nickRes, channel) \
PREFIX + " 366 " + nickRes + " " + channel + " :End of NAMES list" + CRLF

// 367   RPL_BANLIST				"<channel> <banmask>"
# define RPL_BANLIST(nickRes, channel, banmask) \
PREFIX + " 367 " + nickRes + " " + channel + " " + banmask + CRLF

// 368   RPL_ENDOFBANLIST			"<channel> :End of channel ban list"
# define RPL_ENDOFBANLIST(nickRes, channel) \
PREFIX + " 368 " + nickRes + " " + channel + " :End of channel ban list" + CRLF


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ERROR REPLIES

// 401   ERR_NOSUCHNICK				"<nickname> :No such nick/channel"
# define ERR_NOSUCHNICK(nickRes, nickname) \
PREFIX + " 401 " + nickRes + " " + nickname + " :No such nick/channel" + CRLF

// 402   ERR_NOSUCHSERVER			"<servername> :No such server"
# define ERR_NOSUCHSERVER(nickRes, servername) \
PREFIX + " 402 " + nickRes + " " + servername + " :No such server" + CRLF

// 403   ERR_NOSUCHCHANNEL			"<channelname> :No such channel"
# define ERR_NOSUCHCHANNEL(nickRes, channelname) \
PREFIX + " 403 " + nickRes + " " + channelname + " :No such channel" + CRLF

// 404   ERR_CANNOTSENDTOCHAN		"<channelname> :Cannot send to channel"
# define ERR_CANNOTSENDTOCHAN(nickRes, channelname) \
PREFIX + " 404 " + nickRes + " " + channelname + " :Cannot send to channel" + CRLF

// 405   ERR_TOOMANYCHANNELS		"<channelname> :You have joined too many channels"
# define ERR_TOOMANYCHANNELS(nickRes, channelname) \
PREFIX + " 405 " + nickRes + " " + channelname + " :You have joined too many channels" + CRLF

// 407   ERR_TOOMANYTARGETS			"<target> :<error> recipients. <message>"
# define ERR_TOOMANYTARGETS(nickRes, target, error, message) \
PREFIX + " 407 " + nickRes + " " + target + " :" + error + "recipients. " + message + CRLF

// 411   ERR_NORECIPIENT			":No recipient given (<command>)"
# define ERR_NORECIPIENT(nickRes, command) \
PREFIX + " 411 " + nickRes + " :No recipient given (" + command + ")" + CRLF

// 412   ERR_NOTEXTTOSEND			":No text to send"
# define ERR_NOTEXTTOSEND(nickRes) \
PREFIX + " 412 " + nickRes + " :No text to send" + CRLF

// 413   ERR_NOTOPLEVEL				"<mask> :No toplevel domain specified"
# define ERR_NOTOPLEVEL(nickRes, mask) \
PREFIX + " 413 " + nickRes + " " + mask + " :No toplevel domain specified" + CRLF

// 414   ERR_WILDTOPLEVEL			"<mask> :Wildcard in toplevel domain"
# define ERR_WILDTOPLEVEL(nickRes, mask) \
PREFIX + " 414 " + nickRes + " " + mask + " :Wildcard in toplevel domain" + CRLF

// 421	  ERR_UNKNOWNCOMMAND		"<command> :Unknown command"
# define ERR_UNKNOWNCOMMAND(nickRes, command) \
PREFIX + " 421 " + nickRes + " " + command + " :Unknown command" + CRLF

// 431   ERR_NONICKNAMEGIVEN		":No nickname given"
# define ERR_NONICKNAMEGIVEN(nickRes) \
PREFIX + " 431 " + nickRes + " :No nickname given" + CRLF

// 432   ERR_ERRONEUSNICKNAME	 	"<nick> :Erroneous nickname"
# define ERR_ERRONEUSNICKNAME(nickRes, nick) \
PREFIX + " 432 " + nickRes + " " + nick + " :Erroneous nickname" + CRLF

// 433   ERR_NICKNAMEINUSE			"<nick> :Nickname is already in use"
# define ERR_NICKNAMEINUSE(nickRes, nick) \
PREFIX + " 433 " + nickRes + " " + nick + " :Nickname is already in use" + CRLF

// 436   ERR_NICKCOLLISION			"<nick> :Nickname collision KILL from <user>@<host>"
# define ERR_NICKCOLLISION(nickRes, nick, user, host) \
PREFIX + " 436 " + nickRes + " " + nick + " :Nickname collision KILL from " + user + "@" + host + CRLF

// 437   ERR_UNAVAILRESOURCE		"<nick_channel> :Nick/channel is temporarily unavailable"
# define ERR_UNAVAILRESOURCE(nickRes, nick_channel) \
PREFIX + " 437 " + nickRes + " " + nick_channel + " :Nick/channel is temporarily unavailable" + CRLF

// 441   ERR_USERNOTINCHANNEL		"<nick> <channel> :They aren't on that channel"
# define ERR_USERNOTINCHANNEL(nickRes, nick, channel) \
PREFIX + " 441 " + nickRes + " " + nick + " " + channel + " :They aren't on that channel" + CRLF

// 442   ERR_NOTONCHANNEL			"<channel> :You're not on that channel"
# define ERR_NOTONCHANNEL(nickRes, channel) \
PREFIX + " 442 " + nickRes + " " + channel + " :You're not on that channel" + CRLF

// 443   ERR_USERONCHANNE			"<user> <channel> :is already on channel"
# define ERR_USERONCHANNE(nickRes, nick, channel) \
PREFIX + " 443 " + nickRes + " " + nick + " " + channel + " :is already on channel" + CRLF

// 461   ERR_NEEDMOREPARAMS			"<command> :Not enough parameters"
# define ERR_NEEDMOREPARAMS(nickRes, command) \
PREFIX + " 461 " + nickRes + " " + command + " :Not enough parameters" + CRLF

// 462	 ERR_ALREADYREGISTRED		":Unauthorized command (already registered)"
# define ERR_ALREADYREGISTRED(nickRes) \
PREFIX + " 462 " + nickRes + " :Unauthorized command (already registered)" + CRLF

// 464   ERR_PASSWDMISMATCH			":Password incorrect"
# define ERR_PASSWDMISMATCH(nickRes) \
PREFIX + " 464 " + nickRes + " :Password incorrect" + CRLF

// 467   ERR_KEYSET					"<channel> :Channel key already set"
# define ERR_KEYSET(nickRes, channel) \
PREFIX + " 467 " + nickRes + " " + channel + " :Channel key already set" + CRLF

// 471   ERR_CHANNELISFULL			"<channel> :Cannot join channel (+l)"
# define ERR_CHANNELISFULL(nickRes, channel) \
PREFIX + " 471 " + nickRes + " " + channel + " :Cannot join channel (+l)" + CRLF

// 472   ERR_UNKNOWNMODE			"<char> :is unknown mode char to me for <channel>"
# define ERR_UNKNOWNMODE(nickRes, char, channel) \
PREFIX + " 472 " + nickRes + " " + nick + " " + char + " :is unknown mode char to me for" + channel + CRLF

// 473   ERR_INVITEONLYCHAN			"<channel> :Cannot join channel (+i)"
# define ERR_INVITEONLYCHAN(nickRes, channel) \
PREFIX + " 473 " + nickRes + " " + channel + " :Cannot join channel (+i)" + CRLF

// 474   ERR_BANNEDFROMCHAN			"<channel> :Cannot join channel (+b)"
# define ERR_BANNEDFROMCHAN(nickRes, channel) \
PREFIX + " 474 " + nickRes + " " + channel + " :Cannot join channel (+b)" + CRLF

// 475   ERR_BADCHANNELKEY			"<channel> :Cannot join channel (+k)"
# define ERR_BADCHANNELKEY(nickRes, channel) \
PREFIX + " 475 " + nickRes + " " + channel + " :Cannot join channel (+k)" + CRLF

// 476   ERR_BADCHANMASK			"<channel> :Bad Channel Mask"
# define ERR_BADCHANMASK(nickRes, channel) \
PREFIX + " 476 " + nickRes + " " + channel + " :Bad Channel Mask" + CRLF

// 477   ERR_NOCHANMODES			"<channel> :Channel doesn't support modes"
# define ERR_NOCHANMODES(nickRes, channel) \
PREFIX + " 477 " + nickRes + " " + channel + " :Channel doesn't support modes" + CRLF

// 482   ERR_CHANOPRIVSNEEDED		"<channel> :You're not channel operator"
# define ERR_CHANOPRIVSNEEDED(nickRes, channel) \
PREFIX + " 482 " + nickRes + " " + channel + " :You're not channel operator" + CRLF

// 484   ERR_RESTRICTED				":Your connection is restricted!"
# define ERR_RESTRICTED(nickRes) \
PREFIX + " 484 " + nickRes + " :Your connection is restricted!" + CRLF

// 491   ERR_NOOPERHOST				":No O-lines for your host"
# define ERR_NOOPERHOST(nickRes) \
PREFIX + " 491 " + nickRes + " :No O-lines for your host" + CRLF

// 501   ERR_UMODEUNKNOWNFLAG		":Unknown MODE flag"
# define ERR_UMODEUNKNOWNFLAG(nickRes) \
PREFIX + " 501 " + nickRes + " :Unknown MODE flag!" + CRLF

// 502   ERR_USERSDONTMATCH			":Cannot change mode for other users"
# define ERR_USERSDONTMATCH(nickRes) \
PREFIX + " 502 " + nickRes + " :Cannot change mode for other users" + CRLF

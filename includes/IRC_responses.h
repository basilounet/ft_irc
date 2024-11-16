#pragma once

# define HOST std::string("localhost")
# define SERVER_REAL_NAME std::string("irc.cri")
# define CRLF std::string("\r\n")

# define C_VERT "\e[38;5;40m"
# define C_ROUGE "\e[38;5;196m"
# define C_OR "\e[38;5;220m"
# define C_LIME "\e[38;5;121m"
# define C_ROSE "\e[38;5;217m"
# define C_RESET "\033[0m"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// COMMAMD REPONSES

// 001   RPL_WELCOME				"Welcome to the Internet Relay Network <nick>!<user>@<host>"
# define RPL_WELCOME(prefix, nickRes, nick, user, host) \
(std::string(prefix) + " 001 " + std::string(nickRes) + " " + std::string(nick) + " :Welcome to the Internet Relay Network " + std::string(nick) + "!" + std::string(user) + "@" + std::string(host) + CRLF)

// 221   RPL_UMODEIS				"<user mode string>"
# define RPL_UMODEIS(prefix, nickRes, user_mode_string) \
(std::string(prefix) + " 221 " + std::string(nickRes) + " " + std::string(user_mode_string) + CRLF)

// 300   RPL_NONE	

// 301   RPL_AWAY					"<nick> :<away message>"
# define RPL_AWAY(prefix, nickRes, nick, away_message) \
(std::string(prefix) + " 301 " + std::string(nickRes) + " " + std::string(nick) + " :" + std::string(away_message) + CRLF)

// 322   RPL_LIST					"<channel> <# visible> :<topic>"
# define RPL_LIST(prefix, nickRes, channel, visible, topic) \
(std::string(prefix) + " 322 " + std::string(nickRes) + " " + std::string(channel) + " " + std::string(visible) + " :" + std::string(topic) + CRLF)

// 323   RPL_LISTEND				":End of LIST"
# define RPL_LISTEND(prefix, nickRes, user_mode_string) \
(std::string(prefix) + " 323 " + std::string(nickRes) + " :End of LIST" + CRLF)

// 324   RPL_CHANNELMODEIS			"<channel> <mode> <mode params>"
# define RPL_CHANNELMODEIS(prefix, nickRes, channel, mode, mode_params) \
(std::string(prefix) + " 324 " + std::string(nickRes) + " " + std::string(channel) + " " + std::string(mode) + " " + std::string(mode_params) + CRLF)

// 325   RPL_UNIQOPIS				"<channel> <nickname>"
# define RPL_UNIQOPIS(prefix, nickRes, channel, nickname) \
(std::string(prefix) + " 325 " + std::string(nickRes) + " " + std::string(channel) + " " + std::string(nickname) + CRLF)

// 331   RPL_NOTOPIC				"<channel> :No topic is set"
# define RPL_NOTOPIC(prefix, nickRes, channel) \
(std::string(prefix) + " 331 " + std::string(nickRes) + " " + std::string(channel) + " :No topic is set" + CRLF)

// 332   RPL_TOPIC					"<channel> :<topic>"
# define RPL_TOPIC(prefix, nickRes, channel, topic) \
(std::string(prefix) + " 332 " + std::string(nickRes) + " " + std::string(channel) + " :" + std::string(topic) + CRLF)

// 341   RPL_INVITING				"<channel> <nick>"
# define RPL_INVITING(prefix, nickRes, channel, nick) \
(std::string(prefix) + " 341 " + std::string(nickRes) + " " + std::string(channel) + " " + std::string(nick) + CRLF)

// 346   RPL_INVITELIST				"<channel> <invitemask>"
# define RPL_INVITELIST(prefix, nickRes, channel, invitemask) \
(std::string(prefix) + " 346 " + std::string(nickRes) + " " + std::string(channel) + " " + std::string(invitemask) + CRLF)

// 347   RPL_ENDOFINVITELIST		"<channel> :End of channel invite list"
# define RPL_ENDOFINVITELIST(prefix, nickRes, channel) \
(std::string(prefix) + " 347 " + std::string(nickRes) + " " + std::string(channel) + " :End of channel invite list" + CRLF)

// 348   RPL_EXCEPTLIST				"<channel> <exceptionmask>"
# define RPL_EXCEPTLIST(prefix, nickRes, channel, exceptionmask) \
(std::string(prefix) + " 348 " + std::string(nickRes) + " " + std::string(channel) + " " + std::string(exceptionmask) + CRLF)

// 349   RPL_ENDOFEXCEPTLIST		"<channel> :End of channel exception list"
# define RPL_ENDOFEXCEPTLIST(prefix, nickRes, channel) \
(std::string(prefix) + " 349 " + std::string(nickRes) + " " + std::string(channel) + " :End of channel exception list" + CRLF)

// 353   RPL_NAMREPLY				"( "=" / "*" / "@" ) <channel>
# define RPL_NAMREPLY(prefix, nickRes, name, channel) \
(std::string(prefix) + " 353 " + std::string(nickRes) + " " + std::string(name) + " " + std::string(channel) + CRLF)

// 366   RPL_ENDOFNAMES				"<channel> :End of NAMES list"
# define RPL_ENDOFNAMES(prefix, nickRes, channel) \
(std::string(prefix) + " 366 " + std::string(nickRes) + " " + std::string(channel) + " :End of NAMES list" + CRLF)

// 367   RPL_BANLIST				"<channel> <banmask>"
# define RPL_BANLIST(prefix, nickRes, channel, banmask) \
(std::string(prefix) + " 367 " + std::string(nickRes) + " " + std::string(channel) + " " + std::string(banmask) + CRLF)

// 368   RPL_ENDOFBANLIST			"<channel> :End of channel ban list"
# define RPL_ENDOFBANLIST(prefix, nickRes, channel) \
(std::string(prefix) + " 368 " + std::string(nickRes) + " " + std::string(channel) + " :End of channel ban list" + CRLF)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ERROR REPLIES

// 401   ERR_NOSUCHNICK				"<nickname> :No such nick/channel"
# define ERR_NOSUCHNICK(prefix, nickRes, nickname) \
(std::string(prefix) + " 401 " + std::string(nickRes) + " " std::string(nickname) + " :No such nick/channel" + CRLF)

// 402   ERR_NOSUCHSERVER			"<servername> :No such server"
# define ERR_NOSUCHSERVER(prefix, nickRes, servername) \
(std::string(prefix) + " 402 " + std::string(nickRes) + " " + std::string(servername) + " :No such server" + CRLF)

// 403   ERR_NOSUCHCHANNEL			"<channel> :No such channel"
# define ERR_NOSUCHCHANNEL(prefix, nickRes, channel) \
(std::string(prefix) + " 403 " + std::string(nickRes) + " " + std::string(channel) + " :No such channel" + CRLF)

// 404   ERR_CANNOTSENDTOCHAN		"<channel> :Cannot send to channel"
# define ERR_CANNOTSENDTOCHAN(prefix, nickRes, channel) \
(std::string(prefix) + " 404 " + std::string(nickRes) + " " + std::string(channel) + " :Cannot send to channel" + CRLF)

// 405   ERR_TOOMANYCHANNELS		"<channel> :You have joined too many channels"
# define ERR_TOOMANYCHANNELS(prefix, nickRes, channel) \
(std::string(prefix) + " 405 " + std::string(nickRes) + " " + std::string(channel) + " :You have joined too many channels" + CRLF)

// 407   ERR_TOOMANYTARGETS			"<target> :<error> recipients. <message>"
# define ERR_TOOMANYTARGETS(prefix, nickRes, target, error, message) \
(std::string(prefix) + " 407 " + std::string(nickRes) + " " + std::string(target) + " :" + std::string(error) + "recipients. " + std::string(message) + CRLF)

// 411   ERR_NORECIPIENT			":No recipient given (<command>)"
# define ERR_NORECIPIENT(prefix, nickRes, command) \
(std::string(prefix) + " 411 " + std::string(nickRes) + " :No recipient given (" + std::string(command) + ")" + CRLF)

// 412   ERR_NOTEXTTOSEND			":No text to send"
# define ERR_NOTEXTTOSEND(prefix, nickRes) \
(std::string(prefix) + " 412 " + std::string(nickRes) + " :No text to send" + CRLF)

// 413   ERR_NOTOPLEVEL				"<mask> :No toplevel domain specified"
# define ERR_NOTOPLEVEL(prefix, nickRes, mask) \
(std::string(prefix) + " 413 " + std::string(nickRes) + " " + std::string(mask) + " :No toplevel domain specified" + CRLF)

// 414   ERR_WILDTOPLEVEL			"<mask> :Wildcard in toplevel domain"
# define ERR_WILDTOPLEVEL(prefix, nickRes, mask) \
(std::string(prefix) + " 414 " + std::string(nickRes) + " " + std::string(mask) + " :Wildcard in toplevel domain" + CRLF)

// 421	  ERR_UNKNOWNCOMMAND		"<command> :Unknown command"
# define ERR_UNKNOWNCOMMAND(prefix, nickRes, command) \
(std::string(prefix) + " 421 " + std::string(nickRes) + " " + std::string(command) + " :Unknown command" + CRLF)

// 431   ERR_NONICKNAMEGIVEN		":No nickname given"
# define ERR_NONICKNAMEGIVEN(prefix, nickRes) \
(std::string(prefix) + " 431 " + std::string(nickRes) + " :No nickname given" + CRLF)

// 432   ERR_ERRONEUSNICKNAME	 	"<nick> :Erroneous nickname"
# define ERR_ERRONEUSNICKNAME(prefix, nickRes, nick) \
(std::string(prefix) + " 432 " + std::string(nickRes) + " " + std::string(nick) + " :Erroneous nickname" + CRLF)

// 433   ERR_NICKNAMEINUSE			"<nick> :Nickname is already in use"
# define ERR_NICKNAMEINUSE(prefix, nickRes, nick) \
(std::string(prefix) + " 433 " + std::string(nickRes) + " " + std::string(nick) + " :Nickname is already in use" + CRLF)

// 436   ERR_NICKCOLLISION			"<nick> :Nickname collision KILL from <user>@<host>"
# define ERR_NICKCOLLISION(prefix, nickRes, nick, user, host) \
(std::string(prefix) + " 436 " + std::string(nickRes) + " " + std::string(nick) + " :Nickname collision KILL from " + std::string(user) + "@" + std::string(host) + CRLF)

// 437   ERR_UNAVAILRESOURCE		"<nick_channel> :Nick/channel is temporarily unavailable"
# define ERR_UNAVAILRESOURCE(prefix, nickRes, nick_channel) \
(std::string(prefix) + " 437 " + std::string(nickRes) + " " + std::string(nick_channel) + " :Nick/channel is temporarily unavailable" + CRLF)

// 441   ERR_USERNOTINCHANNEL		"<nick> <channel> :They aren't on that channel"
# define ERR_USERNOTINCHANNEL(prefix, nickRes, nick, channel) \
(std::string(prefix) + " 441 " + std::string(nickRes) + " " + std::string(nick) + " " + std::string(channel) + " :They aren't on that channel" + CRLF)

// 442   ERR_NOTONCHANNEL			"<channel> :You're not on that channel"
# define ERR_NOTONCHANNEL(prefix, nickRes, channel) \
(std::string(prefix) + " 442 " + std::string(nickRes) + " " + std::string(channel) + " :You're not on that channel" + CRLF)

// 443   ERR_USERONCHANNE			"<user> <channel> :is already on channel"
# define ERR_USERONCHANNE(prefix, nickRes, nick, channel) \
(std::string(prefix) + " 443 " + std::string(nickRes) + " " + std::string(nick) + " " + std::string(channel) + " :is already on channel" + CRLF)

// 461   ERR_NEEDMOREPARAMS			"<command> :Not enough parameters"
# define ERR_NEEDMOREPARAMS(prefix, nickRes, command) \
(std::string(prefix) + " 461 " + std::string(nickRes) + " " + std::string(command) + " :Not enough parameters" + CRLF)

// 462	 ERR_ALREADYREGISTRED		":Unauthorized command (already registered)"
# define ERR_ALREADYREGISTRED(prefix, nickRes) \
(std::string(prefix) + " 462 " + std::string(nickRes) + " :Unauthorized command (already registered)" + CRLF)

// 464   ERR_PASSWDMISMATCH			":Password incorrect"
# define ERR_PASSWDMISMATCH(prefix, nickRes) \
(std::string(prefix) + " 464 " + std::string(nickRes) + " :Password incorrect" + CRLF)

// 467   ERR_KEYSET					"<channel> :Channel key already set"
# define ERR_KEYSET(prefix, nickRes, channel) \
(std::string(prefix) + " 467 " + std::string(nickRes) + " " + std::string(channel) + " :Channel key already set" + CRLF)

// 471   ERR_CHANNELISFULL			"<channel> :Cannot join channel (+l)"
# define ERR_CHANNELISFULL(prefix, nickRes, channel) \
(std::string(prefix) + " 471 " + std::string(nickRes) + " " + std::string(channel) + " :Cannot join channel (+l)" + CRLF)

// 472   ERR_UNKNOWNMODE			"<char> :is unknown mode char to me for <channel>"
# define ERR_UNKNOWNMODE(prefix, nickRes, chara, channel) \
(std::string(prefix) + " 472 " + std::string(nickRes) + " " + std::string(chara) + " :is unknown mode char to me for" + std::string(channel) + CRLF)

// 473   ERR_INVITEONLYCHAN			"<channel> :Cannot join channel (+i)"
# define ERR_INVITEONLYCHAN(prefix, nickRes, channel) \
(std::string(prefix) + " 473 " + std::string(nickRes) + " " + std::string(channel) + " :Cannot join channel (+i)" + CRLF)

// 474   ERR_BANNEDFROMCHAN			"<channel> :Cannot join channel (+b)"
# define ERR_BANNEDFROMCHAN(prefix, nickRes, channel) \
(std::string(prefix) + " 474 " + std::string(nickRes) + " " + std::string(channel) + " :Cannot join channel (+b)" + CRLF)

// 475   ERR_BADCHANNELKEY			"<channel> :Cannot join channel (+k)"
# define ERR_BADCHANNELKEY(prefix, nickRes, channel) \
(std::string(prefix) + " 475 " + std::string(nickRes) + " " + std::string(channel) + " :Cannot join channel (+k)" + CRLF)

// 476   ERR_BADCHANMASK			"<channel> :Bad Channel Mask"
# define ERR_BADCHANMASK(prefix, nickRes, channel) \
(std::string(prefix) + " 476 " + std::string(nickRes) + " " + std::string(channel) + " :Bad Channel Mask" + CRLF)

// 477   ERR_NOCHANMODES			"<channel> :Channel doesn't support modes"
# define ERR_NOCHANMODES(prefix, nickRes, channel) \
(std::string(prefix) + " 477 " + std::string(nickRes) + " " + std::string(channel) + " :Channel doesn't support modes" + CRLF)

// 482   ERR_CHANOPRIVSNEEDED		"<channel> :You're not channel operator"
# define ERR_CHANOPRIVSNEEDED(prefix, nickRes, channel) \
(std::string(prefix) + " 482 " + std::string(nickRes) + " " + std::string(channel) + " :You're not channel operator" + CRLF)

// 484   ERR_RESTRICTED				":Your connection is restricted!"
# define ERR_RESTRICTED(prefix, nickRes) \
(std::string(prefix) + " 484 " + std::string(nickRes) + " :Your connection is restricted!" + CRLF)

// 491   ERR_NOOPERHOST				":No O-lines for your host"
# define ERR_NOOPERHOST(prefix, nickRes) \
(std::string(prefix) + " 491 " + std::string(nickRes) + " :No O-lines for your host" + CRLF)

// 501   ERR_UMODEUNKNOWNFLAG		":Unknown MODE flag"
# define ERR_UMODEUNKNOWNFLAG(prefix, nickRes) \
(std::string(prefix) + " 501 " + std::string(nickRes) + " :Unknown MODE flag!" + CRLF)

// 502   ERR_USERSDONTMATCH			":Cannot change mode for other users"
# define ERR_USERSDONTMATCH(prefix, nickRes) \
(std::string(prefix) + " 502 " + std::string(nickRes) + " :Cannot change mode for other users" + CRLF)

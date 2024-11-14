#pragma once

# define SERVER_NAME std::string("irc.cri")
# define PREFIX std::string(":" + SERVER_NAME)
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
# define RPL_WELCOME(nickRes, nick, user, host) \
(PREFIX + " 001 " + std::string(nickRes) + " " + std::string(nick) + " :Welcome to the Internet Relay Network " + std::string(nick) + "!" + std::string(user) + "@" + std::string(host) + CRLF)

// 221   RPL_UMODEIS				"<user mode string>"
# define RPL_UMODEIS(nickRes, user_mode_string) \
(PREFIX + " 221 " + std::string(nickRes) + " " + std::string(user_mode_string) + CRLF)

// 300   RPL_NONE	

// 301   RPL_AWAY					"<nick> :<away message>"
# define RPL_AWAY(nickRes, nick, away_message) \
(PREFIX + " 301 " + std::string(nickRes) + " " + std::string(nick) + " :" + std::string(away_message) + CRLF)

// 322   RPL_LIST					"<channel> <# visible> :<topic>"
# define RPL_LIST(nickRes, channel, visible, topic) \
(PREFIX + " 322 " + std::string(nickRes) + " " + std::string(channel) + " " + std::string(visible) + " :" + std::string(topic) + CRLF)

// 323   RPL_LISTEND				":End of LIST"
# define RPL_LISTEND(nickRes, user_mode_string) \
(PREFIX + " 323 " + std::string(nickRes) + " :End of LIST" + CRLF)

// 324   RPL_CHANNELMODEIS			"<channel> <mode> <mode params>"
# define RPL_CHANNELMODEIS(nickRes, channel, mode, mode_params) \
(PREFIX + " 324 " + std::string(nickRes) + " " + std::string(channel) + " " + std::string(mode) + " " + std::string(mode_params) + CRLF)

// 325   RPL_UNIQOPIS				"<channel> <nickname>"
# define RPL_UNIQOPIS(nickRes, channel, nickname) \
(PREFIX + " 325 " + std::string(nickRes) + " " + std::string(channel) + " " + std::string(nickname) + CRLF)

// 331   RPL_NOTOPIC				"<channel> :No topic is set"
# define RPL_NOTOPIC(nickRes, channel) \
(PREFIX + " 331 " + std::string(nickRes) + " " + std::string(channel) + " :No topic is set" + CRLF)

// 332   RPL_TOPIC					"<channel> :<topic>"
# define RPL_TOPIC(nickRes, channel, topic) \
(PREFIX + " 332 " + std::string(nickRes) + " " + std::string(channel) + " :" + std::string(topic) + CRLF)

// 341   RPL_INVITING				"<channel> <nick>"
# define RPL_INVITING(nickRes, channel, nick) \
(PREFIX + " 341 " + std::string(nickRes) + " " + std::string(channel) + " " + std::string(nick) + CRLF)

// 346   RPL_INVITELIST				"<channel> <invitemask>"
# define RPL_INVITELIST(nickRes, channel, invitemask) \
(PREFIX + " 346 " + std::string(nickRes) + " " + std::string(channel) + " " + std::string(invitemask) + CRLF)

// 347   RPL_ENDOFINVITELIST		"<channel> :End of channel invite list"
# define RPL_ENDOFINVITELIST(nickRes, channel) \
(PREFIX + " 347 " + std::string(nickRes) + " " + std::string(channel) + " :End of channel invite list" + CRLF)

// 348   RPL_EXCEPTLIST				"<channel> <exceptionmask>"
# define RPL_EXCEPTLIST(nickRes, channel, exceptionmask) \
(PREFIX + " 348 " + std::string(nickRes) + " " + std::string(channel) + " " + std::string(exceptionmask) + CRLF)

// 349   RPL_ENDOFEXCEPTLIST		"<channel> :End of channel exception list"
# define RPL_ENDOFEXCEPTLIST(nickRes, channel) \
(PREFIX + " 349 " + std::string(nickRes) + " " + std::string(channel) + " :End of channel exception list" + CRLF)

// 353   RPL_NAMREPLY				"( "=" / "*" / "@" ) <channel>
# define RPL_NAMREPLY(nickRes, name, channel) \
(PREFIX + " 353 " + std::string(nickRes) + " " + std::string(name) + " " + std::string(channel) + CRLF)

// 366   RPL_ENDOFNAMES				"<channel> :End of NAMES list"
# define RPL_ENDOFNAMES(nickRes, channel) \
(PREFIX + " 366 " + std::string(nickRes) + " " + std::string(channel) + " :End of NAMES list" + CRLF)

// 367   RPL_BANLIST				"<channel> <banmask>"
# define RPL_BANLIST(nickRes, channel, banmask) \
(PREFIX + " 367 " + std::string(nickRes) + " " + std::string(channel) + " " + std::string(banmask) + CRLF)

// 368   RPL_ENDOFBANLIST			"<channel> :End of channel ban list"
# define RPL_ENDOFBANLIST(nickRes, channel) \
(PREFIX + " 368 " + std::string(nickRes) + " " + std::string(channel) + " :End of channel ban list" + CRLF)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ERROR REPLIES

// 401   ERR_NOSUCHNICK				"<nickname> :No such nick/channel"
# define ERR_NOSUCHNICK(nickRes, nickname) \
(PREFIX + " 401 " + std::string(nickRes) + " " std::string(nickname) + " :No such nick/channel" + CRLF)

// 402   ERR_NOSUCHSERVER			"<servername> :No such server"
# define ERR_NOSUCHSERVER(nickRes, servername) \
(PREFIX + " 402 " + std::string(nickRes) + " " + servername + " :No such server" + CRLF)

// 403   ERR_NOSUCHCHANNEL			"<channelname> :No such channel"
# define ERR_NOSUCHCHANNEL(nickRes, channelname) \
(PREFIX + " 403 " + std::string(nickRes) + " " + channelname + " :No such channel" + CRLF)

// 404   ERR_CANNOTSENDTOCHAN		"<channelname> :Cannot send to channel"
# define ERR_CANNOTSENDTOCHAN(nickRes, channelname) \
(PREFIX + " 404 " + std::string(nickRes) + " " + channelname + " :Cannot send to channel" + CRLF)

// 405   ERR_TOOMANYCHANNELS		"<channelname> :You have joined too many channels"
# define ERR_TOOMANYCHANNELS(nickRes, channelname) \
(PREFIX + " 405 " + std::string(nickRes) + " " + channelname + " :You have joined too many channels" + CRLF)

// 407   ERR_TOOMANYTARGETS			"<target> :<error> recipients. <message>"
# define ERR_TOOMANYTARGETS(nickRes, target, error, message) \
(PREFIX + " 407 " + std::string(nickRes) + " " + std::string(target) + " :" + std::string(error) + "recipients. " + std::string(message) + CRLF)

// 411   ERR_NORECIPIENT			":No recipient given (<command>)"
# define ERR_NORECIPIENT(nickRes, command) \
(PREFIX + " 411 " + std::string(nickRes) + " :No recipient given (" + std::string(command) + ")" + CRLF)

// 412   ERR_NOTEXTTOSEND			":No text to send"
# define ERR_NOTEXTTOSEND(nickRes) \
(PREFIX + " 412 " + std::string(nickRes) + " :No text to send" + CRLF)

// 413   ERR_NOTOPLEVEL				"<mask> :No toplevel domain specified"
# define ERR_NOTOPLEVEL(nickRes, mask) \
(PREFIX + " 413 " + std::string(nickRes) + " " + std::string(mask) + " :No toplevel domain specified" + CRLF)

// 414   ERR_WILDTOPLEVEL			"<mask> :Wildcard in toplevel domain"
# define ERR_WILDTOPLEVEL(nickRes, mask) \
(PREFIX + " 414 " + std::string(nickRes) + " " + std::string(mask) + " :Wildcard in toplevel domain" + CRLF)

// 421	  ERR_UNKNOWNCOMMAND		"<command> :Unknown command"
# define ERR_UNKNOWNCOMMAND(nickRes, command) \
(PREFIX + " 421 " + std::string(nickRes) + " " + std::string(command) + " :Unknown command" + CRLF)

// 431   ERR_NONICKNAMEGIVEN		":No nickname given"
# define ERR_NONICKNAMEGIVEN(nickRes) \
(PREFIX + " 431 " + std::string(nickRes) + " :No nickname given" + CRLF)

// 432   ERR_ERRONEUSNICKNAME	 	"<nick> :Erroneous nickname"
# define ERR_ERRONEUSNICKNAME(nickRes, nick) \
(PREFIX + " 432 " + std::string(nickRes) + " " + std::string(nick) + " :Erroneous nickname" + CRLF)

// 433   ERR_NICKNAMEINUSE			"<nick> :Nickname is already in use"
# define ERR_NICKNAMEINUSE(nickRes, nick) \
(PREFIX + " 433 " + std::string(nickRes) + " " + std::string(nick) + " :Nickname is already in use" + CRLF)

// 436   ERR_NICKCOLLISION			"<nick> :Nickname collision KILL from <user>@<host>"
# define ERR_NICKCOLLISION(nickRes, nick, user, host) \
(PREFIX + " 436 " + std::string(nickRes) + " " + std::string(nick) + " :Nickname collision KILL from " + std::string(user) + "@" + std::string(host) + CRLF)

// 437   ERR_UNAVAILRESOURCE		"<nick_channel> :Nick/channel is temporarily unavailable"
# define ERR_UNAVAILRESOURCE(nickRes, nick_channel) \
(PREFIX + " 437 " + std::string(nickRes) + " " + std::string(nick_channel) + " :Nick/channel is temporarily unavailable" + CRLF)

// 441   ERR_USERNOTINCHANNEL		"<nick> <channel> :They aren't on that channel"
# define ERR_USERNOTINCHANNEL(nickRes, nick, channel) \
(PREFIX + " 441 " + std::string(nickRes) + " " + std::string(nick) + " " + std::string(channel) + " :They aren't on that channel" + CRLF)

// 442   ERR_NOTONCHANNEL			"<channel> :You're not on that channel"
# define ERR_NOTONCHANNEL(nickRes, channel) \
(PREFIX + " 442 " + std::string(nickRes) + " " + std::string(channel) + " :You're not on that channel" + CRLF)

// 443   ERR_USERONCHANNE			"<user> <channel> :is already on channel"
# define ERR_USERONCHANNE(nickRes, nick, channel) \
(PREFIX + " 443 " + std::string(nickRes) + " " + std::string(nick) + " " + std::string(channel) + " :is already on channel" + CRLF)

// 461   ERR_NEEDMOREPARAMS			"<command> :Not enough parameters"
# define ERR_NEEDMOREPARAMS(nickRes, command) \
(PREFIX + " 461 " + std::string(nickRes) + " " + std::string(command) + " :Not enough parameters" + CRLF)

// 462	 ERR_ALREADYREGISTRED		":Unauthorized command (already registered)"
# define ERR_ALREADYREGISTRED(nickRes) \
(PREFIX + " 462 " + std::string(nickRes) + " :Unauthorized command (already registered)" + CRLF)

// 464   ERR_PASSWDMISMATCH			":Password incorrect"
# define ERR_PASSWDMISMATCH(nickRes) \
(PREFIX + " 464 " + std::string(nickRes) + " :Password incorrect" + CRLF)

// 467   ERR_KEYSET					"<channel> :Channel key already set"
# define ERR_KEYSET(nickRes, channel) \
(PREFIX + " 467 " + std::string(nickRes) + " " + std::string(channel) + " :Channel key already set" + CRLF)

// 471   ERR_CHANNELISFULL			"<channel> :Cannot join channel (+l)"
# define ERR_CHANNELISFULL(nickRes, channel) \
(PREFIX + " 471 " + std::string(nickRes) + " " + std::string(channel) + " :Cannot join channel (+l)" + CRLF)

// 472   ERR_UNKNOWNMODE			"<char> :is unknown mode char to me for <channel>"
# define ERR_UNKNOWNMODE(nickRes, chara, channel) \
(PREFIX + " 472 " + std::string(nickRes) + " " + std::string(nick) + " " + std::string(chara) + " :is unknown mode char to me for" + std::string(channel) + CRLF)

// 473   ERR_INVITEONLYCHAN			"<channel> :Cannot join channel (+i)"
# define ERR_INVITEONLYCHAN(nickRes, channel) \
(PREFIX + " 473 " + std::string(nickRes) + " " + std::string(channel) + " :Cannot join channel (+i)" + CRLF)

// 474   ERR_BANNEDFROMCHAN			"<channel> :Cannot join channel (+b)"
# define ERR_BANNEDFROMCHAN(nickRes, channel) \
(PREFIX + " 474 " + std::string(nickRes) + " " + std::string(channel) + " :Cannot join channel (+b)" + CRLF)

// 475   ERR_BADCHANNELKEY			"<channel> :Cannot join channel (+k)"
# define ERR_BADCHANNELKEY(nickRes, channel) \
(PREFIX + " 475 " + std::string(nickRes) + " " + std::string(channel) + " :Cannot join channel (+k)" + CRLF)

// 476   ERR_BADCHANMASK			"<channel> :Bad Channel Mask"
# define ERR_BADCHANMASK(nickRes, channel) \
(PREFIX + " 476 " + std::string(nickRes) + " " + std::string(channel) + " :Bad Channel Mask" + CRLF)

// 477   ERR_NOCHANMODES			"<channel> :Channel doesn't support modes"
# define ERR_NOCHANMODES(nickRes, channel) \
(PREFIX + " 477 " + std::string(nickRes) + " " + std::string(channel) + " :Channel doesn't support modes" + CRLF)

// 482   ERR_CHANOPRIVSNEEDED		"<channel> :You're not channel operator"
# define ERR_CHANOPRIVSNEEDED(nickRes, channel) \
(PREFIX + " 482 " + std::string(nickRes) + " " + std::string(channel) + " :You're not channel operator" + CRLF)

// 484   ERR_RESTRICTED				":Your connection is restricted!"
# define ERR_RESTRICTED(nickRes) \
(PREFIX + " 484 " + std::string(nickRes) + " :Your connection is restricted!" + CRLF)

// 491   ERR_NOOPERHOST				":No O-lines for your host"
# define ERR_NOOPERHOST(nickRes) \
(PREFIX + " 491 " + std::string(nickRes) + " :No O-lines for your host" + CRLF)

// 501   ERR_UMODEUNKNOWNFLAG		":Unknown MODE flag"
# define ERR_UMODEUNKNOWNFLAG(nickRes) \
(PREFIX + " 501 " + std::string(nickRes) + " :Unknown MODE flag!" + CRLF)

// 502   ERR_USERSDONTMATCH			":Cannot change mode for other users"
# define ERR_USERSDONTMATCH(nickRes) \
(PREFIX + " 502 " + std::string(nickRes) + " :Cannot change mode for other users" + CRLF)

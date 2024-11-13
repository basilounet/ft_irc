#include "../includes/Message.h"

#include <stddef.h> //NULL

Message::Message() : _client(NULL), _str(std::string("")) {
	//throw std::invalid_argument("Message Client is NULL");
}

Message::Message(Client* client, std::string msg) : _client(client), _str(msg) {
	if (client == NULL) {
		//throw std::invalid_argument("Message Client is NULL");
		return;
	}
	if (msg.empty()) {
		//throw std::invalid_argument("Message str is empty");
		return;
	}
	parseMessageStr();
}

Message::~Message() {
}

Message::Message(const Message& src) {
	*this = src;
}

Message& Message::operator=(const Message& src) {
	if (this != &src) {
		_client = src._client;
		_str = src._str;
		_nick = src._nick;
		_server_name = src._server_name;
		_command = src._command;
		_params = src._params;
		_trailing = src._trailing;
	}
	return (*this);
}

void Message::parseMessageStr() {
	// [ ":" prefix SPACE ] command [ params ] crlf
	size_t index0 = 0;
	size_t index1 = 0;

	// [ ":" prefix SPACE ]
	if (_str.at(0) == ':') {
		index1 = _str.find_first_of(" \r", 1);
		if (index1 == -1)
			throw std::invalid_argument("Invalid format");
		std::string prefix = _str.substr(0, index1 - index0);
		if (!prefix.empty())
			parsePrefix(prefix);
		index0 = _str.find_first_not_of(" \r", index1);
	}

	// command
	index1 = _str.find_first_of(" \r", index0);
	if (index1 == -1)
		throw std::invalid_argument("Invalid format");
	std::string command = _str.substr(index0, index1 - index0);
	if (!command.empty()) {
		parseCommand(command);
	}
	if (_str.at(index1) != '\r')
		index0 = index1 + 1;

	// [ params ] crlf
	index1 = _str.find_last_of('\r');
	if (index1 == -1)
		throw std::invalid_argument("Invalid format");
	std::string params = _str.substr(index0, index1 - index0);
		if (!params.empty())
			parseParams(params);
		index0 = _str.find_first_not_of(" \r\n", index1) + 1;
	}
}

void Message::parsePrefix(const std::string& str) {
	std::cout << "parsePrefix :" << str << std::endl;
}
void Message::parseCommand(const std::string& str) {
	std::cout << "parseCommand :" << str << std::endl;
}
void Message::parseParams(const std::string& str) {
	std::cout << "parseParams :" << str << std::endl;
}

	/*

void			parsePrefix(std::string str);
void			parseCommand(std::string str);
void			parseArguments(std::string str);
static void		removeSpaces(std::string str);
static bool		isnospcrlfcl(std::string str);
static bool		isCrlfEnding(std::string str);

 */

/*
Client* Message::getClient() const {
	return _client;
}
std::string Message::getMessageStr() const {
	return _message_str;
}
std::string Message::getNick() const {
	return _nick;
}
std::string Message::getServerName() const {
	return _server_name;
}
std::string Message::getCommand() const {
	return _command;
}
std::vector<std::string> Message::getParams() const {
	return _params;
}
std::string Message::getTrailing() const {
	return _trailing;
}
*/

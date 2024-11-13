#include <Message.h>

#include <cstdlib> //NULL

Message::Message() : _client(NULL), _msg(std::string("")) {
}

Message::Message(Client* client, const std::string &msg) : _client(client), _msg(msg) {
	try {
		if (client == NULL)
			throw std::invalid_argument("client is NULL");
		if (msg.empty())
			throw std::invalid_argument("message is empty");
		parseMsg();
	} catch (std::exception& e) {
		std::cerr << "Message error :" << e.what() << std::endl;
	}
}

Message::~Message() {
}


Message::Message(const Message& src) {
	*this = src;
}

Message& Message::operator=(const Message& src) {
	if (this != &src) {
		_client = src._client;
		_msg = src._msg;
		_nick = src._nick;
		_server_name = src._server_name;
		_command = src._command;
		_params = src._params;
		_trailing = src._trailing;
	}
	return (*this);
}

void Message::parseMsg() {
	std::string str;
	size_t index0 = 0;
	size_t index1 = 0;

	// [ ":" prefix SPACE ]
	if (_msg.at(0) == ':') {
		index0 = 1;
		index1 = _msg.find_first_of(" \r", index0);
		if (index1 == std::string::npos)
			throw std::invalid_argument("Invalid parse 1");
		str = _msg.substr(0, index1 - index0);
		if (!str.empty())
			this->parsePrefix(str);
		else
			throw std::invalid_argument("Invalid parse 1");
		index0 = _msg.find_first_not_of(" \r", index1);
	}

	// command
	index1 = _msg.find_first_of(" \r", index0);
	if (index1 == std::string::npos)
		throw std::invalid_argument("Invalid parse 2");
	str = _msg.substr(index0, index1 - index0);
	if (!str.empty())
		this->parseCommand(str);
	else
		throw std::invalid_argument("Invalid parse 2");
	if (_msg.at(index1) == '\r')
		return;

	// [ params ] crlf
	index0 = index1 + 1;
	index1 = _msg.find_last_of('\r');
	if (index1 == std::string::npos)
		throw std::invalid_argument("Invalid parse 3");
	str = _msg.substr(index0, index1 - index0);
	if (!str.empty())
		this->parseParams(str);
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

bool Message::isnospcrlfcl(const std::string &str) {
	(void) str;
	return true;
}

bool Message::isCrlfEnding(const std::string &str) {
	(void) str;
	return true;
}

Client* Message::getClient() const {
	return _client;
}
std::string Message::getMsg() const {
	return _msg;
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


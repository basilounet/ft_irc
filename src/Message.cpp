#include <Message.h>

Message::Message() {
	Message(NULL, std::string(("")));
}

Message::Message(Client* client, const std::string &msg) : _client(client), _msg(msg) {
	if (client == NULL)
		throw std::invalid_argument("client is NULL");
	if (msg.empty())
		throw std::invalid_argument("message is empty");
	parseMsg();
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
		_serverName = src._serverName;
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
			throw std::invalid_argument("Invalid parse pre prefix (no end)");
		str = _msg.substr(index0, index1 - index0);
		parsePrefix(str);
		index0 = _msg.find_first_not_of(" \r", index1);
	}
	// command
	index1 = _msg.find_first_of(" \r", index0);
	if (index1 == std::string::npos)
		throw std::invalid_argument("Invalid parse pre command (no end)");
	str = _msg.substr(index0, index1 - index0);
	parseCommand(str);
	if (_msg.at(index1) == '\r')
		return;
	// [ params ] crlf
	index0 = index1 + 1;
	index1 = _msg.find_last_of('\r');
	if (index1 == std::string::npos)
		throw std::invalid_argument("Invalid parse pre arguments (no end)");
	str = _msg.substr(index0, index1 - index0);
	parseParams(str);
	std::cout << std::endl;
}

// prefix = servername / ( nickname [ [ "!" user ] "@" host ] )
void Message::parsePrefix(const std::string& str) {
	if (str.empty())
		throw std::invalid_argument("Invalid parse pre prefix (empty)");
	_serverName = str;
	std::cout << C_OR << _serverName << C_RESET << " ";
}

// command    =  1*letter / 3digit
void Message::parseCommand(const std::string& str) {
	if (str.empty())
		throw std::invalid_argument("Invalid parse pre command (empty)");
	_command = str;
	std::cout << C_LIME << _command << C_RESET << " ";
}

// params	= *14( SPACE middle ) [ SPACE ":" trailing ]
// 			=/ 14( SPACE middle ) [ SPACE [ ":" ] trailing ]
void Message::parseParams(const std::string& str) {
	if (str.empty())
		return ;
	int nb = 0;
	size_t index0 = 0;
	size_t index1 = 0;
	while (nb < 14) {
		index0 = str.find_first_not_of(" ", index1);
		if (index0 == std::string::npos)
			break ;
		index1 = str.find_first_of(" ", index0);
		//std::cout << C_OR << "[" << str << "]" << C_RESET;
		if (str.at(index0) == ':') {
			_trailing = str.substr(index0 + 1);
			std::cout << C_ROSE << ":[" << _trailing << "]" << C_RESET;
			break ;
		}
		if (index1 == std::string::npos) {
			_params.push_back(str.substr(index0));
			std::cout << C_ROSE << _params.back() << C_RESET << " ";
			break ;
		}
		_params.push_back(str.substr(index0, index1 - index0));
		std::cout << C_ROSE << _params.back() << C_RESET << ",";
		if (++nb >= 14)
			throw std::invalid_argument("Invalid parse params (too many arguments)");
	}
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
	return _serverName;
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


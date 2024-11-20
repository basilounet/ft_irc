#include <Message.h>

Message::Message() {
	*this = Message(NULL, "");
}

Message::Message(Client* client, const std::string &msg) 
	: _cmd(NULL), _client(client), _msg(msg) {
	if (client == NULL)
		throw std::invalid_argument("client is NULL");
	if (msg.empty())
		throw std::invalid_argument("message is empty");
	parseMsg();
}

Message::~Message() {
	delete _cmd;
}


Message::Message(const Message& src) {
	*this = src;
}

Message& Message::operator=(const Message& src) {
	if (this != &src) {
		_client = src._client;
		_msg = src._msg;
		_serverName = src._serverName;
		_command = src._command;
		_params = src._params;
		_trailing = src._trailing;
		delete _cmd;
		_cmd = NULL;
		if (src._cmd)
			_cmd = src._cmd->clone();
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
	index1 = _msg.rfind('\r');
	if (index1 == std::string::npos)
		throw std::invalid_argument("Invalid parse pre arguments (no end)");
	str = _msg.substr(index0, index1 - index0);
	parseParams(str);
	std::cout << std::endl;
}

void Message::execCommand() {
	createCommand();
	if ((_client->getFlags() & HAS_REGISTERED) == 0)
		if (_command != "PASS" && _command != "NICK" && _command != "USER")
			throw std::invalid_argument("User registration not complete");
	_cmd->process(*this);
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
		index0 = str.find_first_not_of(' ', index1);
		if (index0 == std::string::npos)
			break ;
		index1 = str.find(' ', index0);
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

std::string Message::prefix(int type) const {
	std::string	prefix_str;
	if (type == 1) // :localhost
		prefix_str = " :" + SERVER_REAL_NAME + " ";
	if (type == 2) // :localhost
		prefix_str = " :" + _client->getNick() + "!" + _client->getUser() + HOST + " ";
	return prefix_str;
}

Client* Message::getClient() const {
	return _client;
}

std::string Message::getMsg() const {
	return _msg;
}

std::string Message::getNick() const {
	return _client->getNick();
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

int Message::getFd() const {
	return _client->getfd().fd;
}

void	Message::createCommand() {
	const char	*tmp[] = {"INVITE", "JOIN", "KICK", "MODE", "NICK",
		"PART", "PASS", "MSG", "PRIVMSG", "TOPIC", "USER", NULL};
	int i = 0;

	while (tmp[i] && _command != tmp[i])
		i++;
	switch (i) {
		case 0:
			_cmd = new Invite();
		break ;
		case 1:
			_cmd = new Join();
		break ;
		case 2:
			_cmd = new Kick();
		break ;
		case 3:
			_cmd = new Mode();
		break ;
		case 4:
			_cmd = new Nick();
		break ;
		case 5:
			_cmd = new Part();
		break ;
		case 6:
			_cmd = new Pass();
		break ;
		case 7: ;
		case 8:
			_cmd = new Privmsg();
		break ;
		case 9:
			_cmd = new Topic();
		break ;
		case 10:
			_cmd = new User();
		break ;
		default:
			throw std::invalid_argument("Not known command");
	}
}

#include <ACommand.h>

ACommand::ACommand() :
	_params() {
}

ACommand::ACommand(const ACommand& src) :
	_params(src._params) {
	*this = src;
}

ACommand& ACommand::operator=(const ACommand& right) {
	if (this != &right) {
		_params = right._params;
	}
	return (*this);
}

ACommand::~ACommand() {
}

#include <ACommand.h>

ACommand::ACommand() {
}

ACommand::ACommand(const ACommand& src) {
	*this = src;
}

ACommand& ACommand::operator=(const ACommand& right) {
	if (this != &right) {
	}
	return (*this);
}

ACommand::~ACommand() {
}

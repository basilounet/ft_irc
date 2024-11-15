//
// Created by bvasseur on 11/15/24.
//

#include "Mode.h"

Mode::Mode() {
}

Mode::Mode(Mode const& src) {
	*this = src;
}

Mode::~Mode() {
}

Mode& Mode::operator=(Mode const& other) {
	ACommand::operator=(other);
	return (*this);
}

void	Mode::process(const Message& msg) {
	(void)msg;
}

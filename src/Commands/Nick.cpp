//
// Created by bvasseur on 11/15/24.
//

#include "Nick.h"

Nick::Nick() {
}

Nick::Nick(Nick const& src) {
	*this = src;
}

Nick::~Nick() {
}

Nick& Nick::operator=(Nick const& other) {
	ACommand::operator=(other);
	return (*this);
}

void	Nick::process(const Message& msg) {
	(void)msg;
}

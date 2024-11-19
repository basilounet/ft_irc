//
// Created by bvasseur on 11/15/24.
//

class ACommand;

#include "Pass.h"

Pass::Pass() {
}

Pass::Pass(Pass const& src) {
	(void) src;
}

Pass::~Pass() {
}

Pass& Pass::operator=(Pass const& other) {
	(void) other;
	return (*this);
}

void	Pass::process(const Message& msg) {
	(void) msg;
}

ACommand	*Pass::clone(void) const {
	return new Pass();
}

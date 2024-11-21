//
// Created by bvasseur on 11/15/24.
//

class ACommand;

#include "Quit.h"

Quit::Quit() {
}

Quit::Quit(Quit const& src) {
	(void) src;
}

Quit::~Quit() {
}

Quit& Quit::operator=(Quit const& other) {
	(void) other;
	return (*this);
}

void	Quit::process(const Message& msg) {
	msg.getClient()->setFlags(IS_RM);
}

ACommand	*Quit::clone(void) const {
	return new Quit();
}

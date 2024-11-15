//
// Created by bvasseur on 11/15/24.
//

#include "Kick.h"

Kick::Kick() {
}

Kick::Kick(Kick const& src) {
	*this = src;
}

Kick::~Kick() {
}

Kick& Kick::operator=(Kick const& other) {
	ACommand::operator=(other);
	return (*this);
}

void	Kick::process(const Message& msg) {
	(void)msg;
}

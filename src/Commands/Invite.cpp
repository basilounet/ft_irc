//
// Created by bvasseur on 11/15/24.
//

#include "Invite.h"

Invite::Invite() {
}

Invite::Invite(Invite const& src) {
	*this = src;
}

Invite::~Invite() {
}

Invite& Invite::operator=(Invite const& other) {
	ACommand::operator=(other);
	return (*this);
}

void	Invite::process(const Message& msg) {
	(void)msg;
}

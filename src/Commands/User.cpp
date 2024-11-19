//
// Created by bvasseur on 11/15/24.
//

#include "User.h"

User::User() {
}

User::User(User const& src) {
	*this = src;
}

User::~User() {
}

User& User::operator=(User const& other) {
	ACommand::operator=(other);
	return (*this);
}

void	User::process(const Message& msg) {
	(void)msg;
}

ACommand	*User::clone(void) const {
	return new User();
}

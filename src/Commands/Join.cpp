//
// Created by bvasseur on 11/15/24.
//

#include "Join.h"

Join::Join() {
}

Join::Join(Join const& src) {
	*this = src;
}

Join::~Join() {
}

Join& Join::operator=(Join const& other) {
	ACommand::operator=(other);
	return (*this);
}

void	Join::process(const Message& msg) {
	(void)msg;
}

ACommand	*Join::clone(void) const {
	return new Join();
}

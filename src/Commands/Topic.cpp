//
// Created by bvasseur on 11/15/24.
//

#include "Topic.h"

Topic::Topic() {
}

Topic::Topic(Topic const& src) {
	*this = src;
}

Topic::~Topic() {
}

Topic& Topic::operator=(Topic const& other) {
	ACommand::operator=(other);
	return (*this);
}

void	Topic::process(const Message& msg) {
	(void)msg;
}

ACommand	*Topic::clone(void) const {
	return new Topic();
}

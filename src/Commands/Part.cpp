//
// Created by bvasseur on 11/15/24.
//

#include "Part.h"

Part::Part() {
}

Part::Part(Part const& src) {
	*this = src;
}

Part::~Part() {
}

Part& Part::operator=(Part const& other) {
	ACommand::operator=(other);
	return (*this);
}

void	Part::process(const Message& msg) {
	(void)msg;
}

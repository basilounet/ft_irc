//
// Created by bvasseur on 11/15/24.
//

#include "Privmsg.h"

Privmsg::Privmsg() {
}

Privmsg::Privmsg(Privmsg const& src) {
	*this = src;
}

Privmsg::~Privmsg() {
}

Privmsg& Privmsg::operator=(Privmsg const& other) {
	ACommand::operator=(other);
	return (*this);
}

void	Privmsg::process(const Message& msg) {
	if (msg.getParams().empty())
		//ERR_NORECIPIENT
	if (msg.getParams.size() == 1 && msg.getTrailing().empty())
		//ERR_NOTEXTTOSEND
}

void	Pr

ACommand	*Privmsg::clone(void) const {
	return new Privmsg();
}

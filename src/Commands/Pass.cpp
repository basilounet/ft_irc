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
	const int clientFlags = msg.getClient()->getFlags();

	if (clientFlags & HAS_REGISTERED)
	{
		Server::sendMessage(ERR_ALREADYREGISTRED(msg.prefix(1), msg.getNick()), msg.getFd());
		throw std::logic_error("PASS: Unauthorized command (already registered)");
	}
	checkNbParam(msg, 1); // throw if ERR_NEEDMOREPARAMS
	msg.getClient()->setPassword(msg.getParams()[0]);
	msg.getClient()->setFlags(clientFlags | HAS_TRY_PASS);
}

ACommand	*Pass::clone(void) const {
	return new Pass();
}

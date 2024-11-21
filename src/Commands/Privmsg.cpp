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
	std::vector<std::string> &recip;

	if (msg.getParams().empty())
		//ERR_NORECIPIENT
	if (msg.getTrailing().empty())
	{
		if (msg.getParams.size() == 1)
			//ERR_NOTEXTTOSEND
		recip = ACommand::split(msg.getParams()[1], ',');
	}
	else
		recip = ACommand::split(msg.getTrailing(), ',');
	for (std::vector<std::string>::iterator it = recip.begin() ;
			it != recip.end() ; it++)
		sendToRecipient(msg.getParams[0], *it);
}

void	Privmsg::sendToRecipient(const std::string &toSend, 
		const std::string &recip)
{
	if (recip[0] == '#' || recip[0] == '+' || recip[0] == '&' || recip[0] == '!')
		//sendtochannel
		//return
}

ACommand	*Privmsg::clone(void) const {
	return new Privmsg();
}

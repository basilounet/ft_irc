#include "Channel.h"

Channel::Channel(const std::string& name) : _name(name), _clients() {
}

Channel::~Channel() {
}

Channel::Channel(const Channel& src) : _name(src._name), _clients() {
	*this = src;
}

Channel& Channel::operator=(const Channel& src) {
	if (this != &src) {
		_name = src._name;
		_clients = src._clients;
	}
	return (*this);
}

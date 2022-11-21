#ifndef CLIENT_H
#define CLIENT_H

#include<string>
#include"crypto.h"
#include "server.h"
class Server;
class Client
{
public:
	Client(const std::string id, const Server& server);
	const std::string get_id() const;
	const std::string get_publickey() const;
	const double get_wallet() const;
	std::string sign(const std::string& txt) const;
	bool transfer_money(const std::string& receiver, const double& value);
	size_t generate_nonce();
private:
	Server const* const server;
	const std::string id;
	std::string public_key;
	std::string private_key;
};

#endif //CLIENT_H
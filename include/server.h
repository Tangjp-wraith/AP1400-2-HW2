#ifndef SERVER_H
#define SERVER_H

#include<string>
#include<memory>
#include<map>
#include<compare>
#include<random>
#include"crypto.h"
#include"client.h"

extern std::vector<std::string> pending_trxs;
class Client;
class Server
{
public:
	Server();
	std::shared_ptr<Client> add_client(std::string id);
	const std::shared_ptr<Client> get_client(const std::string& id) const ;
	const double get_wallet(const std::string& id) const;
	bool parse_trx(const std::string& trx, std::string sender, std::string receiver, double value)const;
	bool add_pending_trx(const std::string& trx, const std::string signature)const;
	size_t mine();
	friend void show_wallets(const Server& server);
private:
	std::map<std::shared_ptr<Client>, double> clients;
};


#endif //SERVER_H
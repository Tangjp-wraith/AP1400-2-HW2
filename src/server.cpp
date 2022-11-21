#include "server.h"

std::vector<std::string> pending_trxs;

Server::Server()=default;

std::shared_ptr<Client> Server::add_client(std::string id){
    for(const auto &[name,value]:clients){
        const std::strong_ordering order = id <=> (*name).get_id();
        if(std::is_eq(order)){
            std::default_random_engine e;
            std::uniform_int_distribution<int> u(1000,9999);
            id+=std::to_string(u(e));
            break;
        }
    }
    double wallet=5;
    std::shared_ptr<Client> pntr_client=std::make_shared<Client>(id,*this);
    clients[pntr_client]=wallet;
    return pntr_client;
}

const std::shared_ptr<Client> Server::get_client(const std::string& id) const{
    for(const auto &[name,value]:clients){
        const std::strong_ordering order = id <=> (*name).get_id();
        if(std::is_eq(order)){
            return name;
        }
    }
    return nullptr;
}

const double Server::get_wallet(const std::string& id)const{
    for(const auto &[name,value]:clients){
        const std::strong_ordering order = id <=> (*name).get_id();
        if(std::is_eq(order)){
            return value;
        }
    }
    throw std::logic_error("Client is not found");
}

bool parse_trx(const std::string& trx, std::string sender, std::string receiver, double value){
    size_t cnt=0;
    std::string svalue;
    for(const auto& c:trx){
        if(c=='-'){
            cnt++;
            continue;
        }
        if(cnt==0){
            sender+=c;
        }
        if(cnt==1){
            receiver+=c;
        }
        if(cnt==2){
            svalue+=c;
        }
    }
    if(cnt!=2){
        throw std::logic_error("the format is error");
    }
    value=std::stod(svalue);
    return true;
}

bool Server::add_pending_trx(const std::string trx, const std::string signature)const{
    
}


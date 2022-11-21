#include "server.h"

std::vector<std::string> pending_trxs;

Server::Server()=default;

std::shared_ptr<Client> Server::add_client(std::string id){
    for(const auto &[name,value]:clients){
        const std::strong_ordering order = id <=> (*name).get_id();
        if(std::is_eq(order)){
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<int> u(1000,9999);
            id+=std::to_string(u(mt));
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

bool Server::parse_trx(const std::string& trx, std::string sender, std::string receiver, double value)const {
    size_t cnt=0;
    std::string svalue;
    for(const auto& c:trx){
        if(c=='-'){
            cnt++;
            continue;
        }
        if(cnt==0){
            sender+=c;
        }else if(cnt==1){
            receiver+=c;
        }else if(cnt==2){
            svalue+=c;
        }
    }
    if(cnt!=2){
        throw std::logic_error("the format is error");
    }
    value=std::stod(svalue);
    return true;
}

bool Server::add_pending_trx(const std::string& trx, const std::string signature)const{
    std::string sender_id,receiver_id;
    double value;
    parse_trx(trx,sender_id,receiver_id,value);
    bool sign_true=crypto::verifySignature(get_client(sender_id)->get_publickey(),trx,signature);
    if(sign_true&&get_client(sender_id)->get_wallet()>=value){
        pending_trxs.push_back(trx);
        return true;
    }
    return false;
}

size_t mine(){
    
}

void show_wallets(const Server& server){
    std::cout<<"*******************************"<<std::endl;
    for(const auto&  client:server.clients){
        std::cout<<client.first->get_id()<<" : "<<client.second<<std::endl;
    }
    std::cout<<"*******************************"<<std::endl;
}


#include "client.h"

Client::Client(const std::string _id,const Server& _server)
    : id{_id} , server{&_server}{
        std::string  _public_key{}, _private_key{};
        crypto::generate_key(_public_key,_private_key);
        public_key=_public_key;
        private_key=_private_key;
}

const std::string Client::get_id()const{
    return id;
}

const std::string Client::get_publickey()const{
    return public_key;
}

const double Client::get_wallet()const{
    return server->get_wallet(id);
}

std::string Client::sign(const std::string& txt)const {
    std::string signature = crypto::signMessage(private_key,txt);
    
}



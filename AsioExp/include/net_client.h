#pragma once
#include "net_common.h"
#include "net_message.h"
#include "net_tsqueue.h"
#include "net_connection.h"

using namespace boost;

template <typename T>
class client_interface{
public:
   bool Connect(const std::string& host, const uint16_t port){
       try{
           m_connection = std::make_unique<connection<T>>();

           asio::ip::tcp::resolver resolver(m_context);
           auto m_endpoints = resolver.resolve(host, std::to_string(port));

           m_connection->ConnectToServer(m_endpoints);

           thrContext = std::thread([this]() { m_context.run(); });
       }
       catch(std::exception& e){
           std::cerr << "Client exception";
           return false;
       }
    }

    void Disconnect(){
       if(IsConnected()){
           m_connection->Disconnect();
       }

       m_context.stop();

       if(thrContext.joinable()){
           thrContext.join();
       }
    }

    bool IsConnected(){
       if (m_connection){
           return m_connection->IsConnected();
       }
       else return false;
    }
public:
    bool Send(message<T>& msg);

protected:
    asio::io_context m_context;

    std::thread thrContext;

    asio::ip::tcp::socket  m_socket;

    std::unique_ptr<connection<T>> m_connection;

private:
    tsqueue<owned_message<T>> m_qMessagesIn;
};

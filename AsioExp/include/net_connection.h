#pragma once

#include "net_common.h"
#include "net_tsqueue.h"
#include "net_message.h"

template<typename T>
class connection : public std::enable_shared_from_this<connection<T>>{
public:
    connection(){}

    virtual ~connection(){}

public:
    bool ConnectToServer();
    bool Disconnect();
    bool IsConnected() const;

public:
    bool Send(const message<T>& msg);

protected:
    asio::ip::tcp::socket m_socket;

    //This is a reference to the context a user has created.
    asio::io_context& m_asioContext;

    tsqueue<message<T>> m_qMessagesOut;

    tsqueue<owned_message<T>> m_qMessagesIn;
};
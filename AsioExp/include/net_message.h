#pragma once
#include "net_common.h"

template<typename T>
struct message_header{
   T id{};
   uint32_t size;
};

template<typename T>
struct message{
    //Describes ID and size of entire message
    message_header<T> header{};
    std::vector<uint8_t> body;

    size_t size() const{
        return sizeof(message_header<T>) + body.size();
    }

public:
    friend std::ostream& operator << (std::ostream& os, const message<T>& msg){
        os << "ID:" << int(msg.header.id) << " Size:" << msg.header.size;
        return os;
    }

    //Methods for working with buffer
public:
    template<typename DataType>
    friend std::ostream& operator << (message<T>& msg, const DataType& data){
        auto i = msg.body.size();

        msg.body.resize(i + sizeof(data));

        std::memcpy(msg.body.data() + i, &data, sizeof(data));

        msg.header.size = msg.size();

        return msg;
    }

    template<typename DataType>
    friend std::ostream& operator >> (message<T>& msg, const DataType& data){
        auto data_start_index = msg.body.size() - sizeof(DataType);

        std::memcpy(&data, msg.body.data() + data_start_index, sizeof(DataType));

        msg.body.resize(data_start_index);

        msg.header.size = sizeof(msg);

        return msg;
    }
};

template<typename T>
class connection;

template<typename T>
struct owned_message{
    std::shared_ptr<connection<T>> remote = nullptr;
    message<T> msg;

    friend std::ostream& operator<<(std::ostream& os, const owned_message<T>& msg){
       os << msg.msg;
       return os;
    }
};
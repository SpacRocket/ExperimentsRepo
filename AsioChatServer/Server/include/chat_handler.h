#pragma once

#include <memory>
#include <deque>
#include <boost/asio.hpp>

using namespace boost;

class chat_handler : public std::enable_shared_from_this<chat_handler> {
public:
    chat_handler(asio::io_service &service) : service_(service), socket_(service), write_strand_(service) {

    }

    asio::ip::tcp::socket &socket() {
        return socket_;
    }

    void send(std::string msg)
    {
        service_.post( write_strand_.wrap( [me=shared_from_this(), msg](){
            me->queue_message(msg);
        }));
    }

    void queue_message(std::string message){
        bool write_in_progress = !send_packet_queue.empty();
        send_packet_queue.push_back(std::move(message));

        if(!write_in_progress){
            start_packet_send();
        }
    };

    void start_packet_send(){
        send_packet_queue.front() += "\0";
        asio::async_write(socket_, asio::buffer(send_packet_queue.front()), write_strand_.wrap( [me=shared_from_this()](system::error_code const & ec, std::size_t){me->packet_send_done();});
    };

    void packet_send_done(system::error_code const & error)
    {
        if(!error)
        {
            send_packet_queue.pop_front();
            if(!send_packet_queue.empty()) { start_packet_send(); }
        }
    }

    void start() {
        read_packet();
    }

private:
    void read_packet() {
        asio::async_read_until(socket_, in_packet_, '\0',
                               [me = shared_from_this()](system::error_code const &ec, std::size_t bytes_xfer) {
                                   me->read_packet_done(ec, bytes_xfer);
                               });
    }

    void read_packet_done(system::error_code const &error, std::size_t bytes_transferred) {
        if(error){ return; }

        std::istream stream(&in_packet_);
        std::string packet_string;
        stream >> packet_string;

        // do something

        read_packet();
    }

    asio::io_service &service_;
    asio::ip::tcp::socket socket_;
    asio::io_service::strand write_strand_;
    asio::streambuf in_packet_;
    std::deque<std::string> send_packet_queue;
};

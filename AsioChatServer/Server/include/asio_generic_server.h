#pragma  once

#include <memory>
#include <vector>
#include "boost/asio.hpp"

using namespace boost;

template<typename ConnectionHandler>
class asio_generic_server {
    using shared_handler_t = std::shared_ptr<ConnectionHandler>;
public:
    asio_generic_server(const int thread_count = 1) : thread_count_(thread_count), acceptor_(io_service_) {}

    void start_server(uint16_t port) {
        auto handler = std::make_shared<ConnectionHandler>(io_service_);

        //Create a acceptor, listens on
        asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), port);
        acceptor_.open(endpoint.protocol());
        acceptor_.set_option(asio::socket_base::reuse_address(true));
        acceptor_.bind(endpoint);
        acceptor_.listen();

        acceptor_.async_accept(handler->socket(), [=](auto ec) {
            handle_new_connection(handler, ec);
        });

        for (int i = 0; i < thread_count_; ++i) {
            thread_pool_.emplace_back([=] { io_service_.run(); });
        }
    }

private:
    void handle_new_connection(shared_handler_t handler, system::error_code const &error) {
        if (error) { return; }

        handler->start();

        auto new_handler = std::make_shared<ConnectionHandler>(io_service_);

        acceptor_.template async_accept(new_handler->socket(),
                                        [=](auto ec) { handle_new_connection(new_handler, ec); });
    }

    int thread_count_;
    std::vector<std::thread> thread_pool_;
    asio::io_service io_service_;
    asio::ip::tcp::acceptor acceptor_;
};
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>
#include <olc_net.h>

using namespace boost;

std::vector<char> vBuffer(20 * 1024);

void GrabSomeData(asio::ip::tcp::socket& socket){
    socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
    [&](std::error_code ec, std::size_t length){
        if(!ec){
            std::cout << "\n\nRead " << length << " bytes \n\n";

            for( int i = 0; i < length; i++)
                std::cout << vBuffer[i];

            GrabSomeData(socket);
        }
    }
    );
}

int main() {
    system::error_code ec;

    asio::io_context io_context;
    asio::ip::tcp::endpoint endpoint(asio::ip::make_address("93.184.216.34", ec), 80);
    asio::ip::tcp::socket socket(io_context);

    socket.connect(endpoint, ec);
    if (!ec){
        std::cout << "Connection is ok!" << std::endl;
    }
    else{
        std::cout << "Failed to connect" << ec.message() << std::endl;
    }

    if(socket.is_open()){
        GrabSomeData(socket);

        std::string sRequest = "GET /index.html HTTP/1.1\r\n"
                               "Host: example.com\r\n"
                               "Connection:close\r\n\r\n";
        socket.write_some(asio::buffer(sRequest), ec);

        std::thread t1 = std::thread([&]() {io_context.run(); });

        t1.join();
    }
    return 0;
}
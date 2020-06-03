#include <iostream>
#include "dccp.hpp"
#include <boost/asio/spawn.hpp>
int main() {
    boost::asio::io_context io;
    boost::asio::spawn(io, [&](boost::asio::yield_context yield) {
        auto ep = boost::asio::ip::dccp::endpoint(boost::asio::ip::make_address_v4("127.0.0.1"), 1234);
        boost::asio::ip::dccp::socket socket(io);
        boost::system::error_code ec;
        socket.async_connect(ep, yield[ec]);
        if (ec) {
            std::cout << ec.message();
            return;
        }
        std::cout << "connected" << std::endl;
        int times = 1024000;
        char buff[1024] = {1};
        auto t1 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 1000000; ++i) {
            auto bytes_send = socket.async_send(boost::asio::buffer(buff, 1024), yield[ec]);
            if (ec) {
                printf("%s\n", ec.message().c_str());
                return;
            }
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        std::cout << "total :" << times / 1024  << "\n";
        std::cout << "duration:" << duration  << "\n";
        fflush(stdout);
    });
    io.run();
    return 0;
}

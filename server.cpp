#include <iostream>
#include "dccp.hpp"
#include <boost/asio/spawn.hpp>
int main() {
    boost::asio::io_context io;
    boost::asio::spawn(io, [&](boost::asio::yield_context yield) {
        boost::asio::ip::dccp::acceptor acceptor(io, boost::asio::ip::dccp::endpoint(boost::asio::ip::make_address_v4("127.0.0.1"), 1234));
        boost::system::error_code ec;
        while(1) {
            auto peer = std::make_unique<boost::asio::ip::dccp::socket>(io);
            acceptor.async_accept(*peer, yield[ec]);
            if (ec) {
                std::cout << ec.message();
                return 0;
            }
            printf("conn from %s:%d\n",peer->remote_endpoint().address().to_string().c_str(), peer->remote_endpoint().port());
            boost::asio::spawn(io, [&, peer = std::move(peer)](boost::asio::yield_context yield){
                boost::system::error_code ec;
                char buff[1024] = {0};
                int count = 0;
                while (1) {
                    auto bytes_read = peer->async_receive(boost::asio::buffer(buff, 1024), yield[ec]);
                    if (ec) {
                        printf("%s\n", ec.message().c_str());
                        return;
                    }
                    if (bytes_read == 0) {
                        printf("peer closed\n");
                        printf("read packet count %d\n", count);
                        return;
                    }
                    ++count;
                }
            });
        }

    });
    io.run();
    return 0;
}

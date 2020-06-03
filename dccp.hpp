#ifndef BOOST_ASIO_IP_DCCP_HPP
#define BOOST_ASIO_IP_DCCP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/basic_datagram_socket.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/ip/basic_endpoint.hpp>
#include <boost/asio/ip/basic_resolver.hpp>
#include <boost/asio/ip/basic_resolver_iterator.hpp>
#include <boost/asio/ip/basic_resolver_query.hpp>
#include <boost/asio/basic_stream_socket.hpp>
#include <boost/asio/basic_socket_acceptor.hpp>
#include <boost/asio/detail/push_options.hpp>

namespace boost {
    namespace asio {
        namespace ip {

/// Encapsulates the flags needed for DCCP.
/**
 * The boost::asio::ip::dccp class contains flags necessary for DCCP sockets.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Safe.
 *
 * @par Concepts:
 * Protocol, InternetProtocol.
 */
            class dccp
            {
            public:
                /// The type of a DCCP endpoint.
                typedef basic_endpoint<dccp> endpoint;

                /// Construct to represent the IPv4 DCCP protocol.
                static dccp v4()
                {
                    return dccp(AF_INET);
                }

                /// Construct to represent the IPv6 DCCP protocol.
                static dccp v6()
                {
                    return dccp(AF_INET6);
                }

                /// Obtain an identifier for the type of the protocol.
                int type() const
                {
                    return SOCK_DCCP;
                }

                /// Obtain an identifier for the protocol.
                int protocol() const
                {
                    return IPPROTO_DCCP;
                }

                /// Obtain an identifier for the protocol family.
                int family() const
                {
                    return family_;
                }

                /// The DCCP socket type.
                typedef basic_stream_socket<dccp> socket;

                typedef basic_socket_acceptor<dccp> acceptor;

                /// The DCCP resolver type.
                typedef basic_resolver<dccp> resolver;

                /// Compare two protocols for equality.
                friend bool operator==(const dccp& p1, const dccp& p2)
                {
                    return p1.family_ == p2.family_;
                }

                /// Compare two protocols for inequality.
                friend bool operator!=(const dccp& p1, const dccp& p2)
                {
                    return p1.family_ != p2.family_;
                }

            private:
                // Construct with a specific family.
                explicit dccp(int protocol_family)
                        : family_(protocol_family)
                {
                }

                int family_;
            };

        } // namespace ip
    } // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_DCCP_HPP

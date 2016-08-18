//
// Created by lahmer on 8/16/16.
//
#include"common.h"
int main(){
    std::cout<<"Hello world"<<std::endl;
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"),12000);
    boost::asio::io_service ios;
    boost::asio::ssl::context ctx(ios,
    boost::asio::ssl::context::sslv23);

    ctx.set_options(
            boost::asio::ssl::context::default_workarounds|
            boost::asio::ssl::context::no_sslv2|
            boost::asio::ssl::context::single_dh_use
    );
    ctx.set_verify_mode(
            boost::asio::ssl::context::verify_peer |
            boost::asio::ssl::context::verify_fail_if_no_peer_cert
    );
    ctx.load_verify_file("certs/server.crt");
    ctx.use_certificate_chain_file("certs/server.crt");
    ctx.use_private_key_file("certs/server.key", boost::asio::ssl::context::pem);
    ctx.use_tmp_dh_file("certs/dh512.pem");



    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> m_ssl_socket(ios,ctx);

    m_ssl_socket.set_verify_mode(boost::asio::ssl::verify_peer);
    m_ssl_socket.set_verify_callback([](bool preverified,
    boost::asio::ssl::verify_context& context) -> bool {
        return true;
    });

    m_ssl_socket.lowest_layer().connect(ep);
    m_ssl_socket.handshake(boost::asio::ssl::stream_base::client);
    std::string message = "Helko there \n";
    boost::asio::write(m_ssl_socket, boost::asio::buffer(message));

    boost::asio::streambuf buf;
    boost::asio::read_until(m_ssl_socket,buf,'\n');
    std::string responses;
    std::istream input(&buf);
    std::getline(input,responses);
    std::cout<<responses<<std::endl;
    while(true);


}

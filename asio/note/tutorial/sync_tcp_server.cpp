#include <ctime>
#include <iostream>
#include <string>
#include <asio.hpp>

std::string make_daytime_string()
{
    std::time_t now = std::time(nullptr);
    return std::ctime(&now);
}

int main()
{
    try
    {
        asio::io_context context;

        asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), 13);
        asio::ip::tcp::acceptor acceptor(context, endpoint);

        for (;;)
        {
            asio::ip::tcp::socket socket(context);
            acceptor.accept(socket);

            std::string daytime = make_daytime_string();
            std::error_code ignored_ec;
            asio::write(socket, asio::buffer(daytime), ignored_ec);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
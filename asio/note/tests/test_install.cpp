#include <iostream>
#include <asio.hpp>

int main()
{
    asio::io_context io_context;
    asio::steady_timer timer(io_context, asio::chrono::seconds(1));
    timer.wait();
    std::cout << "Hello, world!" << std::endl;
    return 0;
}
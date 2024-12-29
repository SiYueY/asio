#include <iostream>
#include <asio.hpp>

// completion_handler 完成处理函数
void print(const std::error_code /*e*/){
    std::cout << "Async timer expired." << std::endl;
    std::cout << "Hello, world!" << std::endl;
}

/* 异步定时器 */
int main()
{
    asio::io_context io;

    asio::steady_timer timer(io, std::chrono::seconds(1));

    // 异步等待
    timer.async_wait(&print);

    // asio保证仅从io_context::run()所在线程调用completion_handler
    io.run();
    
    return 0;
}
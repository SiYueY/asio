#include <asio.hpp>
#include <functional>
#include <iostream>

void print(const std::error_code& /*e*/,
           asio::steady_timer* timer, int* count) {
    // 在计数器第六次触发时停止运行程序
    if(*count < 6){
        std::cout << "Timer expired, count = " << *count << std::endl;
        ++(*count);
        // 修改定时器的到期时间，将定时器的到期时间从上一个到期时间向后移动1秒
        timer->expires_at(timer->expiry() + std::chrono::seconds(1));
        // 启动新的异步等待
        // asio::placeholders::error是传递给completion_handler的错误对象的命名占位符
        timer->async_wait(std::bind(print, asio::placeholders::error, timer, count));
    }
}

// 将参数绑定到completion_handler
int main() {
    // 计数器
    int count = 1;
    asio::io_context io;
    asio::steady_timer timer(io, std::chrono::seconds(1));
    timer.async_wait(std::bind(print, asio::placeholders::error, &timer, &count));
    io.run();
    std::cout << "Final count is "  << count << std::endl;
    return 0;
}
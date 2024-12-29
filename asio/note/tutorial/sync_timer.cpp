#include <iostream>
/* 只需包含"asio.hpp"头文件即可使用所有asio类 */
#include <asio.hpp>

/* 同步定时器 */
int main(){
    // I/O执行上下文：提供对I/O功能的访问
    asio::io_context io;

    
    // 提供I/O功能的asio类始终将exector或对执行上下文的引用作为其构造函数的第一个参数。
    asio::steady_timer timer(io, asio::chrono::seconds(3));

    // timer始终处于“已过期”或“未过期”状态。
    // 若在“已过期”状态下的timer上调用steady_timer::wait()，则会立即返回。
    // 同步阻塞
    timer.wait();

    std::cout << "Sync Timer Expired!" << std::endl;
    std::cout << "Hello, world!" << std::endl;

    return 0;
}

#include <functional>
#include <iostream>
#include <thread>
#include <asio.hpp>

class Printer{
public:
    Printer(asio::io_context& io_context):
        strand_(asio::make_strand(io_context)),
        timer1_(io_context, std::chrono::seconds(1)),
        timer2_(io_context, std::chrono::seconds(1)),
        count(0)
        {
            timer1_.async_wait(asio::bind_executor(strand_, std::bind(&Printer::print1, this)));
            timer2_.async_wait(asio::bind_executor(strand_, std::bind(&Printer::print2, this)));
        }

    ~Printer(){
        std::cout << "Final count: " << count << std::endl;
    }

    void print1(){
        if(count < 10){
            std::cout << "Timer1 Count: " << count << std::endl;
            ++count;
            timer1_.expires_at(timer1_.expiry() + std::chrono::seconds(1));
            timer1_.async_wait(asio::bind_executor(strand_, std::bind(&Printer::print1, this)));
        }
    }

    void print2(){
        if(count < 10){
            std::cout << "Timer2 Count: " << count << std::endl;
            ++count;
            timer2_.expires_at(timer1_.expiry() + std::chrono::seconds(1));
            timer2_.async_wait(asio::bind_executor(strand_, std::bind(&Printer::print2, this)));
        }
    }

private:
    asio::strand<asio::io_context::executor_type> strand_;
    asio::steady_timer timer1_;
    asio::steady_timer timer2_;
    int count;
};

int main(){
    asio::io_context io_context;
    Printer printer(io_context);
    std::thread t([&io_context](){ io_context.run(); });
    io_context.run();
    t.join();
    return 0;
}
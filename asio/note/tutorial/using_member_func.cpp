#include <functional>
#include <iostream>
#include <asio.hpp>

class Printer{
public:
    Printer(asio::io_context& io_context):
        timer_(io_context, std::chrono::seconds(1)),
        count_(0)
    {
        timer_.async_wait(std::bind(&Printer::print, this));
    }

    ~Printer(){
        std::cout << "Final count: " << count_ << std::endl;
    }

    void print(){
        if(count_ < 5){
            std::cout << "Count: " << count_ << std::endl;
            ++count_;
            timer_.expires_at(timer_.expiry() + std::chrono::seconds(1));
            timer_.async_wait(std::bind(&Printer::print, this));
        }
    }

private:
    asio::steady_timer timer_;
    int count_;
};

int main(){
    asio::io_context io_context;
    Printer printer(io_context);
    io_context.run();
    
    return 0;
}
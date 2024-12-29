#include <array>
#include <iostream>
#include <asio.hpp>



int main(int argc, char* argv[]){
    try{
        if(argc!= 2){
            std::cerr << "Usage: " << argv[0] << " <host>\n";
            return 1;
        }

        asio::io_context context;

        // 将指定为应用程序的服务器名称转换为Tcp终端节点
        asio::ip::tcp::resolver resolver(context);
        // 解析程序采用主机名和服务名称，并将其转换为终端节点列表
        // 使用argv[1]作为主机名，"daytime"作为服务名称，执行resolver.resolve()调用
        asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(argv[1], "daytime");

        asio::ip::tcp::socket socket(context);
        asio::connect(socket, endpoints);

        for(;;){
            // 使用std::array作为缓冲区，以便一次读取128个字节
            std::array<char, 128> buf;
            asio::error_code error;

            // buffer()函数会自动确定数组的大小，以防止缓冲区溢出
            // 当连接关闭时，read_some()会返回asio::error::eof错误
            size_t len = socket.read_some(asio::buffer(buf), error);

            if(error == asio::error::eof){
                break;
            } else if(error){
                throw asio::system_error(error);
            }

            std::cout.write(buf.data(), len);
        }
        
    } catch(const std::exception& e){
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
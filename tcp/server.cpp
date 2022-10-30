#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
    // 1. 初始化创建套接字
    // 参数 AF_INET 表示使用 IPv4 地址，SOCK_STREAM 表示使用面向连接的套接字，IPPROTO_TCP 表示使用 TCP 协议
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // 

    //将套接字和IP、端口绑定
    struct sockaddr_in serv_addr; 
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(1234);  //端口

    /**
     * 服务器端要用 bind() 函数将套接字与特定的 IP 地址和端口绑定起来，
     * 只有这样，流经该 IP 地址和端口的数据才能交给套接字处理。
     * 套接字 serv_sock 与特定的 IP 地址和端口绑定，IP 地址和端口都保存在 sockaddr_in 结构体中
     * int bind(int sock, struct sockaddr *addr, socklen_t addrlen);  
     * sock 为 socket 文件描述符，
     * addr 为 sockaddr 结构体变量的指针，
     * addrlen 为 addr 变量的大小，可由 sizeof() 计算得出
     * */
    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    /**
     * 2. 进入监听状态，等待用户发起请求
     * 对于服务器端程序，使用 bind() 绑定套接字后，还需要使用 listen() 函数让套接字进入被动监听状态，
     * 再调用 accept() 函数，就可以随时响应客户端的请求了
     * 让套接字处于被动监听状态。所谓被动监听，是指套接字一直处于“睡眠”中，直到客户端发起请求才会被“唤醒”
     * 
     * int listen(int sock, int backlog); linux
     * sock 为需要进入监听状态的套接字，backlog 为请求队列的最大长度。
     * 
     * 当套接字正在处理客户端请求时，如果有新的请求进来，套接字是没法处理的，只能把它放进缓冲区，
     * 待当前请求处理完毕后，再从缓冲区中读取出来处理。如果不断有新的请求进来，
     * 它们就按照先后顺序在缓冲区中排队，直到缓冲区满。这个缓冲区，就称为请求队列（Request Queue）
     * 当请求队列满时，就不再接收新的请求，对于 Linux，客户端会收到 ECONNREFUSED 错误，
     * 对于 Windows，客户端会收到 WSAECONNREFUSED 错误。
     * */
    listen(serv_sock, 20); 
    
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    char buffer[BUFSIZ];
    /**
     * 3. 建立连接
     * 当套接字处于监听状态时，可以通过 accept() 函数来接收客户端请求。
     * int accept(int sock, struct sockaddr *addr, socklen_t *addrlen);  //Linux
     * sock 为服务器端套接字，addr 为 sockaddr_in 结构体变量，addrlen 为参数 addr 的长度，可由 sizeof() 求得。
     * 程序一旦执行到 accept() 就会被阻塞（暂停运行），直到客户端发起请求。
     * 
     * accept() 返回一个新的套接字来和客户端通信，addr 保存了客户端的IP地址和端口号，而 sock 是服务器端的套接字，大家注意区分。
     * 后面和客户端通信时，要使用这个新生成的套接字，而不是原来服务器端的套接字。
     * 
     * 最后需要说明的是：listen() 只是让套接字进入监听状态，并没有真正接收客户端请求，listen() 后面的代码会继续执行，
     * 直到遇到 accept()。accept() 会阻塞程序执行（后面代码不能被执行），直到有新的请求到来。
     * */
    int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    read(clnt_sock, buffer, sizeof(buffer)); //接收客户端发来的数据

    // 4. 关闭套接字
    close(clnt_sock);
    close(serv_sock);
    return 0;
}
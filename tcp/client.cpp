#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
int main(){
    // 1. 创建套接字
    /**
     * int socket(int af, int type, int protocol);
     * af 为地址族（Address Family），也就是 IP 地址类型，常用的有 AF_INET 和 AF_INET6
     * type 为数据传输方式/套接字类型，常用的有 SOCK_STREAM（流格式套接字/面向连接的套接字） 
     * 和 SOCK_DGRAM（数据报套接字/无连接的套接字）
     * protocol 表示传输协议，常用的有 IPPROTO_TCP 和 IPPTOTO_UDP，分别表示 TCP 传输协议和 UDP 传输协议。
     * */
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //向服务器（特定的IP和端口）发起请求
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(1234);  //端口

    /**
     * 2. 建立连接
     * 通过 connect() 向服务器发起请求，服务器的IP地址和端口号保存在 sockaddr_in 结构体中。
     * 直到服务器传回数据后，connect() 才运行结束
     * int connect(int sock, struct sockaddr *serv_addr, socklen_t addrlen);
     * sock 为 socket 文件描述符，
     * addr 为 sockaddr 结构体变量的指针，
     * addrlen 为 addr 变量的大小，可由 sizeof() 计算得出
     * */
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
   
    char bufferWrite[BUFSIZ];
    char bufferRead[BUFSIZ];
    // 获取用户输入的字符串并发送给服务器
    printf("Input a string: ");
    scanf("%s", bufferWrite);
    write(sock, bufferWrite, sizeof(bufferWrite));

    // close(sock);
    return 0;
}
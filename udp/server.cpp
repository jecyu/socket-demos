#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

void error(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}
int main()
{
     // 1. 初始化创建套接字
    int sockfd;
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    struct sockaddr_in serv, client;

    //将套接字和IP、端口绑定
    serv.sin_family = AF_INET;
    serv.sin_port = htons(1234);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    bind(sockfd, (struct sockaddr*)&serv, sizeof(serv));

    char buffer[256];
    socklen_t l = sizeof(client);
    cout << "\ngoing to recv\n";
    int rc = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client, &l);
    if (rc < 0)
    {
        cout << "ERROR READING FROM SOCKET";
    }
    cout << "\n the message received is : " << buffer << endl;
    int rp = sendto(sockfd, "hi", 2, 0, (struct sockaddr *)&client, l);

    if (rp < 0)
    {
        cout << "ERROR writing to SOCKET";
    }
    close(sockfd);
}
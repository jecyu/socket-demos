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
    int sockfd;
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    struct sockaddr_in serv, client;

    serv.sin_family = AF_INET;
    serv.sin_port = htons(1234);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");

    char buffer[256];
    char readBuffer[2];
    socklen_t l = sizeof(client);
    socklen_t m = sizeof(serv);
    cout << "\ngoing to send\n";
    cout << "\npls enter the mssg to be sent\n";
    fgets(buffer, 256, stdin);
    sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&serv, m);
    recvfrom(sockfd, readBuffer, sizeof(readBuffer), 0, (struct sockaddr *)&client, &l);
    cout << "\n the message received is : " << readBuffer << endl;
    close(sockfd);
}
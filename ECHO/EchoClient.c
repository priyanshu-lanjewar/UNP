#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "unistd.h"
#include "string.h"

int main(int argc, char const *argv[])
{
    int n;
    char* data;
    int net_socket;
    net_socket = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(atoi(argv[2]));



    connect(net_socket, (struct sockaddr *) &server_address,sizeof(server_address));
    char msg[100];
    data = (char*)malloc(201);
    while(1)
    {
        scanf("%s",msg);
        write(net_socket,msg, strlen(msg));
        free(data);
        data = (char*)malloc(201);
        recv(net_socket,data,199,0);
        printf("%s",data);

    }

}
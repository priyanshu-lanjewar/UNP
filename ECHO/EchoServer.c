#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    int net_socket;
    net_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address, client_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5900);
    server_address.sin_addr.s_addr = inet_addr(argv[1]);


    bind(net_socket, (struct sockaddr*)&server_address,sizeof(server_address));


    // Listen Function creates Queue for incoming Request
    // Maintain 2 Queue 1 for incomplete 3 way handshake and other for those who has completed 3 way handshake
    listen(net_socket,10);
    char str[100];
    int fd;
    int c;
    while(1)
    {
        // accepts the request from completed queue
        // accept is blocking function: if there is no incoming request accept function will pause execution of program further unless it encounter any request
        fd=accept(net_socket,(struct sockaddr*)&client_address,&c);
        while (1) {
            int n = recv(fd, str, 99, 0);
            if(n==0)
                break;
            str[n]='\0';
            write(fd, str, strlen(str));

        }
        close(fd);
    }
}
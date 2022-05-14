#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char *argv[])
{
    int net_socket;
    net_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address, client_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5900);
    server_address.sin_addr.s_addr = inet_addr(argv[1]);

    bind(net_socket, (struct sockaddr*)&server_address,sizeof(server_address));

    listen(net_socket,10);
    char str[100];
    int fd;
    int c;
    int i=0;
    while(1)
    {
        fd=accept(net_socket,(struct sockaddr*)&client_address,&c);

        if(fork()==0) {

            close(net_socket);
            while (1) {
                int n = recv(fd, str, 99, 0);
                if (n == 0)
                    break;
                str[n] = '\0';
                printf("Message Recieved from Client %d : %s" , i, str);
                printf("\nSend Message : ");
                scanf("%s", str);
                write(fd, str, strlen(str));

            }
            close(fd);
        }else {
            i++;
            close(fd);
        }
    }
}
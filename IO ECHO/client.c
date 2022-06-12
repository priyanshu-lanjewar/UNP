#include "stdio.h"
#include "sys/socket.h"
#include "arpa/inet.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
int* net_socket;
struct sockaddr_in* server_address;
char* ip;
int* port;
int* size;
FILE *fp;
int* fd;
char* fname;
char* data;
int* n;
int* maxfd;
fd_set* read_set;


void allocate_mem(){
    net_socket = malloc(sizeof(int));
    server_address = malloc(sizeof(struct sockaddr_in));
    ip = malloc(17);
    port = malloc(sizeof(int));
    size = malloc(sizeof(int));
    fd = malloc(sizeof(int));
    fname = malloc(20);
    data = malloc(201);
    n = malloc(sizeof(int));
    maxfd = malloc(sizeof(int));
    read_set = malloc(sizeof(fd_set));
}
void deallocate_mem(){
    free(net_socket);
    free(server_address);
    free(ip);
    free(port);
    free(size);
    free(fd);
    free(fname);
    free(data);
    free(n);
    free(maxfd);
    free(read_set);
}

void input(){
    printf("Enter IP Address : ");
    scanf("%s",ip);
    printf("Enter Port Number : ");
    scanf("%d",port);
    printf("Enter File Name : ");
    scanf("%s",fname);
}

void socket_connect(){
    *net_socket = socket(AF_INET,SOCK_STREAM,0);
    server_address->sin_addr.s_addr = inet_addr(ip);
    // inet_aton(ip, server_address->sin_addr);
    // inet_pton(AF_INET, ip, server_address->sin_addr);
    //server_address->sin_addr.s_addr  = htonl(INADDR_ANY);
    server_address->sin_port = htons(*port);
    server_address->sin_family = AF_INET;
    *size = sizeof(struct sockaddr_in);
    connect(*net_socket, (struct sockaddr*) server_address, *size);
}
int main(){

    allocate_mem();
    input();
    socket_connect();

    printf("%s",fname);

    fp = fopen(fname,"r+");
    *fd = fileno(fp);
    printf("%d %p",*fd,fp);
    //*fd= fileno(stdin);

    FD_ZERO(read_set);
    while(1) {
        FD_SET(*fd, read_set);
        FD_SET(*net_socket, read_set);
        *maxfd = (*net_socket > *fd ? *net_socket : *fd) + 1;
        select(*maxfd, read_set, NULL, NULL, NULL);
        if (FD_ISSET(*fd, read_set)) {
            if (fgets(data, 200, fp) != NULL)
                write(*net_socket, data, strlen(data));
            else
                break;
        }
        if (FD_ISSET(*net_socket, read_set)) {
            *n = recv(*net_socket, data, 200, 0);
            if (*n == 0) {
                printf("Data Recieved\n");
                break;
            } else {
                data[*n] = '\0';
                printf("%s\n", data);
            }
        }
    }
    deallocate_mem();
    return  0;
}
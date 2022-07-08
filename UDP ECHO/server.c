#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include <unistd.h>

int main(){
    int net_socket = socket(AF_INET , SOCK_DGRAM, IPPROTO_UDP);
    if(net_socket < 0)
        perror("Failed Creating Socket : ");
    else
        printf("Socket Created Successfully\n");

    struct sockaddr_in add;
    add.sin_family = AF_INET;
    add.sin_port = htons(0);
    add.sin_addr.s_addr = inet_addr("0.0.0.0");
    int len = sizeof (struct sockaddr_in);
    int b = bind(net_socket,(struct sockaddr*)&add,len);
    if (b<0)
        perror("Error in Binding : ");
    else{
        printf("Bind Completed\n");
        getsockname(net_socket,(struct sockaddr*)&add,&len);
        printf("IP = %s\n", inet_ntoa(add.sin_addr));
        printf("Port = %d\n", ntohs(add.sin_port));
    }
    int n;
    char buf[200];
    while(1){
        //n = read(net_socket,buf,200);
        n = recvfrom(net_socket,buf,200,0,(struct sockaddr*)&add,&len);
        if (n<0)
            perror("Error While Reading : ");

        //n =  write(net_socket,buf,200);
        n = sendto(net_socket,buf,200,0,(struct sockaddr*)&add,len);
        if(n<0)
            perror("Error While Writing : ");
    }
    close(net_socket);
    return  0;

}
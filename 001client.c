#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int n;
    char data[201];
    int net_socket;
    net_socket = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5600);
    server_address.sin_addr.s_addr = inet_addr(argv[1]);

    connect(net_socket, (struct sockaddr *) &server_address,sizeof(server_address));
    n=recv(net_socket,data,200,0);
    char dt[20];
    for(int i=11;i<19;i++)
        dt[i-11]=data[i];
    char hh[3],mm[3];
    for(int i=0;i<2;i++)
        hh[i]=dt[i];
    for(int i=3;i<5;i++)
        mm[i-3]=dt[i];
    hh[2]=mm[2]='\0';
    printf("%d\n",n);

    int h = atoi(hh);
    int m = atoi(mm);
    if(m>=30)
        m-=30;
    else{
        h--;
        m+=60;
        m-=30;
    }
    if(h>=5)
        h-=5;
    else{
        //0=> 19 , 1 => 20, 2 => 21 , 3 => 22 , 4 => 23
        h-=5;
        h+=24;
    }
    printf("IST %s %s\n",hh,mm);
    printf("UTC %2d %2d\n",h,m);
    return 0;
}
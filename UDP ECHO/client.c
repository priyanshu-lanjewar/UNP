#include "stdio.h"
#include "arpa/inet.h"
#include "sys/socket.h"
#include "unistd.h"
#include "signal.h"

void timeout(int signal){
    printf("Timeout Occurred\nNo Response\nExiting....");
    _exit(0);
}

int main()
{
    signal(SIGALRM,timeout);
    int sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock<0)
        perror("Failed Creating Socket : ");
    else
        printf("Socket Created Successfully\n");

    struct sockaddr_in add;
    char ip[16];
    int po;
    printf("Enter IP : ");
    scanf("%s", ip);
    printf("Enter Port : ");
    scanf("%d",&po);
    add.sin_addr.s_addr = inet_addr(ip);
    add.sin_port = htons(po);
    add.sin_family =AF_INET;


    int len = sizeof (struct sockaddr_in);
    int n;
    char buf[200];

    while (fgets(buf,200,stdin)){
        len  = sizeof (struct sockaddr_in);
        n = sendto(sock,buf,200,0,(struct sockaddr*)&add,len);
        if (n<0)
            perror("Error While Writing : ");
        alarm(5);
        len  = sizeof (struct sockaddr_in);
        n = recvfrom(sock,buf,200,0,(struct sockaddr*)&add,&len);
        if (n<0)
            perror("Error While Reading : ");
        else{
            alarm(0);
            buf[n] = '\0';
            printf("Data Recieved : %s",buf);
        }
    }
    close(buf);
    return  0;

}
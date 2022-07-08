#include "stdio.h"
#include "arpa/inet.h"
#include "sys/socket.h"
#include "unistd.h"

int main()
{
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
    int cr = connect(sock,(struct sockaddr*)&add,len);
    struct sockaddr_in sa;

    if(cr<0)
        perror("Connection Failed ..");
    else{
        getpeername(sock,(struct sockaddr*)&sa,&len);
        printf("Server IP = %s\n", inet_ntoa(sa.sin_addr));
        printf("Server Port = %d\n", ntohs(sa.sin_port));
    }
    int n;
    char buf[200];

    while (fgets(buf,200,stdin)){
        n = write(sock,buf,200);
        if (n<0)
            perror("Error While Writing : ");
        n = read(sock,buf,200);
        if (n<0)
            perror("Error While Reading : ");
        buf[n] = '\0';
        printf("Data Recieved : %s",buf);
    }
    close(buf);
    return  0;

}
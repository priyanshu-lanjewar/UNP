#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
int main(){
    struct sockaddr_in addr;
    char ip[16],datetime[100];
    int n, p, choice;

    printf("Enter IP : ");
    scanf("%s",ip);
    printf("Enter Port : ");
    scanf("%d",&p);
    int nsocket=socket(AF_INET,SOCK_DGRAM,0);
    if(nsocket<0)
        perror("Error while creating Socket : ");
    else
        printf("Socket Created Successfully");

    addr.sin_family = AF_INET;
    addr.sin_port = htons(p);
    addr.sin_addr.s_addr = inet_addr(ip);

    int len = sizeof(struct sockaddr);

    while(1){
        printf("Enter 0 to Exit\nEnter 1 to Get Time\nInput Goes Here > ");
        scanf("%d",&choice);
        if(choice==0){
            close(nsocket);
            printf("Exiting..");
            exit(0);
        }
        else if(choice==1){
            strcpy(datetime,"datetime");
            int n = sendto(nsocket,datetime,100,0,(struct sockaddr*)&addr,len);
            if(n<0)
                perror("Error While Connecting : ");
            else{
                n = recvfrom(nsocket,datetime,100,0,(struct sockaddr*)&addr,&len);
                if(n<0)
                    perror("Error While Getting Time : " );
                datetime[n]='\0';
                printf("Time : %s\n",datetime);
            }
        }
        else{
            printf("Invalid Input\nTry Again...");
        }
    }

    return  0;
}
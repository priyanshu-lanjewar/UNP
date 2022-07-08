#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<time.h>
int main(){
    int nsocket=socket(AF_INET,SOCK_DGRAM,0);
    if(nsocket<0)
        perror("Error while creating Socket : ");
    else
        printf("Socket Created Successfully");
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(0);
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");

    int len = sizeof(struct sockaddr_in);

    int bnd = bind(nsocket,(struct sockaddr*)&addr,len);

    if(bnd<0)
        perror("Error While binding : ");
    else {
        printf("Bind Successful\n");
        getsockname(nsocket,(struct sockaddr*)&addr,&len);
        printf("IP : %s\n",inet_ntoa(addr.sin_addr));
        printf("Port : %d\n",ntohs(addr.sin_port));
    }
    int n;
    char datetime[100];

    while(1){
        len = sizeof(struct sockaddr_in);
        n = recvfrom(nsocket,datetime,100,0,(struct sockaddr*)&addr,&len);
        if (n<0)
            perror("Error While Receiving : ");
        else{
            time_t t = time(NULL);
            snprintf(datetime,100,"%s", ctime(&t));
            len = sizeof(struct sockaddr_in);
            n = sendto(nsocket,datetime,100,0,(struct sockaddr*) &addr,len);
            if(n<0)
                perror("Error While Sending : ");
        }

    }
    close(nsocket);
    return  0;
}
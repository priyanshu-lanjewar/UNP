#include "stdio.h"
#include "arpa/inet.h"

int main(){
    struct sockaddr_in s;
    char str[20];
    printf("Enter IP : ");
    scanf("%s",str);
    if(inet_aton(str,&s.sin_addr))
        printf("IP %s is Valid",str);
    else
        printf("IP %s is invalid.",str);
    return 0;
}
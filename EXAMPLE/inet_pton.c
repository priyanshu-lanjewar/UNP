#include "stdio.h"
#include "arpa/inet.h"
#include "strings.h"

int main(){
    struct sockaddr_in s;
    char str[20],ss[50];
    printf("Enter IP : ");
    scanf("%s",str);
    if(inet_pton(AF_INET6,str,&s.sin_addr)) {
        inet_ntop(AF_INET6, &s.sin_addr, ss, 50);
        printf("IP %s is Valid",ss);
    }
    else
        printf("IP %s is invalid.",str);
    return 0;
}
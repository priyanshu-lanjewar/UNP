#include "stdio.h"
#include "arpa/inet.h"
#include "strings.h"

int main(){

    /*
    struct sockaddr_in{
        sa_family_t sin_family;
        in_port_t sin_port;
        struct in_addr sin_addr;
    };

     struct in_addr{
        in_addr_t s_addr;
    };
    in_addr_t inet_addr(const char* str);
     */

    struct sockaddr_in s1, s2;
    char str[50];
    scanf("%s",str);
    s1.sin_addr.s_addr = inet_addr(str);
    inet_aton(str,&s2.sin_addr);

    if(bcmp(&s1.sin_addr,&s2.sin_addr,sizeof(struct in_addr))==0)
        printf("Same");
    else
        printf("Different");

    return  0;

}
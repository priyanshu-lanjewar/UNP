#include "stdio.h"
#include "arpa/inet.h"
#include "strings.h"

int main(){
    struct sockaddr_in s;
    char str[50];
    scanf("%s",str);
    printf("%s",inet_ntoa(s.sin_addr));

    return  0;

}
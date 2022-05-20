#include "stdio.h"
#include "arpa/inet.h"
int main(){
    char str[200]= "127.0.0.1";
    printf("%d",inet_addr(str));
    return 0;
}
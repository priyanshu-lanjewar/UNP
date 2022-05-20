#include "stdio.h"
#include "string.h"

int main(){
    int a = 23;
    int b = 23;

    if(memcmp(&a,&b,sizeof(int))==0)
        printf("Same\n");
    else
        printf("Differentn");

    a = 131073;
    b = 1;

    if(memcmp(&a,&b,2)==0)
        printf("Same\n");
    else
        printf("Different\n");
}
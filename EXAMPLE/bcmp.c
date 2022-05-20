#include "stdio.h"
#include "strings.h"

int main(){
    int a = 23;
    int b = 23;

    if(bcmp(&a,&b,sizeof(int))==0)
        printf("Same\n");
    else
        printf("Differentn");

    a = 131073;
    b = 1;

    if(bcmp(&a,&b,2)==0)
        printf("Same\n");
    else
        printf("Different\n");
}
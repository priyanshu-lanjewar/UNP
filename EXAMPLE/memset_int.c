#include "stdio.h"
#include "string.h"

int main(){
    int a = 131073;
    memset(&a,0,2);
    printf("%d",a);
    return 0;
}
#include "stdio.h"
#include "string.h"

int main(){
    char a[200] = "Hello";
    memset(a+2,67,2);
    for(int i=0;i<200;i++){
        printf("%c",a[i]);
    }
    printf("\n%s",a);
    return 0;
}
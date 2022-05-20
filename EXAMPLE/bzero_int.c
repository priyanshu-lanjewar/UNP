#include "stdio.h"
#include "strings.h"

int main() {
   int a[2] = {256,131073};
   bzero(&a[1],2);
   for(int i = 0; i<2;i++){
       printf(" %d |",a[i]);
   }
    return 0;
}
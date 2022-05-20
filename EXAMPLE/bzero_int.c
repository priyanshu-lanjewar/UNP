#include "stdio.h"
#include "strings.h"

int main() {
   int a[2] = {256,1};
   bzero(a,1);
   for(int i = 0; i<2;i++){
       printf(" %d |",a[i]);
   }
    return 0;
}
#include "stdio.h"
#include "strings.h"

int main() {
    char str[200] = "Hello";
    bzero(str + 2, 2);
    for (int i = 0; i < 200; i++)
        printf("%c", str[i]);
    printf("\n");
    printf("String : %s", str + 4);
    return 0;
}
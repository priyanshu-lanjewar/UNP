#include "stdio.h"
#include "string.h"

int main() {
    int a = 131073;
    int b = 1;
    memcpy(&a, &b, 2);
    printf("%d ", a);
    return 0;
}

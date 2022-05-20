#include "stdio.h"
#include "strings.h"

int main() {
    int a = 131073;
    int b = 1;
    bcopy(&a, &b, 2);
    printf("%d ", b);
    return 0;
}

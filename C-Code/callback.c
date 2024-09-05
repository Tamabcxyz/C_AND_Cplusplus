#include <stdio.h>

typedef int(*sum)(int, int);

int plusTwoNumbers(int a, int b){
    return a+b;
}

void funcCallback(sum cb, int a, int b) {
    printf("a+b=%d", cb(a,b));
}

int main()
{
    int a=5, b=10;
    funcCallback(plusTwoNumbers, a, b);
    return 0;
}
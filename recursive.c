#include<stdio.h>
//12
int recursive(int a)
{
    if(a == 0 || a == 1)
        return a+1;
    else
        return recursive(a - 1) + recursive(a / 2);
}
int main()
{
    int num;
    scanf("%d", &num);

    int answer = recursive(num);
    printf("%d\n", answer);
    return 0;
}

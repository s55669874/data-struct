#include<stdio.h>
//10

int main()
{
    int num1, num2;
    scanf("%d %d", &num1, &num2);
    int answer;
    while(num2 != 0)
    {
        answer = num2;
        num2 = num1%num2;
        num1 = answer;
    }
    printf("%d\n", answer);
    return 0;
}

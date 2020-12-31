#include<stdio.h>

int main()
{
    int answer[8], compare_to_scanf = 1;
    int num;
    scanf("%d",  &num);
    if(num  >= 0)
    {
        for(int i = 0; i < 8 ; i++)
        {
            answer[i] = num % 2;
            num /= 2;
        }
    }
    else
    {
        answer[7] = 1;
        num -= -128;
        for(int i = 0; i < 7 ; i++)
        {
            answer[i] = num % 2;
                num /= 2;
        }
    }
    for(int i = 7; i >= 0;  i--)
        printf("%d", answer[i]);
    printf("\n");
    return 0;
}

#include<stdio.h>
//8
int main()
{
    int num;
    while( scanf("%d", &num) ==  1)
    {
        if(num%2 == 0 || num%3 == 0)
        {
            printf("NO\n");
            continue;
        }
        for( int i = 2; i < num; i++)
        {
            if(i%2 == 0 || i%3 ==0)
                continue;
            else if(num%i == 0)
            {
                printf("NO\n");
                break;
            }
            else
            {
                printf("YES\n");
                break;
            }
        }
    }
    return 0;
}

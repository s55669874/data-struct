#include<stdio.h>
//9
int main()
{
    int num;
    while(scanf("%d", &num)== 1)
    {
        int counter = 0;
        int num_division[num];
        for(int i = 1; i <= num ; i++)
        {
            if(i%3 == 0)
                {
                    num_division[counter] = i;
                    counter++;
                }
        }
        int total = 0;
        for( int i = 0; i < counter; i++)
        {
            total += num_division[i];
        }
        printf("%d\n", total);
    }
    return 0;
}

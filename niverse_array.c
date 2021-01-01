#include<stdio.h>
int main()
{
    int x, y;
    while(scanf("%d", &x) == 1 && scanf("%d", &y) == 1)
    {
        int array[x][y];
        for(int i = 0; i < x; i++)
            for(int j = 0; j < y; j++)
                scanf("%d", &array[i][j]);

        int temp[y][x];
        for(int i = 0; i< y; i++)
            for(int j = 0; j < x; j++)
                temp[i][j] = array[j][i];

        for(int i = 0;i < y; i++)
        {
            for(int j = 0; j < x; j++)
            {
                printf("%d", temp[i][j]);
                if( j != x-1)
                    printf(" ");
            }
            printf("\n");
        }
    }
    return 0;
}

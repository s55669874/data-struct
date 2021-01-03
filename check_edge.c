#include<stdio.h>
int main()
{
    int num;
    scanf("%d", &num);
    int x, y;
    int map[102][102] = {0};
    for( int i = 0; i < num; i++)
    {
        scanf("%d %d", &x, &y);
        for(int j = 1;j <= x; j++)
            for(int k = 1;k <= y; k++)
                scanf("%d", &map[j][k]);
        if(i > 0)
            printf("\n");
        for(int j = 1; j <= x; j++)
        {
            for(int k = 1; k <= y; k++)
            {
                if(map[j][k] == 0)
                    printf("_ ");
                else if(map[j][k] == 1)
                    if(map[j-1][k]==0 ||map[j+1][k]==0 ||map[j][k-1]==0 ||map[j][k+1]==0)
                    printf("0 ");
                else
                    printf("_ ");
            }
            if(i != num )
                printf("\n");
        }
    }
    return 0;
}

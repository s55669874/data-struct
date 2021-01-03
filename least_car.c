#include<stdio.h>
int main()
{
    int n;
    scanf("%d", &n);
    int car[n][2];
    for(int i = 0;i < n; i++)
            scanf("%d %d", &car[i][0], &car[i][1]);

    int map[25] = {0};
    for(int i = 0; i < n; i++)
        for(int j = car[i][0]; j < car[i][1]; j++)
            map[j]++;
    int ans = 0;
    for(int j = 0;j < 25; j++)
        if(map[j] > ans)
            ans = map[j];
    printf("%d\n", ans);
    return 0;

}

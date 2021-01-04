#include<stdio.h>

int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}
int main()
{
    int n, t, m, k;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        scanf("%d %d %d", &t, &m, &k);
        int gift[k];
        for (int j = 0; j < k; j++)
            scanf("%d", &gift[j]);
        qsort(gift, k, sizeof(int), cmp);
        for (int j = 0; j < m; j++)
            sum += gift[j];
        if (sum <= t)
            printf("%d\n", sum);
        else
            printf("Impossible\n");
    }
}


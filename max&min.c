#include<stdio.h>

int cmp(const void *a, const void *b)
{
    if (*(double *)a - *(double *)b > 0)
        return 1;
    return 0;
}
int main()
{
    double num[11];
    for (int i = 0; i < 10; i++)
        scanf("%lf", &num[i]);
    qsort(num, 10, sizeof(double), cmp);
    printf("maximum:%.2lf\n", num[9]);
    printf("minimum:%.2lf\n", num[0]);
}


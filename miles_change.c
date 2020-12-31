#include<stdio.h>

int main()
{
    int A;
    while(scanf("%d", &A) == 1)
    {
        double B = A * 1.6 ;
        printf("%.1f\n", B);
    }
    return 0;
}

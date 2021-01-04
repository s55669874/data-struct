#include<stdio.h>

int main()
{
    double weight;
    int check;
    while(scanf("%lf %d", &weight, &check) != EOF)
    {
        if(check == 1)
            printf("%.1lf\n", (weight - 80) * 0.7);
        else if(check == 2)
            printf("%.1lf\n", (weight - 70) * 0.6);
    }
    return 0;
}

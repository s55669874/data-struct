#include<stdio.h>

int main()
{

    int num;
    scanf("%d", &num);
    if (num <= 120)
    {
        printf("Summer months:%.2lf\n", num * 2.1);
        printf("Non-Summer months:%.2lf\n", num * 2.1);
    }
    else if (num > 120 && num <= 330)
    {
        printf("Summer months:%.2lf\n", 120 * 2.1 + (num - 120) * 3.02);
        printf("Non-Summer months:%.2lf\n", 120 * 2.1 + (num - 120) * 2.68);
    }
    else if (num > 330 && num <= 500)
    {
        printf("Summer months:%.2lf\n", 120 * 2.1 + 210 * 3.02 + (num - 330) * 4.39);
        printf("Non-Summer months:%.2lf\n", 120 * 2.1 + 210 * 2.68 + (num - 330) * 3.61);
    }
    else if (num > 500 && num <= 700)
    {
        printf("Summer months:%.2lf\n", 120 * 2.1 + 210 * 3.02 + 170 * 4.39 + (num - 500) * 4.97);
        printf("Non-Summer months:%.2lf\n", 120 * 2.1 + 210 * 2.68 + 170 * 3.61 + (num - 500) * 4.01);
    }
    else
    {
        printf("Summer months:%.2lf\n", 120 * 2.1 + 210 * 3.02 + 170 * 4.39 + 200 * 4.97 + (num - 700) * 5.63);
        printf("Non-Summer months:%.2lf\n", 120 * 2.1 + 210 * 2.68 + 170 * 3.61 + 200 * 4.01 + (num - 700) * 4.5);
    }
}

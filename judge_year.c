#include<stdio.h>
//36
int main()
{
    int year;
    while(scanf("%d", &year) == 1)
    {
        if(( year % 400 ) == 0)
            printf("Bissextile Year\n");
        else if((year % 4) == 0 && (year % 100) != 0)
            printf("Bissextile Year\n");
        else
            printf("Common Year\n");
    }
}

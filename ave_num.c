#include<stdio.h>

int main()
{
    char num[2000];
    while (fgets(num, 1000, stdin) != NULL)
    {
        int size = 0, len = strlen(num);
        double avg = 0.0;
        char n[110], *ptr = num;
        while (*ptr != '\n' && ptr < num + len)
        {
            char *qtr = n;
            while (*ptr != ' ' && *ptr != '\n')
                *qtr++ = *ptr++;
            *qtr = '\0';
            ptr++;
            avg = avg + atoi(n);
            *n = '\n';
            size++;
        }
        printf("Size: %d\n", size);
        printf("Average: %.3lf\n", avg / size);
    }
}

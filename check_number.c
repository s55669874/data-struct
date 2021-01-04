#include<stdio.h>

int main()
{
    char str[11];
    scanf("%s", str);
    int sum = 0;
    if (str[0] < 'I')
        sum = (str[0] - 'A' + 10) / 10 + ((str[0] - 'A' + 10) % 10) * 9;
    else if (str[0] == 'I')
        sum = 3 + 4 * 9;
    else if (str[0] < 'O')
        sum = (str[0] - 'A' + 9) / 10 + ((str[0] - 'A' + 9) % 10) * 9;
    else if (str[0] == 'W')
        sum = 3 + 2 * 9;
    else if (str[0] == 'X')
        sum = 3;
    else if (str[0] == 'Y')
        sum = 3 + 1 * 9;
    else
        sum = (str[0] - 'A' + 8) / 10 + ((str[0] - 'A' + 10) % 8) * 9;
    for (int i = 1; i < 9; i++)
        sum = sum + (str[i] - '0') * (9 - i);
    sum = sum + (str[9] - '0');
    if (sum % 10 == 0)
        printf("CORRECT!!!\n");
    else
        printf("WRONG!!!\n");
}


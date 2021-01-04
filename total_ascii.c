#include <stdio.h>
int main()
{
    int num;
    char str[33];
    fgets(str, 33, stdin);
    num = atoi(str);
    for (int i = 0; i < num; i++)
    {
        fgets(str, 33, stdin);
        int len = strlen(str);
        int sum = 0;
        for (int j = 0; j < len; j++)
            if (str[j] >= 32 && str[j] <= 126)
                sum = sum + str[j];

        printf("%d\n", sum);
    }
}

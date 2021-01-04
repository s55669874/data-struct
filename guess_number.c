#include<stdio.h>
int main()
{
    char str[5], cmp_str[5];
    scanf("%s\n", str);
    while (scanf("%s\n", cmp_str) != EOF)
    {
        if (strcmp(cmp_str, "0000") == 0)
            break;
        int a = 0;
        int b = 0;
        for (int i = 0; i < 4 ; i++) {
            if (str[i] == cmp_str[i])
                a++;
            else
            {
                for (int j = 0; j < 4; j++)
                    if (cmp_str[i] == str[j])
                    {
                        b++;
                        break;
                    }
            }
        }
        printf("%dA%dB\n", a, b);
    }
}

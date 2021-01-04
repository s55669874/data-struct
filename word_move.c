#include<stdio.h>

int main()
{
    int change;
    char string[101];
    fgets(string, 101, stdin);
    scanf("%d", &change);
    for (int i = 0; i < strlen(string); i++)
    {
        if (string[i] >= 'A' && string[i] <= 'Z')
            string[i] = (string[i] - 'A' + change) % 26 + 'A';
        else if (string[i] >= 'a' && string[i] <= 'z')
            string[i] = (string[i] - 'a' + change) % 26 + 'a';
        else if (string[i] >= '0' && string[i] <= '9')
            string[i] = (string[i] - '0' + change) % 10 + '0';
    }
    printf("%s", string);
}

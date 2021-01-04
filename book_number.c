#include<stdio.h>

int main() {
    char tmp;
    int num[11];
    //printf("%d", '0');
    for (int i = 0; i < 10; i++)
        {
        scanf("%c", &tmp);
        if (tmp == ' ')
        {
            i--;
            continue;
        }
        else if (tmp == 'X')
            num[i] = 10;
        else
            num[i] = tmp - 48;
    }
    int new_num[11];
    new_num[0] = num[0];
    for (int i = 1; i < 10; i++)
        new_num[i] = num[i] + new_num[i - 1];

    int sum = 0;
    for (int i = 0; i < 10; i++)
        sum = sum + new_num[i];
    if (sum % 11 == 0)
        printf("YES\n");
    else
        printf("NO\n");
}


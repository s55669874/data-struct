#include<stdio.h>

int main()
{
    int num[5], big = 0;
    for (int i = 0; i < 4; i++)
        scanf("%d", &num[i]);

    if (num[0] == num[1] && num[1] == num[2] && num[2] == num[3] && num[3] == num[0])
        printf("WIN\n");
    else if ((num[0] == num[1] && num[1] == num[2] && num[2] != num[3]) || (num[0] == num[1] && num[1] != num[2] && num[1] == num[3]) ||
             (num[1] == num[2] && num[2] == num[3] && num[0] != num[1]) || (num[0] == num[2] && num[2] == num[3] && num[0] != num[1]))
        printf("R\n");
    else if (num[0] != num[1] && num[0] != num[2] && num[0] != num[3]  && num[1] != num[2] && num[1] != num[3] && num[2] != num[3])
        printf("R\n");
    else
    {
        if (num[2] + num[3] > big && num[0] == num[1])
            big = num[2] + num[3];
        if (num[1] + num[3] > big && num[0] == num[2])
            big = num[1] + num[3];
        if (num[1] + num[2] > big && num[0] == num[3])
            big = num[1] + num[2];
        if (num[0] + num[3] > big && num[1] == num[2])
            big = num[0] + num[3];
        if (num[0] + num[2] > big && num[1] == num[3])
            big = num[0] + num[2];
        if (num[0] + num[1] > big && num[2] == num[3])
            big = num[0] + num[1];
        printf("%d\n", big);
    }
}

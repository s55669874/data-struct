#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int main()
{
    int money, a1, a2, a3;
    scanf("%d,%d,%d,%d", &money, &a1, &a2, &a3);
    int sum = a1 * 15 + a2 * 20 + a3 * 30;
    int num_fif = 0, num_ten = 0, num_one = 0;
    if (sum > money)
        printf("0\n");
    else
    {
        sum = money - sum;
        num_fif = sum / 50;
        sum = sum % 50;
        num_ten = sum / 5;
        sum = sum % 5;
        num_one = sum;
        printf("%d,%d,%d\n", num_one, num_ten, num_fif);
    }
    return 0;
}

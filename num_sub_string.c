#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//16
int main()
{
    char sub_string[128], str[512];
    scanf(" %s %s", sub_string, str);
    int ans = 0, mark = 0;
    for(int i = 0; i < strlen(str); i++)
    {
        mark = 0;
        for(int j = 0; j < strlen(sub_string); j++)
            {
                if(str[i + j] == sub_string[j])
                    mark = 1;
                else
                {
                    mark = 0;
                    break;
                }
            }
            if(mark == 1)
                ans++;
    }
    printf("%d\n", ans);
    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//15
int main()
{//65 ~90 97~122
    char string[100];
    fgets(string, 100, stdin);
    //printf("%s", string);
    int times[26] = {0};
    int times1[26] = {0};
    int num_sub_string = 1;
   for(int i = 0;i < strlen(string); i++)
   {
        if(string[i] >= 'A' && string[i] <= 'Z')
            times1[string[i] - 'A']++;
        else if(string[i] >='a' && string[i] <= 'z')
            times[string[i] - 'a']++;
        else if(string[i] == ' ')
            num_sub_string++;
   }
   //printf("\n");
   printf("%d\n", num_sub_string);
   for(int i = 0; i < 26; i++)
   {
        if(times[i] != 0 || times1[i] != 0)
        {
            if(times[i] != 0)
                printf("%c : %d\n", 'a'+i, times[i]+times1[i]);
            else if(times1[i] != 0)
                printf("%c : %d\n", 'a'+i, times[i]+times1[i]);
        }
   }
   return 0;
}

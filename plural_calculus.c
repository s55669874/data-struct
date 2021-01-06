#include <stdlib.h>
#include <stdio.h>
//7
int main(){
    int num;
    int a,b,c,d;
    char do_what;
    scanf("%d",&num);
    for(int i=0; i<num; i++)
    {
        scanf(" %c %d %d %d %d", &do_what,& a, &b, &c, &d);
        switch(do_what)
        {
            case '+':
                printf("%d %d\n",a+c,b+d);
                break;
            case '-':
                printf("%d %d\n",a-c,b-d);
                break;
            case '*':
                printf("%d %d\n",a*c-b*d,b*c+a*d);
                break;
        }
    }
}

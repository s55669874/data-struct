#include<stdio.h>
//24
int main()
{
    long double sum = 0.0, r;
    long long int n, p;
    scanf("%Lf %lld %lld", &r, &n, &p);
    //printf("%lf", r);
    for(int i = 0; i < n; i++)
    {
        sum = sum + p;
        sum = sum * (1.0 + r);
    }
    long long int ans = sum;
    printf("%lld\n", ans);
}

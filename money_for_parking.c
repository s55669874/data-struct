#include<stdio.h>
//4
int main()
{
    int time1_hour, time1_min, time2_hour, time2_min;
    scanf("%d %d", &time1_hour, &time1_min);
    scanf("%d %d", &time2_hour, &time2_min);
    int money = 0,time_change = 0;
    time_change = (time2_hour - time1_hour) * 60 + time2_min  - time1_min;
    if(time_change  > 240 )
    {
        money += ((time_change - 240) / 30) * 60;
        time_change = 240;
    }
    if(time_change > 120 && time_change <= 240)
    {
        money += ((time_change - 120) / 30) * 40;
        time_change = 120 ;
    }
    if(time_change <= 120)
    {
        money += (time_change / 30) * 30 ;
    }
    printf("%d\n", money);
    return 0;
}

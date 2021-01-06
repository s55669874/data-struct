#include<stdio.h>
//30
int main()
{
    int month = 0, day = 0;
    scanf("%d %d", &month, &day);
    switch (month)
    {
        case 1:
            if (day <= 20 && day >0)
                printf("Capricorn\n");
            else if (day <= 31 && day > 20)
                printf("Aquarius\n");
            break;
        case 2:
            if (day <= 18 && day >0)
                printf("Aquarius\n");
            else if (day <= 29 && day > 18)
                printf("Pisces\n");
            break;
        case 3:
            if (day <= 20 && day > 0)
                printf("Pisces\n");
            else if (day <= 31 && day > 20)
                printf("Aries\n");
            break;
        case 4:
            if (day <= 20 && day >0)
                printf("Aries\n");
            else if (day <= 30 && day > 20)
                printf("Taurus\n");
            break;
        case 5:
            if (day <= 20 && day >0)
                printf("Taurus\n");
            else if (day <= 31 && day > 20)
                printf("Gemini\n");
            break;
        case 6:
            if (day <= 21 && day >0)
                printf("Gemini\n");
            else if (day <= 30 && day > 21)
                printf("Cancer\n");
            break;
        case 7:
            if (day <= 22 && day >0)
                printf("Cancer\n");
            else if (day <= 31 && day > 22)
                printf("Leo\n");
            break;
        case 8:
            if (day <= 22 && day >0)
                printf("Leo\n");
            else if (day <= 31 && day > 22)
                printf("Virgo\n");
            break;
        case 9:
            if (day <= 22 && day >0)
                printf("Virgo\n");
            else if (day <= 30 && day > 22)
                printf("Libra\n");
            break;
        case 10:
            if (day <= 22 && day >0)
                printf("Libra\n");
            else if (day <= 31 && day > 22)
                printf("Scorpio\n");
            break;
        case 11:
            if (day <= 21 && day >0)
                printf("Scorpio\n");
            else if (day <= 30 && day > 21)
                printf("Sagittarius\n");
            break;
        case 12:
            if (day <= 21 && day >0)
                printf("Sagittarius\n");
            else if (day <= 31 && day > 21)
                printf("Capricorn\n");
            break;
    }
}

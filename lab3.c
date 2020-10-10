#include<stdio.h>
#include<locale.h>


void main(void){
    int days = 0;
    int year;
    printf("Введите год: ");
    scanf("%d", &year);

    int our_year = 0;
    if (year % 4 == 0){
        our_year = 366;
    }
    else{
        our_year = 365;
    }

    int year2 = year - 1;
    days = (year/4)*366 + (year-(year/4)*365);
    int ostatok = days % 7;
    int result = ostatok - 1; //Название дня с которого начинается наш год


    int start_october_day = 140%7 + result;
    int end = 1;
    for (int i = 0; start_october_day != 7; i++){
        start_october_day++;
        end++;
    }
    if (end > 7){
        end-=7;
    }
    printf("Воскресенье приходится на %d число.", end);
}

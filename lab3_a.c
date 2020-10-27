#include<stdio.h>
#include<locale.h>
#include<conio.h>
#include<stdlib.h>


int main(){
    setlocale(LC_ALL, "Russian");
    int neVesokos[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int Vesokos[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int a, b, c, a1, b1, c1;
point:
    printf("Введите первую дату: день/месяц/год\n");
    scanf("%d%d%d", &a, &b, &c);
    system("cls");
    printf("Введите первую дату: день/месяц/год\n");
    scanf("%d%d%d", &a1, &b1, &c1);

    if(a > 31 || a1 > 31 || a < 0 || a1 < 0 ){
        printf("Введены неверные данные!\n");
        goto point;
    }
    
    if(b > 12 || b1 > 12 || b1 < 0 || b1 < 0 ){
        printf("Введены неверные данные!\n");
        goto point;
    }

    if(c < 0 || c1 < 0){
        printf("Введены неверные данные!\n");
        goto point;
    }

    int day, day1; day = day1 = 0;
    day = a + (b * 31) + (c * 365);
    day1 = a1 + (b1 * 31) + (c1 * 365);
    int result = day - day1; 
    if (result < 0){
        result *= -1;
    }

    printf("Разница между датами %d дней!\n", result);

    _getch();
}

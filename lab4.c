#include<stdio.h>
#include<locale.h>
#define kl 10
//Программа работает с любой размероностью массива.
//Массив принимается только одномерный.

int main(){
    setlocale(LC_ALL, "Russian");
    int ms[kl];
    int prd = 0;
    int appent;
    for (int i = 0; i < kl; i++){
        scanf("%d", &appent);
        ms[i] = appent; //Окончание заполнения массива.
    }

    int number; 

    for (int i = 0; i < kl -1; i++){
        if((ms[i] * ms[i+1]) > prd){
            prd = ms[i] * ms[i+1];
            number = i + 1;
        }
        else{
            continue;
        }
    }

    printf("Введенный массив(размероность %d элементов): \n", kl);
    for(int b = 0; b < kl; b ++){
        printf("[%d] ", ms[b]);
    }
    printf("\n");
    printf("Наибольшее произведение соседних элементов =  %d\n", prd);
    printf("Индексы данных чисел: %d, %d\n", number, number - 1);
}

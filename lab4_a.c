#include<stdio.h>
#include<locale.h>
#include<conio.h>
#define kl 10

int factorial(int);

int main(){
    setlocale(LC_ALL, "Russian");
    int ms[kl];
    printf("Введите числа в массив(Всего %d): ", kl);
    for (int i = 0; i < kl; i++){
        int append;
        scanf("%d", &append);
        ms[i] = append;
    }//Конец наполнения массива эллементами.


    int schetchik = 0;
    for(int i = 0; i < kl; i++){
        if (ms[i] < 0){
            ms[i] = 0;
            schetchik++;
        }
        else{
            continue;
        }
    }
    printf("Количество замен: %d\n\n", schetchik);

    for(int i = 0; i < kl; i++){
        printf("%d ", ms[i]);
    } 
    printf("\n");
    printf("Факториал количества замен = %d\n", factorial(schetchik));

    _getch();
}

int factorial(int a){ //Функция нахождения факторила.
        int _DIGITLS = 1;
        for (int i = 1; i < (a + 1); i++){
            _DIGITLS *= i;
        }
        return _DIGITLS;
    }

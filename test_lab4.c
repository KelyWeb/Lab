#include<stdio.h>
#include<locale.h>
#include<stdlib.h>
#define kl 15


void fillMass(int a[], int b); //Функция наполнения массива.
void showMass(int a[], int b); //Функция вывода массива. 
void checkPosled(int a[], int b); //Функция проверки на количество послежовательностей.


int main(){
    int ms[kl];
    //Тестирование функции
    for (int i = 0; i < 5; i++){
        fillMass(ms, kl);
        showMass(ms, kl);
        checkPosled(ms, kl);
        printf("\n");
    }

}


//Функция наполнения массива элементами.
void fillMass(int a[], int b){
    for(int i = 0; i < b; i++){
        a[i] = rand() % 100;
    }
}

//Функция вывода элементов массива.
void showMass(int a[], int b){
    for (int i = 0; i < b; i++){
        printf("[%d] ", a[i]);
    }
}

void checkPosled(int a[], int b){
    int schetchik = 0;
    int t = 1;
    while (t < kl){
        int g = 0;
        while(a[t] > a[t-1]){
            t++;
            g++;
            continue;
        }
        if (g > 0){
            schetchik++;
        }        
        else{
            t++;
            continue;
        }
    }
    printf("\nКоличество возрастающих последователностей в массиве: %d\n", schetchik);
}

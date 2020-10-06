#include<stdio.h>
#include<locale.h>
#include<stdlib.h>
#define SIZE 20

void fillMass(int a[], int b);
void printMass(int a[], int b);
void bubble_sort(int a[], int b);

int main(){
    int ms[SIZE];
    fillMass(ms, SIZE);
    printMass(ms, SIZE);
    bubble_sort(ms, SIZE);
    printMass(ms, SIZE);
}

void fillMass(int a[], int b){
    for (int i = 0; i < b; i++){
        int APP_DIG = rand() % 100;
        a[i] = APP_DIG;
    }
}

void printMass(int a[], int b){
    for (int i = 0; i < b; i++){
        printf("[%d] ", a[i]);
    }
    printf("\n");
}

void bubble_sort(int a[], int b){
    int PONIGENIE = b;
    for (int i = 0; i < b; i++){ //пробежка каждого эелмента массива.
        for (int t = 0; t < PONIGENIE; t++){
            if (a[t] > a[t+1]){
                int EXTRACT = a[t];
                a[t] = a[t+1];
                a[t+1] = EXTRACT;
            }
            else{
                continue;
            }
        }
        PONIGENIE--;
    }
}

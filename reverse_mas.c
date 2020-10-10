#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void reversMass(int a[], int b);


void main(void){
    int ms[10] = {4, 1, 8, 4, 2, 9, 3, 0, 6, 7};
    reversMass(ms, 10);

    for (int i = 0; i < 10; i++){
        printf("[%d] ", ms[i]);
    }
}


void reversMass(int a[], int b){
    for (int i = 0; i < b/2; i++){
        int EXTAND = a[b - i - 1];
        a[b - i - 1] = a[i];
        a[i] = EXTAND;
    }
}

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

int index2(int a, int b, int c);


int main(void){    
    for (int i = 100000; i < 999999; i++){
        int sum1, sum2;
        sum1 = 0;
        sum2 = 0;
        for(int d = 0; d < 3; d++){
            sum1 += index2(i, d, 6);
        }
        for (int g = 3; g < 6; g++){
            sum2 += index2(i, g, 6);
        }
        if (sum1 == sum2){
            printf("%d\n", i);
        }
    }
    _getch();
}

int index2(int a, int b, int c){
    int ms[c];
    for (int i = 0; i < c; i++){
        ms[i] = a % 10;
        a /= 10;
    }
    return ms[b];
}

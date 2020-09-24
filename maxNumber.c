#include<stdio.h>

int max2(int, int);

int main(){
    int a, b, c;
    printf("Введите число a & b & c: \n");
    scanf("%d%d%d", &a, &b, &c);
    printf("Самое большое число из 3: ");
    printf("%d\n", max2(max2(a, b), c));
}


int max2(int a, int b){
    if (a >= b){
        return a;
    }
    else{
        return b;
    }
}

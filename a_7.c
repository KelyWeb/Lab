#include<stdio.h>
#include<stdlib.h>


int main(){
    const int n = 100;
    char * symbols = (char *)malloc(sizeof(char) * n);
    printf("Введите символы (%d):\n", n);
    fgets(symbols, n, stdin);


    int i = 0;
    while(symbols[i] != ':'){
        i++;
    }
    i++;
    while(symbols[i] != ':'){
        if(symbols[i] == '\0') break;
        putchar(symbols[i]);
        i++;
    }
}

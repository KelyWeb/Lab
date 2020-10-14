#include<stdio.h>
#include<locale.h>
#include<stdlib.h>
#include<conio.h>
#define kl 20


void main(void){
    setlocale(LC_ALL, "Russian");
    int ms[kl];
    for(int i = 0; i < kl; i++){
        int append;
        scanf("%d", &append);
        ms[i] = append;
    }
    //Окончание наполнения массива.
    
    int schetchik = 0;
    int t = 1;
    point:
    while (t < kl){
        int a = 0;
        while(ms[t] > ms[t-1]){
            t++;
            a++;
            continue;
        }
        if (a > 0){
            schetchik++;
        }        
        else{
            t++;
            continue;
        }
    }
        

    system("cls");
    for(int g = 0; g < kl; g++){
        printf("[%d] ", ms[g]);
    }
    printf("\n");

    printf("Совпадений: %d", schetchik);
    _getch();

} 

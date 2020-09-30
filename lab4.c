#include<stdio.h>
#include<locale.h>
#define kl 10

int main(){
    int ms[kl];
    int prd = 0;
    int appent;
    for (int i = 0; i < kl; i++){
        scanf("%d", &appent);
        ms[i] = appent; //Окончание заполнения массива.
    }

    for (int i = 0; i < kl -1; i++){
        if((ms[i] * ms[i+1]) > prd){
            prd = ms[i] * ms[i+1];
        }
        else{
            continue;
        }
    }
    
    printf("Наибольшее произведение соседних элементов =  %d", prd);

    

    


}

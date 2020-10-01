#include<stdio.h>
#include<locale.h>
#define kl 5

int main(){
    int ms[5][5];
    for(int i = 0; i < kl; i++){
        for (int b = 0; b < kl; b++){
            int apend;
            scanf("%d", &apend);
            ms[i][b] = apend;
        }
    } 


    for (int i = 1; i < kl; i++){ //Начало(2)
        int max = ms[1][1];
        if (ms[i][i] > max){
            max = ms[i][i];
            for (int b = i; b > 0; b--){
                if (max < ms[i][b]){
                    max = ms[i][b];
                }
                else{
                    continue;
                }
            }
        }
        else{
            continue;
        }
        printf("\n%d ", max);
    }//Конец(2)



    for (int i = 0; i < kl; i++){ //Вывод массива.
        for (int b = 0; b < kl; b++){
            printf("%d ", ms[i][b]);
        }
        printf("\n");
    }
    



}

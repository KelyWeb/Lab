#include<stdio.h>
#include<locale.h>



int main(){
    int ms[3][3] = {{-20, 2, -13}, {-5, 1, -1}, {-43, -2, 1}};
    for (int i = 0; i < 3; i++){ //Взятие строки на проверку.
        for(int b = 0; b < 3; b++){ 
            if (ms[i][b] >= 0){//Проверка каждого элемента строки на <0.
                continue;
            } 
            else{
                int inster;
                inster = ms[i][b]; //Взятие отрицательно числа из строки на проверку.
                for(int t = 0; t < 3; t++){
                    if(inster > ms[i][t]){
                        int promt = ms[i][t];
                        ms[i][t] = inster;
                        ms[i][b] = promt;
                    }
                    
                    else{
                        continue;
                    }
                }
            }



        }



    }

    for (int i = 0; i < 3; i++){
        for (int b = 0; b < 3; b++){
            printf("%d ", ms[i][b]);
        }
        printf("\n");
    }
}

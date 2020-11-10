#include<stdio.h>
#include<locale.h>
#include<stdlib.h>


int main(void){
    setlocale(LC_ALL, "Russian");
    int **ms;
    int s_kl, st_kl;
    printf("Введите количество строк в матрице: ");
    scanf("%d", &s_kl);
    printf("Введите количество столбцов в матрице: ");
    scanf("%d", &st_kl);
    system("clear");
    printf("Матрица будет состоять из %d строк и %d столбцов\n", s_kl, st_kl);

    //Память под массив.
    ms = (int **)malloc(s_kl*sizeof(int *));
    for(int i = 0; i < s_kl; i++){
        ms[i] = (int *)malloc(st_kl*sizeof(int));
    }


    //Наполнения массива.
    printf("Введите элементы массива:\n ");
    for(int i = 0; i < s_kl; i++){
        for(int b = 0; b < st_kl; b++){
            scanf("%d", &ms[i][b]);
        }
    }
    system("clear");
    

    //Вывод введенного массива.
    printf("Матрица: \n");
    for(int i = 0; i < s_kl; i++){
        for(int b = 0; b < st_kl; b++){
            printf("[%d] ", ms[i][b]);
        }
        printf("\n");
    }

    int point2 = 0;
    //Определение, является ли матрица латинским квадратом.
    for(int i = 0; i < s_kl; i++){
        point2++;
        int point = 0;
        int * check;
        int position = 0;
        check = (int *)malloc((i+i)*sizeof(int));
        for(int b = 0; b < st_kl; b++){
            check[position] = ms[i][b];
            check[position+1] = ms[b][i];
            position += 2;
        }

        /*
        printf("\n");
        for(int k = 0; k < s_kl*2; k++){
            printf("[%d] ", check[k]);
        }
        */

        for(int j = 0; j < s_kl*2; j++){
            int number = check[j];
            int schetchik = 0;
            for(int e = 0; e < s_kl*2; e++){
                if (check[e] == number){
                    schetchik++;
                    if(schetchik > 2){
                        printf("Матрица не является латинским квадратом.\n");
                        point++;
                        free(check);
                        break;
                    }
                }
                else{
                    continue;
                }
                
            }
            break;
        }
        if (point == 1) break;
        if (point2 == s_kl) printf("Матрица является латинским квадратом.\n");
    }


}



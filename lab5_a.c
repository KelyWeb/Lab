#include<stdio.h>
#include<conio.h>
#include<locale.h>
#define SIZE_MS 4


int main(){
    int ms[SIZE_MS][SIZE_MS];
    for (int i = 0; i < SIZE_MS; i++){
        for (int b = 0; b < SIZE_MS; b++){
            int append_digit;
            scanf("%d", &append_digit);
            ms[i][b] = append_digit;
        }
    }//Окончание наполнения массива.
    printf("\n");


    for(int i = 0; i < SIZE_MS; i ++){
        for(int b = 0; b < SIZE_MS; b++){
            printf("%d ", ms[i][b]);
        }
        printf("\n");
    }
    printf("\n");
    

    int a = 1;
    for(int i = 0; i < SIZE_MS; i++){
        for (int b = a; b < SIZE_MS; b++){
            int INVOLVE;
            int INVOLVE_2;
            INVOLVE = ms[i][b]; //Ложим элемент по строке.
            INVOLVE_2 = ms[b][i];
            ms[i][b] = INVOLVE_2;
            ms[b][i] = INVOLVE;
        }
        a++;
    }


    for(int i = 0; i < SIZE_MS; i ++){
        for(int b = 0; b < SIZE_MS; b++){
            printf("%d ", ms[i][b]);
        }
        printf("\n");
    }

    _getch();
}


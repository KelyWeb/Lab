#include<stdio.h>
#include<locale.h>
#include<stdlib.h>
#define kl 4

void main(void){
    setlocale(LC_ALL, "Russian");
    int ms[kl][kl];

    //Наполнение матрицы элементами.
    for (int i = 0; i < kl; i++){
        for (int b = 0; b < kl; b++){
            int append; 
            scanf("%d", &append);
            ms[i][b] = append;
        }
    }

    int max = ms[0][0];
    int ravn_max_position_str = -1;
    int ravn_max_position_stolb = -1;
    //Перебор элементов диагонали для нахождения максимального элемента.
    for (int i = 0; i < kl; i++){
        if(max < ms[i][i]){
            max = ms[i][i];
        }
    } 

    //Перебор элементов матрицы ниже диагонали для нахождения числа = max.
    for (int b = 0; b < kl; b++){
        for (int d = b - 1; d >= 0; d--){
            if(ms[b][d] == max){
                ravn_max_position_str = b;
                ravn_max_position_stolb = d;
            }
        }
    }

    //Вывод информации.
    system("clear");
    for (int x = 0; x < kl; x++){
        for (int y = 0; y < kl; y++){
            printf("[%d] ", ms[x][y]);
        }
        printf("\n");
    }
    printf("\nМаксимальный элемент главной диагонали: %d\n", max);


    if (ravn_max_position_stolb == -1 && ravn_max_position_str == -1){
        printf("Ниже главной диагонали нет числа, равного максимальному на глайной диагонали.");
    }
    else{
        printf("Ниже главной диагонали есть элемент равный максимальному элементу главной диагонали.\n");
        printf("Схожий элемент: Строка: %d Столбец: %d \n", ravn_max_position_str, ravn_max_position_stolb);
    }
}

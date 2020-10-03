#include<stdio.h>
#include<locale.h>
#define a 3
#define d 3

int main(){
    setlocale(LC_ALL, "Russian");
    int ms[a][d];
    int VALUES, SCHETCHIK = 0;

    printf("Введите элементы в массив(всего %d): ", a*d);
    for (int i = 0; i < a; i++){
        for (int b = 0; b < d; b++){
            int append;
            scanf("%d", &append);
            ms[i][b] = append;
        }
    }//Окончание наполнения массива. 
    printf("Введите число на подсчет: ");
    scanf("%d", &VALUES);

    printf("Получилась матрица: \n");
    for (int i = 0; i < a; i++){
        for (int b = 0; b < d; b++){
            printf("%d ", ms[i][b]);
        }
        printf("\n");
    }//Вывод введенного массива-матрицы.

    for (int i = 0; i < a; i++){
        for (int b = 0; b < d; b ++){
            if (ms[i][b] == VALUES){
                SCHETCHIK++;
            } 
            else{
                continue;
            }
        }
    }
    printf("Количество числа %d в матрице - %d\n", VALUES, SCHETCHIK);
}

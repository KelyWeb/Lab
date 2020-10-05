#include<stdio.h>
#include<locale.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 20

int main(){
    int ms[SIZE];
    char enterOption[1];
    char more[1] = ">";
    char notmore[1] = "<";
    setlocale(LC_ALL, "Russian");

    //Наполнение массива рандомными значениями.
    for (int i = 0; i < SIZE; i++){
        int APPEND = rand() % 100;
        ms[i] = APPEND;
    }

    //Вывод неотсортированного массива.
    for (int i = 0; i < SIZE; i++){
        printf("[%d] ", ms[i]);
    }
    printf("\n");

start:
    //Запрос на тип сортировки(по возростанию или убыванию).
    printf("Введите тип сортировки(< or >): ");
    scanf("%[^\n]", enterOption);
    if(strcmp(enterOption, ">") == 0){
        int a = SIZE;
        for (int i = 0; i < SIZE; i++){
            for(int b = 0; b < a ; b++){
                if(ms[b] < ms[b+1]){
                    int EXTRACT = ms[b];
                    ms[b] = ms[b + 1];
                    ms[b + 1] = EXTRACT;
                }
                else{
                    continue;
                }
            }
        }
    }
    else if(strcmp(enterOption, "<") == 0){
        int a = SIZE;
        for (int i = 0; i < SIZE; i++){
            for(int b = 0; b < a ; b++ ){
                if(ms[b] > ms[b+1]){
                    int EXTRACT = ms[b];
                    ms[b] = ms[b + 1];
                    ms[b + 1] = EXTRACT;
                }
                else{
                    continue;
                }
            }
        }
    }

    else{
        printf("Введен неправельный параметр!\n");
        system("clear");
        strcpy(enterOption, "");
        goto start;
    }
    
    //Вывод отсортированного массива.
    for (int i = 0; i < SIZE; i++){
        printf("[%d] ", ms[i]);
    }
    printf("\n");

}

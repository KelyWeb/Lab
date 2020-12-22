#include<stdlib.h>
#include<stdio.h>
#include<locale.h>
#include<stdbool.h>
#define kolvo_strok 5
#define razmer_stroki 100

int wordSize(char * word);
void cpw(char * word1, char * word2);

int main(){
    setlocale(LC_ALL, "Russian");


    char ** strMs = NULL;//Память под строки и количесвто символов строке
    strMs = (char **)malloc(sizeof(char *) * kolvo_strok);   
    for(int i = 0; i < kolvo_strok; i++){
        strMs[i] = malloc(sizeof(char) * razmer_stroki);
    }
    
    //Ввод строк.
    printf("Введите %d строк каждая по %d символов: \n", kolvo_strok, razmer_stroki);
    for(int i = 0; i < kolvo_strok; i++){
        printf("[%d] ", i);
        fgets(strMs[i], razmer_stroki, stdin);
        printf("\n");
    }
    system("clear");

    //Массив под хранение слов.
    char ** words = NULL;
    words = malloc((sizeof(char *)) * 100);
    for(int i = 0; i < 100; i++){
        words[i] = malloc(20 * sizeof(char));
    }
    
    int zae = 0;
    int index = 0;
    for(int i = 0; i < kolvo_strok; i++){ //Перебираем каждую строку.
        int b = 0; //Индекс символа в строке перебираемой строки
        int t = 0; //Индекс перехода к сохранению слова 
        while(strMs[i][b] != '\0'){
            if((strMs[i][b] > 64 && strMs[i][b] < 91) || (strMs[i][b] > 96) && (strMs[i][b] < 123)){
                words[index][t] = strMs[i][b];
                t++;
                b++;
            }
            else{
                zae++;
                b++;
                index++;
                t = 0;
            }
        }
    }

    //Неотсортированный порядок слов
    for(int i = 0; i < 100; i++){
        if(words[i][0] != '\0'){
            printf("%s ", words[i]);
        }
    }
    printf("\n");

    int a = zae;
    for(int i = 0; i < zae; i++){
        for(int b = 1; b < a; b++){
            if(wordSize(words[b]) > wordSize(words[b - 1])){
                char * replace = words[b];
                words[b] = words[b - 1];
                words[b - 1] = replace;
            }
        }
    }

    //отсортированный порядок слов
    for(int i = 0; i < 100; i++){
        if(words[i][0] != '\0'){
            printf("%s ", words[i]);
        }
    }
    printf("\n");
    

    for(int i = 0; i < 100; i++){
        free(words[i]);
    }
    free(words);

    for(int b = 0; b < kolvo_strok; b++){
        free(strMs[b]);
    }
    free(strMs);
}

int wordSize(char * word){
    int i = 0; 
    while(word[i] != '\0'){
        i++;
    }
    return i;
}


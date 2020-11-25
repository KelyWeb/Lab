#include<stdio.h>
#include<locale.h>
#include<stdlib.h>
#include<stdbool.h>
#define SIZE 1000

int indexN(const char * text, const char  * word);
bool checkOnEntry(const char * text, const char  * word);
int size_word(const char * text);


int main(void){
    setlocale(LC_ALL, "Russian");
    char word[SIZE], f_word[SIZE], s_word[SIZE];
P:
    fputs("Введите текст: \n", stdout);
    fgets(word, SIZE, stdin);
    system("clear");
    printf("Введенный текст :\n%s", word);



    printf("\nВведите слово, которое хотите заменить: \n");
    fgets(f_word, SIZE, stdin);
    if(!(checkOnEntry(word, f_word))){
        system("clear");
        printf("Данного слова нет в тексте!\n");
        goto P;
    } //Проверка на наличие заменяемого слова.
    

    printf("Введите слово, на которое хотите заменить: \n");
    fgets(s_word, SIZE, stdin);
    //system("clear");

    //printf("%d", indexN(word, f_word));

    int firts_num_index = indexN(word, f_word) - size_word(f_word);
    int second_num_index = firts_num_index + size_word(f_word) + 1;
    printf("%d", firts_num_index);
    printf("%d", second_num_index);
    printf("%d", second_num_index + 1);
    char text[SIZE]; int b = 0;
    for(int i = 0; i < SIZE; i++, b++){
        if(i == firts_num_index){
            int fr = i;
            for(int b = fr; b < i + size_word(s_word); b++){
                text[b] = s_word[b - fr];
            }
            i = fr + size_word(s_word) - 1;
            b = b + size_word(f_word) - 1;
        }
        else{
            text[i] = word[b];
        }
    }



    //system("clear");
    printf("\nИзмененный текст: \n%s", text);
}


bool checkOnEntry(const char * text, const char * word){
    int b = 0;
    int size = 0;
    int word_size = size_word(text);
    for(int i = 0; i < word_size + 1; i++){
        if(text[i] == word[b]){
            if((size_word(word)) == size){
                return true;
            }
            size++;
            b++;
        }
        else{
            if(size_word(word) == size){
                return true;
            }
            else{
                b = 0;
                size = 0;
            }
        }
    }
    return false;
}


int size_word(const char * text){
    for(int i = 0; ; i++){
        if(text[i] != '\n'){
            continue;
        }
        else{
            return i;
        }
    }
}


int indexN(const char * text, const char  * word){
    int b = 0;
    int size = 0;
    int word_size = size_word(text);
    for(int i = 0; i < word_size + 1; i++){
        if(text[i] == word[b]){
            if((size_word(word)) == size){
                return i;
            }
            size++;
            b++;
        }
        else{
            if(size_word(word) == size){
                return i;
            }
            else{
                b = 0;
                size = 0;
            }
        }
    }
    return false;
}

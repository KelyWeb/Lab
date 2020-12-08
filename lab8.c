#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<stdbool.h>


int len_word(const char * word);
int wordEntryValue(const char * text, const char * word);
int kolvo_slov(const char * text);
bool sravnenie(const char * word1, const char * word2);
int max(const int * ms, const int size);


int main(void){
    setlocale(LC_ALL, "Russian");
    const int M = 20;
    char * text = NULL;
    text = (char *)malloc(1000);
    printf("Введите текст: \n");
    fgets(text, 1000, stdin);
    system("clear");
    printf("Введенный текст: \n");
    fputs(text, stdout);

    //Выделение памяти под слова.
    char ** word = NULL;
    word = (char **)calloc(kolvo_slov(text), sizeof(int *));
    for(int i = 0; i < kolvo_slov(text); i++){
        word[i] = (char *)calloc(M, sizeof(char));
    }


    int t = 0; int g = 0; int i = 0;
    do{
        if((text[t] >= 'A' && text[t] <= 'Z') || (text[t] >= 'a' && text[t] <= 'z')){
            word[i][g] = text[t];
            g++;
            t++;
        }
        else{
            i++;
            g = 0;
            t++;
        }
    }while(text[t] != '\0');
    
    
    int n;
    printf("Введите количество слов у которых больше всего повторений: \n");
    scanf("%d", &n);

    //Нахождение повторений слов.
    int * position = NULL;
    position = (int *)calloc(100, sizeof(int));
    int pos = 0;
    for(int i = 0; i < kolvo_slov(text); i++){
        for(int b = 0; b < i; b++){
            if(sravnenie(word[i], word[b])){
                *(position + i) = -1;
            }
        }
        if(*(position + i) == -1){
            pos++;

        }
        else{
            *(position + i) = wordEntryValue(text, word[i]);
            pos++;
        }
    }

    for(int i = 0; i < n; i++){
        printf("Слово %s повторяется %d раз!\n", word[max(position, 100)], position[max(position, 100)]);
        position[max(position, 100)] = -1;
    }

}


int len_word(const char * word){
    int i = 0; 
    while(word[i] != '\0'){
        i++;
    }
    return i;
}

int wordEntryValue(const char * text, const char * word){ // Функция подсчета слова.
    int i = 0;
    int b = 0;
    int schetchik = 0;
    while(text[i] != '\0'){
        if(word[b] == text[i]){
            i++;
            b++;
            if((len_word(word) - 1) == b){
                schetchik++;
            }
        }
        else{
            b = 0;
            i++;
        }
    }
    return schetchik;
}

int kolvo_slov(const char * text){
    int i = 0;
    int schetchik = 0;
    while(text[i] != '\0'){
        if(text[i] == '.' || text[i] == ',' || text[i] == ' '){
            schetchik++;
        }
        i++;
    }
    return schetchik;
}

bool sravnenie(const char * word1, const char * word2){
    if(len_word(word1) != len_word(word2)){
        return false;
    }
    else{
        for(int i = 0; i < len_word(word1) - 1; i++){
            if(word1[i] == word2[i]){
                continue;
            }
            else{
                return false;
            }
        }
        return true;
    }
}

int max(const int * ms, const int size){
    int p = 0;
    for(int i = 0; i < size; i++){
        if(ms[i] > ms[p]){
            p = i;
        }
    }
    return p;
}

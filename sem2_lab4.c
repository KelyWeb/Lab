#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<locale.h>

#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_RESET    "\x1b[0m"



int main(void){
    FILE * ffile = NULL;
    if((ffile = fopen("text1.txt", "w+")) == NULL) exit(EXIT_FAILURE);
    char text[1000];

    printf("Введите текст в файл: \n");
    fgets(text, 1000, stdin);
    fputs(text, ffile);


    char ** words = malloc(sizeof(char *) * 100);
    for(int i = 0; i < 100; i++){
        *(words + i) = malloc(sizeof(char) * 100);
    }


    rewind(ffile);
    int position = 0; 
    int count = 0; 
    int ch = 0;
    
    while(1){
        ch = getc(ffile);
        if(ch == EOF) break;
        if(ch == ' '){
            count += 1;
            position = 0;
        }
        if(ch != ' '){
            words[count][position] = (char)ch;
            position++;
        }
    }
    fclose(ffile);


    for(int i = count; i < 100; i++){
        free(*(words + i));
    }
    words = realloc(words, sizeof(char *) * count);


    //Сортировка слов............
    for(int i = 0; i < count; i++){
        for(int b = 1; b < count; b++){
            if(words[b - 1][0] > words[b][0]){
                char * temp = *(words + b);
                *(words + b) = *(words + b - 1);
                *(words + b - 1) = temp;
            }
        }
    }
    //................

    //Запись в файл упорядоченного текста...
    ffile = fopen("text1.txt", "w+");
    for(int i = 0; i < count; i++){
        fprintf(ffile, "%s ", *(words + i));
    }
    fclose(ffile);
    //.............


    //Вывод упорядоченного файла....
    printf("Файл упорядоченный лексикографически: \n");
    ffile = fopen("text1.txt", "r");
    rewind(stdin);
    int chk = 0;
    while((chk = getc(ffile)) != EOF){
        putchar(chk);
    }
    putchar('\n');
    fclose(ffile);
    //............
}

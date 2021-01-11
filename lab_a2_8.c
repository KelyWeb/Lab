#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<locale.h>
#define size_str 1000



int main(void){
    int ascii_symbols[] = {65, 69, 73, 79, 85, 89,
                           97, 101, 105, 111, 117, 121}; 
    char * text = (char *)malloc(size_str * sizeof(char));
    fgets(text, size_str, stdin);

    int index = 0;
    while(1){
        while((text[index] < 65 && text[index] > 90) || (text[index] < 97 && text[index] > 122)){
            index++;
        } //Доход до индекса перой буквы
        int position = index; //Запоминание индекса первой буквы
        while((text[index] > 64 && text[index] < 91) || (text[index] > 96 && text[index] < 123)){
            for(int i = 0; i < sizeof(ascii_symbols) / sizeof(int); i++){
                if((int)text[index] == ascii_symbols[i]){
                    for(int b = 0; b < sizeof(ascii_symbols) / sizeof(int); b++){
                        if(text[index + 1] == ascii_symbols[b]){
                            while(1){
                                if((text[position] > 64 && text[position] < 91) || (text[position] > 96 && text[position] < 123)){
                                    text[position] = (int)text[position] - 32;
                                    position++;
                                }
                                else{
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            if(text[index] == '\0') break;
            else index++;
        }
        if(text[index] == '\0') break;
        else index++;
        
    }
    fputs(text, stdout);
}

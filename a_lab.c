#include<stdio.h>
#include<stdlib.h>
#define SIZE 500

int main(void){
    char * text = NULL;
    text = malloc(sizeof(char) * SIZE);
    fgets(text, SIZE, stdin);

    int b = 0; int max_in_Num; int min_in_Num; int max = 0; int min = 10;
    int t = 0;
    while(text[b] != '\0'){
        if((text[b] > 64 && text[b] < 70) || (text[b] > 96 && text[b] < 123)){
            b++;
            t++;
        }
        else{
            if(t > max){
                max = t;
                max_in_Num = b - t;
            }
            if(min > t){
                min = t;
                min_in_Num = b - t;
            }
            t = 0;
            b++;
        }
    }

    char * newText = NULL;
    newText = malloc(sizeof(char) * 500);
    int y = 0; int p = 0;
    while(text[y] != '\0'){
        if(y == max_in_Num){
            for(int i = 0; i < min; i++){
                newText[p] = text[min_in_Num + i];
                y++;
                p++;
            }
            y += max - min;
        }
        else if(y == min_in_Num){
            for(int i = 0; i < max; i++){
                newText[p] = text[max_in_Num + i];
                y++;
                p++;
            }
            y -= max - min;
        }
        else{
            newText[p] = text[y];
            y++;
            p++;
        }
    }
    fputs(newText, stdout);
}

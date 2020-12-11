#include<stdio.h>
#include<stdlib.h>
#include<locale.h>


int main(){
    char * text = NULL; 
    text = (char *)calloc(1000, sizeof(char));
    fgets(text, 1000, stdin);
    fputs(text, stdout);

    //Поиск минимального слова.
    int j = 0; int vl = 0; int vl1 = 0;
    while(text[j] != '\0'){
        while((text[j] < 'A' || (text[j] > 'Z' && text[j] < 'a') || text[j] > 'z')){
            j++;
        }
        if(vl == 0){
            while((text[j] >= 'A' && text[j] <= 'Z') || (text[j] >= 'a' && text[j] <= 'z')){
                vl++;
                j++;
            }
            if(vl >= vl1){
                vl1 = 0;
            }
            else{
                vl = 0;
            }
        }
        else{
            while((text[j] >= 'A' && text[j] <= 'Z') || (text[j] >= 'a' && text[j] <= 'z')){
                vl1++;
                j++;
            }
            if(vl1 >= vl){
                vl = 0;
            }
            else{
                vl1 = 0;
            }
        }    
    }
    printf("%d\n%d\n", vl, vl1);
    return 0;
}


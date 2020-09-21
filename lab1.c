#include<stdio.h>
#include<locale.h>
#include<string.h>

int main(){
    setlocale(LC_ALL, "Russian");
    char word[60];
    printf("Введите строку: ");
    scanf("%[^\n]", word);
    
    for(int i = 0; i < strlen(word); i++){ //Перебор строки для взятия символа на подсчет.
        int schetchik = 0;
        for(int b = 0; b < strlen(word); b++){ //Перебор строки для подсчета взятого символа.
            if(word[b] == word[i]){
                schetchik++;
            }
        }
    printf("Количество буквы %c = %d\n", word[i], schetchik);
    }
}

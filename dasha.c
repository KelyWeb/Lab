#include<stdio.h>
#include<stdlib.h>

int func(int * ms, int size);



int main(void){
    int * ms = (int *)malloc(sizeof(int) * 10);
    for(int i = 0; i < 10; i++){
        scanf("%d", &ms[i]);
    }

    for(int i = 0; i < 10; i++){
        printf("[%d] ", *(ms + i));
    }
    printf("\n");
    int new_size = func(ms, 10);

    for(int i = 0; i < new_size; i++){
        printf("[%d] ", *(ms + i));
    }
    printf("\n");
}


int func(int * ms, int size){
    int k = 0;
    for(int i = 0; i < size - 1; i++){
        if(ms[i] == ms[i + 1]){
            ms[i] = 0;
            k++;
        }
    }
    for(int i = 0; i < size; i++){
        for(int b = 0; b < size - 1; b++){
            if(ms[b] == 0){
                int tmp = ms[b];
                ms[b] = ms[b + 1];
                ms[b + 1] = tmp;
            }
        }
    }
    ms = (int *)realloc(ms, sizeof(int) * (size - k));
    return size - k;
}

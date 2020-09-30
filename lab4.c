#include<stdio.h>
#include<locale.h>


int main(){
    int ms[3][3];
    for (int i = 0; i < 3; i++){
        for (int b = 0; b < 3; b++){
            int append;
            scanf("%d", &append);
            ms[i][b] = append;

        }
    }
    int proizved = 1;
    for(int i = 0; i < 3; i++ ){
        proizved *= ms[1][i];
    }

    printf("Произведение матрицы = %d", proizved);

}

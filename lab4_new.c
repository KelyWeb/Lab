#include<stdio.h>
#include<locale.h>
#include<stdlib.h>
#define kl 10

int main() {
	setlocale(LC_ALL, "Russian");
	int ms[kl];
	//Наполнение массива.
	for (int i = 0; i < kl; i++) {
		int append;
		scanf("%d", &append);
		ms[i] = append;
	}

	int pass = 0;
	int schetchik = 0;
	for (int b = 1; b < kl; b++) {
		if (ms[b] > ms[b-1]){
            continue;
        }
        else{
            schetchik++;
            b++;
        }
	}

	//Вывод массива.
	system("cls");
	for (int x = 0; x < kl; x++) {
		printf("[%d] ", ms[x]);
	}
	printf("\n");
	printf("Количество найденных последовательных элементов: %d", schetchik);

}

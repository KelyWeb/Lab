#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <iostream>
using namespace std;

void print(char* string);
int word_len(char* string);

int main(int argc, char* argv[]) {
	FILE* ffile = NULL; 
	ffile = fopen("file.txt", "w + b");
	
	cout << "Введите строки для записи в файл, для окончания введите 'q'" << endl;
	while (true) {
		char string_for_file[1000];
		fgets(string_for_file, 1000, stdin);
		if(string_for_file[0] == 'q') break;
		else {
			fputs(string_for_file, ffile);
		}
	}
	rewind(ffile);
	const int array2[] = { 100000, 10000, 1000, 100, 10, 1 };
	char string_for_digit[100][100]; int word = 0; int symb = 0;
	char symbol = 0;
	while (true) {
		symbol = getc(ffile);
		if ((symbol != EOF) && ((symbol > 47) && (symbol < 58))) {
			string_for_digit[word][symb] = symbol;
			symb++;
		}
		else {
			if (symbol == EOF) break;
			else {
				if (symb != 0) {
					word++;
					symb = 0;
				}
			}
		}
		
	}
	
	int array[100];
	int count = 0;
	for (int i = 0; i < word; i++) {
		int result = 0;
		int k = word_len(string_for_digit[i]);
		for (int j = 0; j < k; j++) {
			result += ((int)string_for_digit[i][j] - 48) * array2[6 - k + j];
		}
		array[count] = result;
		count++;
	}
	for (int i = 0; i < count; i++) {
		printf("%d ", array[i]);
	}

}

int word_len(char* string) {
	int k = 0;
	while (string[k] != '\0') {
		k++;
	}
	return k;
}


void print(char* string) {
	int i = 0;
	while (string[i] != 0) {
		putchar(string[i]);
		i++;
	}
}


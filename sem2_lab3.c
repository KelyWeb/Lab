#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<locale.h>

#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_RESET    "\x1b[0m"

typedef struct izdanie {
	char  izd_name[100];
	int   count;
	float price;
} def;


void add_to_File  (FILE* in_which_add);
void check_File   (FILE * in_which_check);
void delete_tabl  (char * str);
void check_min    (FILE * in_which_search);
void check_max    (FILE * in_which_search);
void check_min_ekz(FILE * in_which_search);


int main(void) {
	setlocale(LC_ALL, "Russian");
	FILE * ffile = NULL;

	//Обнуление существуеющего файла и проверка на возможность открытия..
	if ((ffile = fopen("file.txt", "w+b")) == NULL) exit(EXIT_FAILURE);
	fclose(ffile);
	//.....

	while (true) {
		printf(ANSI_COLOR_GREEN "Просмотр информации всех изданий: 1\n");
		printf("Добавление издания в список: 2\n");
		printf("Просмотр издания с максимальной ценой за журнал: 3\n");
		printf("Просмотр издания с минимальной ценой за журнал: 4\n");
		printf("Просмотр издания с максимальным количеством экземпляров в год: 5\n");
		printf("Выход: 6\n" ANSI_COLOR_RESET);

		//Проверка на ввод....
		int choice = 0;
		int check_on_choice = scanf("%d", &choice);
		while (check_on_choice != 1) {
			printf("Введен неверный параметр, повторите ввод.\n");
			rewind(stdin);
			int check_on_choice = scanf("%d", &choice);
		}
		//.......

		if (choice == 1) check_File   (ffile);
		if (choice == 2) add_to_File  (ffile);
		if (choice == 3) check_max    (ffile);
		if (choice == 4) check_min    (ffile);
		if (choice == 5) check_min_ekz(ffile);
		if (choice == 6) break;
	}
}

void check_min_ekz(FILE * in_which_search){
	system("clear");
	in_which_search = fopen("file.txt", "rb");
	struct izdanie for_check1;
	struct izdanie for_check2;
	for_check2.count = -1000;

	rewind(in_which_search);
	while(fread(&for_check1, sizeof(struct izdanie), 1, in_which_search) == 1){
		if(for_check1.count > for_check2.count){
			strcpy(for_check2.izd_name, for_check1.izd_name);
			for_check2.price = for_check1.price;
			for_check2.count = for_check1.count;
		}
	}
	delete_tabl(for_check2.izd_name);
	printf(ANSI_COLOR_BLUE "Максимальную колество экземпляров в год имеет издание: \n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_BLUE "Название издания:\t\tКоличество экземепляров:\t\tСтоимость за 1 экземпляр\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_RED "%-31s %-39d %-20.2f\n" ANSI_COLOR_RESET, for_check2.izd_name, for_check2.count, for_check2.price);
	fclose(in_which_search);
}

void add_to_File(FILE * in_which_add) {
	in_which_add = fopen("file.txt", "a+b");
	struct izdanie for_add;
	printf("Введите название газеты/журнала:\n");
	getchar();
	fgets(for_add.izd_name, 100, stdin);
	printf("Введите стоимость за один экземляр:\n");
	while (true) {
		int choice_check = scanf("%f", &(for_add.price));
		if (for_add.price > 0 && choice_check == 1) break;
		else {
			printf("Введен неверный параметр. Повторите ввод.\n");
			getchar();
			choice_check = scanf("%f", &(for_add.price));
		}
	}
	printf("Введите количество экземпляров в год:\n");
	while (true) {
		int choice_check = scanf("%d", &(for_add.count));
		if (for_add.count > 0 && choice_check == 1) break;
		else {
			printf("Введен неверный параметр. Повторите ввод.\n");
			getchar();
			choice_check = scanf("%d", &(for_add.count));
		}
	}
	fwrite(&for_add, sizeof(struct izdanie), 1, in_which_add);
	fclose(in_which_add);
}

void check_max(FILE * in_which_search){
	system("clear");
	in_which_search = fopen("file.txt", "rb");
	struct izdanie for_check1;
	struct izdanie for_check2;
	for_check2.price = -1000;

	rewind(in_which_search);
	printf(ANSI_COLOR_BLUE "Максимальную стоимость имеет издание: \n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_BLUE "Название издания:\t\tКоличество экземепляров:\t\tСтоимость за 1 экземпляр\n" ANSI_COLOR_RESET);
	while(fread(&for_check1, sizeof(struct izdanie), 1, in_which_search) == 1){
		if(for_check1.price > for_check2.price){
			strcpy(for_check2.izd_name, for_check1.izd_name);
			for_check2.price = for_check1.price;
			for_check2.count = for_check1.count;
		}
	}
	delete_tabl(for_check2.izd_name);
	printf(ANSI_COLOR_RED "%-31s %-39d %-20.2f\n" ANSI_COLOR_RESET, for_check2.izd_name, for_check2.count, for_check2.price);
	fclose(in_which_search);

}

void check_min(FILE * in_which_search){
	system("clear");
	in_which_search = fopen("file.txt", "rb");
	struct izdanie for_check1;
	struct izdanie for_check2;
	for_check2.price = 1000;

	rewind(in_which_search);
	printf(ANSI_COLOR_BLUE "Минимальная стоимость имеет издание: \n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_BLUE "Название издания:\t\tКоличество экземепляров:\t\tСтоимость за 1 экземпляр\n" ANSI_COLOR_RESET);
	while(fread(&for_check1, sizeof(struct izdanie), 1, in_which_search) == 1){
		if(for_check1.price < for_check2.price){
			strcpy(for_check2.izd_name, for_check1.izd_name);
			for_check2.price = for_check1.price;
			for_check2.count = for_check1.count;
		}
	}
	delete_tabl(for_check2.izd_name);
	printf(ANSI_COLOR_RED "%-31s %-39d %-20.2f\n" ANSI_COLOR_RESET, for_check2.izd_name, for_check2.count, for_check2.price);
	fclose(in_which_search);
}

void check_File(FILE * in_which_check){
	system("clear");
	in_which_check = fopen("file.txt", "rb");
	struct izdanie for_check;
	rewind(in_which_check);
	printf(ANSI_COLOR_RED "Название издания:\t\tКоличество экземепляров:\t\tСтоимость за 1 экземпляр\n" ANSI_COLOR_RESET);
	while(fread(&for_check, sizeof(struct izdanie), 1, in_which_check) == 1){
		delete_tabl(for_check.izd_name);
		printf("%-31s %-39d %-20.2f\n", for_check.izd_name, for_check.count, for_check.price);
	}
	fclose(in_which_check);
}

void delete_tabl(char * str){
	int i = 0; 
	while(str[i] != '\n'){
		i++;
	}
	str[i] = '\0';
}

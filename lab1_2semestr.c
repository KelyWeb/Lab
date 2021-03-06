#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<locale.h>


#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"


struct date{
    int day;
    int month;
    int year;
};

struct reader{
    char name_surname[100];;
    char book_name[100];
    int reader_ticket;
    struct date borrow_date;
} r_default;


int msReverse(int * ms, int size);
void show_readers(struct reader * tt, int size);
void readers_sort(struct reader * tt, int size);
void edit_parametrs(struct reader * tt);
void print(char * text);
int amount_of_digits(int number);
void put_space(int amount);
int text_size(char * text);
void delete_struct(struct reader * tt, int * size, int delete_arg);
struct reader * search_reader(struct reader * tt, int size);
struct reader * search_reader2(struct reader * tt, int size);
bool chastichnoe_sr_chisel(int num1, int num2);
bool chastichnoe_sr_strok(char * str1, char * str2);


int main(int argc, char *argv[]){
    setlocale(LC_ALL, "Russian");
    int r_size = 0; //Переменная начального количества читателей
    struct reader * readers = malloc(sizeof(r_default) * r_size);
    if(readers == NULL){
        printf("Недостаточно памяти!\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < r_size; i++){ //Ввод стартовых читателей. 
        printf("Ввод данных для %d читателя: \n", i + 1);
        printf("Имя Фамилия: \n");
        fgets((readers + i) -> name_surname, 100, stdin);
        printf("Название книги: \n");
        fgets((readers + i) -> book_name, 100, stdin);
        printf("Номер читательского билета: \n");
        scanf("%d", &((readers + i) -> reader_ticket));
        printf("Дата возврата: ДЕНЬ МЕСЯЦ ГОД\n");
        scanf("%d%d%d", &((readers + i) -> borrow_date.day), 
                        &((readers + i) -> borrow_date.month), &((readers + i) -> borrow_date.year));
        getchar();
        system("clear");
    }


    while(1){
        printf(ANSI_COLOR_GREEN "Выберите операцию над списком:\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_GREEN "Просмотр списка читателей: 1\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_GREEN "Редактирование параметров читателя: 2\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_GREEN "Добвление читателя в список: 3\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_GREEN "Удаление читателя из списка: 4\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_GREEN "Поиск читателя по заданному параметру: 5\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_GREEN "Сортировка по заданному параметру: 6\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_GREEN "Поиск по частичному совпадению: 7\n" ANSI_COLOR_RESET);
        
        
        int choice = 0;
        int check_on = scanf("%d", &choice);
        while(check_on != 1){
            printf(ANSI_COLOR_RED "Введен неверный параметр, повторите попытку.\n" ANSI_COLOR_RESET);
            getchar();
            check_on = scanf("%d", &choice);
        }
        
        if(choice == 1) show_readers(readers, r_size);
        if(choice == 2){
            printf(ANSI_COLOR_BLUE "Номер какого читателя вы хотите редактировать: \n" ANSI_COLOR_RESET);
            int choice2; 
            scanf("%d", &choice2);
            int tmp = choice2 - 1;
            edit_parametrs(readers + tmp);
        }
        if(choice == 3){
            system("clear");
            r_size += 1;
            readers = realloc(readers, sizeof(r_default) * r_size);
            getchar();
            printf(ANSI_COLOR_GREEN "Имя Фамилия: \n" ANSI_COLOR_RESET);
            fgets((readers + r_size - 1) -> name_surname, 100, stdin);
            printf(ANSI_COLOR_GREEN "Название книги: \n" ANSI_COLOR_RESET);
            fgets((readers + r_size - 1) -> book_name, 100, stdin);
            printf(ANSI_COLOR_GREEN "Номер читательского билета: \n" ANSI_COLOR_RESET);
            scanf("%d", &((readers + r_size - 1) -> reader_ticket));
            printf(ANSI_COLOR_GREEN "Дата возврата: ДЕНЬ.МЕСЯЦ.ГОД\n" ANSI_COLOR_RESET);
            scanf("%d%d%d", &((readers + r_size - 1) -> borrow_date.day), 
                        &((readers + r_size - 1) -> borrow_date.month), &((readers + r_size - 1) -> borrow_date.year));
            while((readers + r_size - 1) -> borrow_date.day > 31 || (readers + r_size - 1) -> borrow_date.day < 1 || 
                (readers + r_size - 1) -> borrow_date.month > 12 || (readers + r_size - 1) -> borrow_date.month < 1 ||
                (readers + r_size - 1) -> borrow_date.year < 2000 || (readers + r_size - 1) -> borrow_date.year > 2030){
                    printf(ANSI_COLOR_RED "Дата введена неверно! Повторите попытку!\n" ANSI_COLOR_RESET);
                    getchar();
                    scanf("%d%d%d", &((readers + r_size - 1) -> borrow_date.day), 
                        &((readers + r_size - 1) -> borrow_date.month), &((readers + r_size - 1) -> borrow_date.year));
                }
            getchar();
            system("clear");
        }
        if(choice == 4){
            system("clear");
            printf(ANSI_COLOR_BLUE "Номер какого читателя вы хотите удалить:\n" ANSI_COLOR_RESET);
            int choice4 = 0;
            scanf("%d", &choice4);
            
            delete_struct(readers, &r_size, choice4 - 1);
        }
        if(choice == 5) search_reader(readers, r_size);
        if(choice == 6) readers_sort(readers, r_size);
        if(choice == 7)  search_reader2(readers, r_size);
    }
}


void readers_sort(struct reader * tt, int size){
    printf(ANSI_COLOR_BLUE "По какому параметру нужно выполнить сортировку? \n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE "по дате - 1, имя_фамилия - 2, номер билета  - 3, названию книги - 4\n" ANSI_COLOR_RESET);
    int choice = 0; 
    int check = scanf("%d", &choice);
    if(check == 0 || choice > 4 || choice < 0){
        printf(ANSI_COLOR_RED "Введен неверный аргумент!\n" ANSI_COLOR_RESET);
        return;
    }

    if(choice == 1){
        struct reader * for_sort = malloc(sizeof(r_default));
        for(int i = 0; i < size; i++){
            for(int b = 0; b < size - 1; b++){
                if((tt + b) -> borrow_date.year > (tt + b + 1) -> borrow_date.year){
                    (for_sort) -> reader_ticket = (tt + b) -> reader_ticket;
                    (for_sort) -> borrow_date.day = (tt + b) -> borrow_date.day;
                    (for_sort) -> borrow_date.month = (tt + b) -> borrow_date.month;
                    (for_sort) -> borrow_date.year = (tt + b) -> borrow_date.year;
                    strcpy((for_sort) -> book_name, (tt + b) -> book_name);
                    strcpy((for_sort) -> name_surname, (tt + b) -> name_surname);
                    (tt + b) -> reader_ticket = (tt + b + 1) -> reader_ticket;
                    (tt + b) -> borrow_date.day = (tt + b + 1) -> borrow_date.day;
                    (tt + b) -> borrow_date.month = (tt + b + 1) -> borrow_date.month;
                    (tt + b) -> borrow_date.year = (tt + b + 1) -> borrow_date.year;
                    strcpy((tt + b) -> book_name, (tt + b + 1) -> book_name);
                    strcpy((tt + b) -> name_surname, (tt + b + 1) -> name_surname);
                    (tt + b + 1) -> reader_ticket = (for_sort) -> reader_ticket;
                    (tt + b + 1) -> borrow_date.day = (for_sort) -> borrow_date.day;
                    (tt + b + 1) -> borrow_date.month = (for_sort) -> borrow_date.month;
                    (tt + b + 1) -> borrow_date.year = (for_sort) -> borrow_date.year;
                    strcpy((tt + b + 1) -> book_name, (for_sort) ->  book_name);
                    strcpy((tt + b + 1) -> name_surname, (for_sort) -> name_surname);
                }
                else if((tt + b) -> borrow_date.year == (tt + b + 1) -> borrow_date.year){
                    if((tt + b) -> borrow_date.month > (tt + b + 1) -> borrow_date.month){
                        (for_sort) -> reader_ticket = (tt + b) -> reader_ticket;
                        (for_sort) -> borrow_date.day = (tt + b) -> borrow_date.day;
                        (for_sort) -> borrow_date.month = (tt + b) -> borrow_date.month;
                        (for_sort) -> borrow_date.year = (tt + b) -> borrow_date.year;
                        strcpy((for_sort) -> book_name, (tt + b) -> book_name);
                        strcpy((for_sort) -> name_surname, (tt + b) -> name_surname);
                        (tt + b) -> reader_ticket = (tt + b + 1) -> reader_ticket;
                        (tt + b) -> borrow_date.day = (tt + b + 1) -> borrow_date.day;
                        (tt + b) -> borrow_date.month = (tt + b + 1) -> borrow_date.month;
                        (tt + b) -> borrow_date.year = (tt + b + 1) -> borrow_date.year;
                        strcpy((tt + b) -> book_name, (tt + b + 1) -> book_name);
                        strcpy((tt + b) -> name_surname, (tt + b + 1) -> name_surname);
                        (tt + b + 1) -> reader_ticket = (for_sort) -> reader_ticket;
                        (tt + b + 1) -> borrow_date.day = (for_sort) -> borrow_date.day;
                        (tt + b + 1) -> borrow_date.month = (for_sort) -> borrow_date.month;
                        (tt + b + 1) -> borrow_date.year = (for_sort) -> borrow_date.year;
                        strcpy((tt + b + 1) -> book_name, (for_sort) ->  book_name);
                        strcpy((tt + b + 1) -> name_surname, (for_sort) -> name_surname);
                    }
                    else if((tt + b) -> borrow_date.month == (tt + b + 1) -> borrow_date.month){
                        if((tt + b) -> borrow_date.day > (tt + b + 1) -> borrow_date.day){
                            (for_sort) -> reader_ticket = (tt + b) -> reader_ticket;
                            (for_sort) -> borrow_date.day = (tt + b) -> borrow_date.day;
                            (for_sort) -> borrow_date.month = (tt + b) -> borrow_date.month;
                            (for_sort) -> borrow_date.year = (tt + b) -> borrow_date.year;
                            strcpy((for_sort) -> book_name, (tt + b) -> book_name);
                            strcpy((for_sort) -> name_surname, (tt + b) -> name_surname);
                            (tt + b) -> reader_ticket = (tt + b + 1) -> reader_ticket;
                            (tt + b) -> borrow_date.day = (tt + b + 1) -> borrow_date.day;
                            (tt + b) -> borrow_date.month = (tt + b + 1) -> borrow_date.month;
                            (tt + b) -> borrow_date.year = (tt + b + 1) -> borrow_date.year;
                            strcpy((tt + b) -> book_name, (tt + b + 1) -> book_name);
                            strcpy((tt + b) -> name_surname, (tt + b + 1) -> name_surname);
                            (tt + b + 1) -> reader_ticket = (for_sort) -> reader_ticket;
                            (tt + b + 1) -> borrow_date.day = (for_sort) -> borrow_date.day;
                            (tt + b + 1) -> borrow_date.month = (for_sort) -> borrow_date.month;
                            (tt + b + 1) -> borrow_date.year = (for_sort) -> borrow_date.year;
                            strcpy((tt + b + 1) -> book_name, (for_sort) ->  book_name);
                            strcpy((tt + b + 1) -> name_surname, (for_sort) -> name_surname);
                        }
                    }
                }
            }
        }
        free(for_sort);
    }
    if(choice == 2){
        struct reader * for_sort = malloc(sizeof(r_default));
        for(int i = 0; i < size; i++){
            for(int b = 0; b < size - 1; b++){
                if((tt + b) -> name_surname[0] > (tt + b + 1) -> name_surname[0]){
                    (for_sort) -> reader_ticket = (tt + b) -> reader_ticket;
                    (for_sort) -> borrow_date.day = (tt + b) -> borrow_date.day;
                    (for_sort) -> borrow_date.month = (tt + b) -> borrow_date.month;
                    (for_sort) -> borrow_date.year = (tt + b) -> borrow_date.year;
                    strcpy((for_sort) -> book_name, (tt + b) -> book_name);
                    strcpy((for_sort) -> name_surname, (tt + b) -> name_surname);
                    (tt + b) -> reader_ticket = (tt + b + 1) -> reader_ticket;
                    (tt + b) -> borrow_date.day = (tt + b + 1) -> borrow_date.day;
                    (tt + b) -> borrow_date.month = (tt + b + 1) -> borrow_date.month;
                    (tt + b) -> borrow_date.year = (tt + b + 1) -> borrow_date.year;
                    strcpy((tt + b) -> book_name, (tt + b + 1) -> book_name);
                    strcpy((tt + b) -> name_surname, (tt + b + 1) -> name_surname);
                    (tt + b + 1) -> reader_ticket = (for_sort) -> reader_ticket;
                    (tt + b + 1) -> borrow_date.day = (for_sort) -> borrow_date.day;
                    (tt + b + 1) -> borrow_date.month = (for_sort) -> borrow_date.month;
                    (tt + b + 1) -> borrow_date.year = (for_sort) -> borrow_date.year;
                    strcpy((tt + b + 1) -> book_name, (for_sort) ->  book_name);
                    strcpy((tt + b + 1) -> name_surname, (for_sort) -> name_surname);
                }
                else{
                    if((tt + b) -> name_surname[0] == (tt + b + 1) -> name_surname[0]){
                        if((tt + b) -> name_surname[1] > (tt + b + 1) -> name_surname[1]){
                            (for_sort) -> reader_ticket = (tt + b) -> reader_ticket;
                            (for_sort) -> borrow_date.day = (tt + b) -> borrow_date.day;
                            (for_sort) -> borrow_date.month = (tt + b) -> borrow_date.month;
                            (for_sort) -> borrow_date.year = (tt + b) -> borrow_date.year;
                            strcpy((for_sort) -> book_name, (tt + b) -> book_name);
                            strcpy((for_sort) -> name_surname, (tt + b) -> name_surname);
                            (tt + b) -> reader_ticket = (tt + b + 1) -> reader_ticket;
                            (tt + b) -> borrow_date.day = (tt + b + 1) -> borrow_date.day;
                            (tt + b) -> borrow_date.month = (tt + b + 1) -> borrow_date.month;
                            (tt + b) -> borrow_date.year = (tt + b + 1) -> borrow_date.year;
                            strcpy((tt + b) -> book_name, (tt + b + 1) -> book_name);
                            strcpy((tt + b) -> name_surname, (tt + b + 1) -> name_surname);
                            (tt + b + 1) -> reader_ticket = (for_sort) -> reader_ticket;
                            (tt + b + 1) -> borrow_date.day = (for_sort) -> borrow_date.day;
                            (tt + b + 1) -> borrow_date.month = (for_sort) -> borrow_date.month;
                            (tt + b + 1) -> borrow_date.year = (for_sort) -> borrow_date.year;
                            strcpy((tt + b + 1) -> book_name, (for_sort) ->  book_name);
                            strcpy((tt + b + 1) -> name_surname, (for_sort) -> name_surname);
                        }
                    }
                }
            }
        }
        free(for_sort);
    }
    if(choice ==  3){
        struct reader * for_sort = malloc(sizeof(r_default));
        for(int i = 0; i < size; i++){
            for(int b = 0; b < size - 1; b++){
                if((tt + b) -> reader_ticket > (tt + b + 1) -> reader_ticket){
                    (for_sort) -> reader_ticket = (tt + b) -> reader_ticket;
                    (for_sort) -> borrow_date.day = (tt + b) -> borrow_date.day;
                    (for_sort) -> borrow_date.month = (tt + b) -> borrow_date.month;
                    (for_sort) -> borrow_date.year = (tt + b) -> borrow_date.year;
                    strcpy((for_sort) -> book_name, (tt + b) -> book_name);
                    strcpy((for_sort) -> name_surname, (tt + b) -> name_surname);
                    (tt + b) -> reader_ticket = (tt + b + 1) -> reader_ticket;
                    (tt + b) -> borrow_date.day = (tt + b + 1) -> borrow_date.day;
                    (tt + b) -> borrow_date.month = (tt + b + 1) -> borrow_date.month;
                    (tt + b) -> borrow_date.year = (tt + b + 1) -> borrow_date.year;
                    strcpy((tt + b) -> book_name, (tt + b + 1) -> book_name);
                    strcpy((tt + b) -> name_surname, (tt + b + 1) -> name_surname);
                    (tt + b + 1) -> reader_ticket = (for_sort) -> reader_ticket;
                    (tt + b + 1) -> borrow_date.day = (for_sort) -> borrow_date.day;
                    (tt + b + 1) -> borrow_date.month = (for_sort) -> borrow_date.month;
                    (tt + b + 1) -> borrow_date.year = (for_sort) -> borrow_date.year;
                    strcpy((tt + b + 1) -> book_name, (for_sort) ->  book_name);
                    strcpy((tt + b + 1) -> name_surname, (for_sort) -> name_surname);
                }
            }
        }
        free(for_sort);
    }
    if(choice == 4){
        struct reader * for_sort = malloc(sizeof(r_default));
        for(int i = 0; i < size; i++){
            for(int b = 0; b < size - 1; b++){
                if(((tt + b) -> book_name[1]) > ((tt + b + 1) -> book_name[1])){
                    (for_sort) -> reader_ticket = (tt + b) -> reader_ticket;
                    (for_sort) -> borrow_date.day = (tt + b) -> borrow_date.day;
                    (for_sort) -> borrow_date.month = (tt + b) -> borrow_date.month;
                    (for_sort) -> borrow_date.year = (tt + b) -> borrow_date.year;
                    strcpy((for_sort) -> book_name, (tt + b) -> book_name);
                    strcpy((for_sort) -> name_surname, (tt + b) -> name_surname);
                    (tt + b) -> reader_ticket = (tt + b + 1) -> reader_ticket;
                    (tt + b) -> borrow_date.day = (tt + b + 1) -> borrow_date.day;
                    (tt + b) -> borrow_date.month = (tt + b + 1) -> borrow_date.month;
                    (tt + b) -> borrow_date.year = (tt + b + 1) -> borrow_date.year;
                    strcpy((tt + b) -> book_name, (tt + b + 1) -> book_name);
                    strcpy((tt + b) -> name_surname, (tt + b + 1) -> name_surname);
                    (tt + b + 1) -> reader_ticket = (for_sort) -> reader_ticket;
                    (tt + b + 1) -> borrow_date.day = (for_sort) -> borrow_date.day;
                    (tt + b + 1) -> borrow_date.month = (for_sort) -> borrow_date.month;
                    (tt + b + 1) -> borrow_date.year = (for_sort) -> borrow_date.year;
                    strcpy((tt + b + 1) -> book_name, (for_sort) ->  book_name);
                    strcpy((tt + b + 1) -> name_surname, (for_sort) -> name_surname);
                }
            }
        }
        free(for_sort);
    }
}


//Функция изменения параметров структуры....
void edit_parametrs(struct reader * tt){
    system("clear");
    printf(ANSI_COLOR_BLUE "Какой параметр вы хотите отредактировать?\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE "Номер читательского билета - 1, имя_фамилия - 2, назв.книги - 3, дату - 4: " ANSI_COLOR_RESET);
    int choice3 = 0;
    int check = scanf("%d", &choice3);

    if((choice3 > 4 || choice3 < 1) || (check == 0)){
        printf(ANSI_COLOR_RED "Некорректный ввод!\n" ANSI_COLOR_RESET);
        return;
    }
    if(choice3 == 1){
        int new_ticket_book;
        printf(ANSI_COLOR_GREEN "Введите новый номер билета: \n" ANSI_COLOR_RESET);
        scanf("%d", &new_ticket_book);
        tt -> reader_ticket = new_ticket_book;
    }
    if(choice3 == 2){
        printf(ANSI_COLOR_GREEN "ВВедите новую фамилию имя: \n" ANSI_COLOR_RESET);
        getchar();
        fgets(tt -> name_surname, 100, stdin);
    }
    if(choice3 == 3){
        printf(ANSI_COLOR_GREEN "Введите новое название книги: \n" ANSI_COLOR_RESET);
        getchar();
        fgets(tt -> book_name, 100, stdin);
    }
    if(choice3 == 4){
        printf(ANSI_COLOR_GREEN "Введите новую дату: день/месяц/год\n" ANSI_COLOR_RESET);
        scanf("%d%d%d", &(tt -> borrow_date.day), &(tt -> borrow_date.month), &(tt -> borrow_date.year));
    }
}


struct reader * search_reader(struct reader * tt, int size){
    system("clear");
    printf(ANSI_COLOR_BLUE "По какому параметру произвести поиск: \n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE "Номеру билета - 1, имя_фамилия - 2, назв.книги - 3, дата - 4, по всем - 5\n" ANSI_COLOR_RESET);
    int choice5 = 0;    scanf("%d", &choice5);

    struct reader * temp = malloc(sizeof(r_default) * size);
    if(choice5 == 1){
        int ticket_search_number;
        int new_temp_size = 0;
        printf(ANSI_COLOR_BLUE "Номер билета по которому искать: \n" ANSI_COLOR_RESET);
        scanf("%d", &ticket_search_number);
        for(int i = 0; i < size; i++){
            if((tt + i) -> reader_ticket == ticket_search_number){
                (temp + new_temp_size) ->        reader_ticket = (tt + i) -> reader_ticket;
                (temp + new_temp_size) ->        borrow_date.day = (tt + i) -> borrow_date.day;
                (temp + new_temp_size) ->        borrow_date.month = (tt + i) -> borrow_date.month;
                (temp + new_temp_size) ->        borrow_date.year = (tt + i) -> borrow_date.year;
                strcpy((temp + new_temp_size) -> name_surname, (tt + i) -> name_surname);
                strcpy((temp + new_temp_size) -> book_name, (tt + i) -> book_name);
                new_temp_size++;
            }
        }
        show_readers(temp, new_temp_size);
        free(temp);
    }
    if(choice5 == 2){
        int new_temp_size = 0;
        char search_name_surname[100];
        getchar();
        printf(ANSI_COLOR_BLUE "Имя_Фамилия для поиска: \n" ANSI_COLOR_RESET);
        fgets(search_name_surname, 100, stdin);
        for(int i = 0; i < size; i++){
            if(strcmp(search_name_surname, (tt + i) -> name_surname) == 0){
                (temp + new_temp_size) ->        reader_ticket = (tt + i) -> reader_ticket;
                (temp + new_temp_size) ->        borrow_date.day = (tt + i) -> borrow_date.day;
                (temp + new_temp_size) ->        borrow_date.month = (tt + i) -> borrow_date.month;
                (temp + new_temp_size) ->        borrow_date.year = (tt + i) -> borrow_date.year;
                strcpy((temp + new_temp_size) -> name_surname, (tt + i) -> name_surname);
                strcpy((temp + new_temp_size) -> book_name, (tt + i) -> book_name);
                new_temp_size++;
            }
        }
        show_readers(temp, new_temp_size);
        free(temp);
    }
    if(choice5 == 3){
        int new_temp_size = 0;
        char search_book_name[100];
        getchar();
        printf(ANSI_COLOR_BLUE "Название книги для поиска: \n" ANSI_COLOR_RESET);
        fgets(search_book_name, 100, stdin);
        for(int i = 0; i < size; i++){
            if(strcmp(search_book_name, (tt + i) -> book_name) == 0){
                (temp + new_temp_size) ->        reader_ticket = (tt + i) -> reader_ticket;
                (temp + new_temp_size) ->        borrow_date.day = (tt + i) -> borrow_date.day;
                (temp + new_temp_size) ->        borrow_date.month = (tt + i) -> borrow_date.month;
                (temp + new_temp_size) ->        borrow_date.year = (tt + i) -> borrow_date.year;
                strcpy((temp + new_temp_size) -> name_surname, (tt + i) -> name_surname);
                strcpy((temp + new_temp_size) -> book_name, (tt + i) -> book_name);
                new_temp_size++;
            }
        }
        show_readers(temp, new_temp_size);
        free(temp);
    }
    if(choice5 == 4){
        int new_temp_size = 0;
        struct date temp_date;
        printf(ANSI_COLOR_BLUE "Введите дату для поиска: денъ/месяц/число\n" ANSI_COLOR_RESET);
        scanf("%d%d%d", &temp_date.day, &temp_date.month, &temp_date.year);
        for(int i = 0; i < size; i++){
            if((((tt + i) -> borrow_date.day) == temp_date.day) && (((tt + i) -> borrow_date.month) == temp_date.month) && (((tt + i) -> borrow_date.year) == temp_date.year)){
                (temp + new_temp_size) ->        reader_ticket = (tt + i) -> reader_ticket;
                (temp + new_temp_size) ->        borrow_date.day = (tt + i) -> borrow_date.day;
                (temp + new_temp_size) ->        borrow_date.month = (tt + i) -> borrow_date.month;
                (temp + new_temp_size) ->        borrow_date.year = (tt + i) -> borrow_date.year;
                strcpy((temp + new_temp_size) -> name_surname, (tt + i) -> name_surname);
                strcpy((temp + new_temp_size) -> book_name, (tt + i) -> book_name);
                new_temp_size++;
            }
        }
        show_readers(temp, new_temp_size);
        free(temp);
    }
    if(choice5 == 5){
        int new_temp_size = 0;
        struct date temp_date;
        int ticket_search_number;
        char search_book_name[100];
        char search_name_surname[100];
        printf(ANSI_COLOR_BLUE "Поиск по всем параметрам.\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_BLUE "Введите номер билета: \n" ANSI_COLOR_RESET);
        scanf("%d", &ticket_search_number);
        getchar();
        printf(ANSI_COLOR_BLUE "Имя_Фамилия для поиска: \n" ANSI_COLOR_RESET);
        fgets(search_name_surname, 100, stdin);
        printf(ANSI_COLOR_BLUE "Название книги для поиска: \n" ANSI_COLOR_RESET);
        fgets(search_book_name, 100, stdin);
        printf(ANSI_COLOR_BLUE "Введите дату для поиска: денъ/месяц/число\n" ANSI_COLOR_RESET);
        scanf("%d%d%d", &temp_date.day, &temp_date.month, &temp_date.year);
        
        for(int i =0; i < size; i++){
            if((tt + i) -> reader_ticket == ticket_search_number){
                if(strcmp(search_name_surname, (tt + i) -> name_surname) == 0){
                    if(strcmp(search_book_name, (tt + i) -> book_name) == 0){
                        if((((tt + i) -> borrow_date.day) == temp_date.day) && (((tt + i) -> borrow_date.month) == temp_date.month) && (((tt + i) -> borrow_date.year) == temp_date.year)){
                            (temp + new_temp_size) ->        reader_ticket = (tt + i) -> reader_ticket;
                            (temp + new_temp_size) ->        borrow_date.day = (tt + i) -> borrow_date.day;
                            (temp + new_temp_size) ->        borrow_date.month = (tt + i) -> borrow_date.month;
                            (temp + new_temp_size) ->        borrow_date.year = (tt + i) -> borrow_date.year;
                            strcpy((temp + new_temp_size) -> name_surname, (tt + i) -> name_surname);
                            strcpy((temp + new_temp_size) -> book_name, (tt + i) -> book_name);
                            new_temp_size++;
                        }
                    }
                }
            }
        }
        show_readers(temp, new_temp_size);
        free(temp);
    }
}


//....Функция удаления элемента из структуры....
void delete_struct(struct reader * tt, int * size, int delete_arg){
    if((delete_arg > (*(size) - 1)) || (delete_arg < 0)){
        system("clear");
        printf(ANSI_COLOR_BLUE "Введен неверный аргумент для удаления!\n" ANSI_COLOR_RESET);
        return;
    }
    if((delete_arg + 1) == (*size)){
        (*size) -= 1;
        tt = realloc(tt, sizeof(r_default) * (*size));
        return;
    }
    for(int i = delete_arg; i < (*size) - 1; i++){
        strcpy((tt + i) -> name_surname, (tt + i + 1) -> name_surname);
        strcpy((tt + i) -> book_name, (tt + i + 1) -> book_name);
        (tt + i) -> reader_ticket = (tt + i + 1) -> reader_ticket;
        (tt + i) -> borrow_date.day = (tt + i + 1) -> borrow_date.day;
        (tt + i) -> borrow_date.month = (tt + i + 1) -> borrow_date.month;
        (tt + i) -> borrow_date.year = (tt + i + 1) -> borrow_date.year;
    }
    (*size) -= 1;
    tt = realloc(tt, sizeof(r_default) * (*size));
}


struct reader * search_reader2(struct reader * tt, int size){
    struct reader * temp_for_search = malloc(sizeof(r_default) * size);
    int choice6 = 0;
    printf(ANSI_COLOR_BLUE "Введите параметр для поиска на частичное совпадение: \n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE "1 - имя_фамилия, 2 - назв. книги, 3 - номер билета, дата - 4\n" ANSI_COLOR_RESET);
    if (scanf("%d", &choice6) == 0){
        return 0;
    }
    if(choice6 < 1 || choice6 > 4 || choice6 == 0){
        printf(ANSI_COLOR_RED "Введен неверный аргумент, повторите попытку снова.\n" ANSI_COLOR_RESET);
        return 0;
    }

    int schetchik = 0;
    if(choice6 == 1){
        char search_n_s[100];
        printf(ANSI_COLOR_BLUE "Введите имя_фамилия для проверки на част. совп: \n" ANSI_COLOR_RESET);
        getchar();
        fgets(search_n_s, 100, stdin);
        for(int i = 0; i < size; i++){
            if(chastichnoe_sr_strok(search_n_s, (tt + i) -> name_surname)){
                (temp_for_search + schetchik) ->        reader_ticket = (tt + i) -> reader_ticket;
                (temp_for_search + schetchik) ->        borrow_date.day = (tt + i) -> borrow_date.day;
                (temp_for_search + schetchik) ->        borrow_date.month = (tt + i) -> borrow_date.month;
                (temp_for_search + schetchik) ->        borrow_date.year = (tt + i) -> borrow_date.year;
                strcpy((temp_for_search + schetchik) -> name_surname, (tt + i) -> name_surname);
                strcpy((temp_for_search + schetchik) -> book_name, (tt + i) -> book_name);
                schetchik++;
            }
        }
        temp_for_search = realloc(temp_for_search, sizeof(r_default) * schetchik);
        show_readers(temp_for_search, schetchik);
        free(temp_for_search);
    }

    if(choice6 == 2){
        char serch_b_s[100];
        printf(ANSI_COLOR_BLUE "Введите назв книги для проверки на част. совп: \n" ANSI_COLOR_RESET);
        getchar();
        fgets(serch_b_s, 100, stdin);
        for(int i = 0; i < size; i++){
            if(chastichnoe_sr_strok(serch_b_s, (tt + i) -> book_name)){
                (temp_for_search + schetchik) ->        reader_ticket = (tt + i) -> reader_ticket;
                (temp_for_search + schetchik) ->        borrow_date.day = (tt + i) -> borrow_date.day;
                (temp_for_search + schetchik) ->        borrow_date.month = (tt + i) -> borrow_date.month;
                (temp_for_search + schetchik) ->        borrow_date.year = (tt + i) -> borrow_date.year;
                strcpy((temp_for_search + schetchik) -> name_surname, (tt + i) -> name_surname);
                strcpy((temp_for_search + schetchik) -> book_name, (tt + i) -> book_name);
                schetchik++;
            }
        }
        temp_for_search = realloc(temp_for_search, sizeof(r_default) * schetchik);
        show_readers(temp_for_search, schetchik);
        free(temp_for_search);
    }

    
    if(choice6 == 3){
        printf(ANSI_COLOR_BLUE "Введите номер билета для проверки на част. совп: \n" ANSI_COLOR_RESET);
        int chislo = 0;
        scanf("%d", &chislo);
        if(chislo < 0 || chislo == 0) return 0;
        for(int i = 0; i < size; i++){
            if(chastichnoe_sr_chisel(chislo, (tt + i) -> reader_ticket)){
                (temp_for_search + schetchik) ->        reader_ticket = (tt + i) -> reader_ticket;
                (temp_for_search + schetchik) ->        borrow_date.day = (tt + i) -> borrow_date.day;
                (temp_for_search + schetchik) ->        borrow_date.month = (tt + i) -> borrow_date.month;
                (temp_for_search + schetchik) ->        borrow_date.year = (tt + i) -> borrow_date.year;
                strcpy((temp_for_search + schetchik) -> name_surname, (tt + i) -> name_surname);
                strcpy((temp_for_search + schetchik) -> book_name, (tt + i) -> book_name);
                schetchik++;
            }
        }
        temp_for_search = realloc(temp_for_search, sizeof(r_default) * schetchik);
        show_readers(temp_for_search, schetchik);
        free(temp_for_search);
    }
    if(choice6 == 4){
        printf(ANSI_COLOR_BLUE "Введите дату(день месяц год) для проверки на част. совп: \n" ANSI_COLOR_RESET);
        struct date temp;
        scanf("%d%d%d", &(temp.day), &(temp.month), &(temp.year));
        for(int i = 0; i < size; i++){
            if(chastichnoe_sr_chisel(temp.day, (tt + i) -> borrow_date.day)){
                if(chastichnoe_sr_chisel(temp.month, (tt + i) -> borrow_date.month)){
                    if(chastichnoe_sr_chisel(temp.year, (tt + i) -> borrow_date.year)){
                        (temp_for_search + schetchik) ->        reader_ticket = (tt + i) -> reader_ticket;
                        (temp_for_search + schetchik) ->        borrow_date.day = (tt + i) -> borrow_date.day;
                        (temp_for_search + schetchik) ->        borrow_date.month = (tt + i) -> borrow_date.month;
                        (temp_for_search + schetchik) ->        borrow_date.year = (tt + i) -> borrow_date.year;
                        strcpy((temp_for_search + schetchik) -> name_surname, (tt + i) -> name_surname);
                        strcpy((temp_for_search + schetchik) -> book_name, (tt + i) -> book_name);
                        schetchik++;
                    }
                }
            }
        }
        temp_for_search = realloc(temp_for_search, sizeof(r_default) * schetchik);
        show_readers(temp_for_search, schetchik);
        free(temp_for_search);
    }
}


//....Функция вывода элементов массива структур....
void show_readers(struct reader * tt, int size){
    system("clear");
    printf(ANSI_COLOR_RED "Номер:\tФамилия_Имя:\t\tНазвание книги:\t\tНомер билета:\tДата возрата:\n" ANSI_COLOR_RESET);
    for(int i = 0; i < size; i++){
        printf(ANSI_COLOR_RED "%d" ANSI_COLOR_RESET, i + 1);                   put_space(8 - amount_of_digits(i + 1)); 
        print((tt + i) -> name_surname);                                       put_space(24 - (text_size((tt + i) -> name_surname) / 2) - 1);
        print((tt + i) -> book_name);                                          put_space(24 - (text_size((tt + i) -> book_name) / 2) - 1);
        printf("%d", (tt + i) -> reader_ticket);                               put_space(16 - amount_of_digits((tt + i) -> reader_ticket));
        printf("%d.%d.%d", (tt + i) -> borrow_date.day, 
                (tt + i) -> borrow_date.month, (tt + i) -> borrow_date.year);
        printf("\n");
    }
    printf("\n\n");
}


//Первый аргумент отвечает за число по частичному поиску
bool chastichnoe_sr_chisel(int num1, int num2){
    if(amount_of_digits(num1) > amount_of_digits(num2)){
        return false;
    }
    else{
        int ms[amount_of_digits(num1)];
        int ms2[amount_of_digits(num2)];

        int schet = 0;
        while(num1 != 0){
            ms[schet] = num1 % 10;
            num1 /= 10;
            schet++;
        }
        int schet2 = 0;
        while(num2 != 0){
            ms2[schet2] = num2 % 10;
            num2 /= 10;
            schet2++;
        }

        msReverse(ms, schet);
        msReverse(ms2, schet2);

        for(int i = 0; i < schet; i++){
            if(ms[i] != ms2[i]){
                return false;
            }
        }
        return true;
    }
}


bool chastichnoe_sr_strok(char * str1, char * str2){
    int i = 0;
    while(str1[i + 1] != '\0'){
        if(str1[i] != str2[i]){
            return false;
        }
        i++;
    }
    return true;
}



//....Функция подсчета количества цифр в числе....
int amount_of_digits(int number){
    int k = 0; 
    while(number != 0){
        number = number / 10;
        k++;
    }
    return k;
}


//....Функция вывода нужного количества пробелов....
void put_space(int amount){
    for(int i = 0; i < amount; i++){
        putchar(' ');
    }
}


//....Функция вывода без символа перевода строки....
void print(char * text){
    int index = 0;
    while(text[index] != '\n'){
        putchar(text[index]);
        index++;
    }
    return;
}


//СИмвольный размер передаваемого слова....
int text_size(char * text){
    int i = 0;
    while(text[i] != '\0'){
        i++;
    }
    return i - 1;
}

int msReverse(int * ms, int size){
    for(int i = 0; i < size / 2; i++){
        int temp = ms[i];
        ms[i] = ms[size - 1 - i];
        ms[size - 1 - i] = temp;
    }
}



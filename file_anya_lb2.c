#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define SIZE_FOR_ARR 5
#define SIZE_FOR_STR 50
#define ANSI_COLOR_BLUE  "\x1b[34m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RED   "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"


struct student_info{
    char f_name[SIZE_FOR_STR];
    char s_name[SIZE_FOR_STR];
    char surname[SIZE_FOR_STR];
    int  semestr_number;
};

union ex_marks{
    int * numbers;
};

typedef struct student{
    struct student_info   info_stud;
    union      ex_marks   student_exams[2];
} student_def;


enum f_semestr{MATH = 0, PHYSICS, PI, IKG, PHILOSOPHY};
enum s_semestr{LOGIC = 5, POLITOLOGY, ENGLISH, AILOVT, HISTORY};
enum t_semestr{NETWORKS = 10, SYS_PROGRAMMING, KPIYAP, RUSSIAN, BELARRUSIAN};
enum c_semestr{ALGHORITMS = 15, DATA_STRUCTURS, CRIPTOGRAPHY, OOP, KPP};


char * f_sem[] = {"Math", "Physics", "PI", "IKG", "Philosophy"};
char * s_sem[] = {"Logic", "Politology", "English", "AILOVT", "History"};
char * t_sem[] = {"Networks", "Sys Programming", "KPIYAP", "Russian", "Belarussian"};
char * c_sem[] = {"Alghoritms", "Data Structurs", "Criptography", "OOP", "KPP"};



bool chastichnoe_sr_chisel  (int num1, int num2);
bool chastichnoe_sr_strok   (char * str1, char * str2);
int msReverse               (int * ms, int size);
void readers_sort           (struct student * tt, int size);
void search_reader2         (struct student * tt, int size);
void struct_search          (struct student * tt, int size);
void edit_parametrs         (struct student * tt);
void delete_struct          (struct student * tt, int * size, int delete_arg);
void show_struct            (struct student * students, int size);
void put_space              (int value);
void print                  (char * text);
int  amount_of_digits       (int number);
int  text_size              (char * text);
int sum_marks               (struct student * tt);

int main(int argc, char * argv[]){
    int SIZE = 0;
    struct student * students = malloc(SIZE * sizeof(student_def));

    while(1){
        printf(ANSI_COLOR_GREEN "Выберите операцию над списком:\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_GREEN "Просмотр списка студентов: 1\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_GREEN "Редактирование параметров студента: 2\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_GREEN "Добавление студента в список: 3\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_GREEN "Удаление студента из списка: 4\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_GREEN "Поиск студента по заданному параметру: 5\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_GREEN "Сортировка по заданному параметру: 6\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_GREEN "Поиск по частичному совпадению: 7\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_GREEN "Студент с наивысшим средним баллом: 8\n" ANSI_COLOR_RESET); 
        printf(ANSI_COLOR_GREEN "Студент с наименьшим средним баллом: 9\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_GREEN "Сортировка студентов по среднему баллу: 10\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_GREEN "Выход: 11\n" ANSI_COLOR_RESET);

        //Проверка на коректный ввод...
        int choice = 0;
        int check_on = scanf("%d", &choice);
        while(check_on != 1){
            printf(ANSI_COLOR_RED "Введен неверный параметр, повторите попытку.\n" ANSI_COLOR_RESET);
            getchar();
            check_on = scanf("%d", &choice);
        }
        //............


        if(choice == 1) show_struct(students, SIZE);
        if(choice == 2){
            printf(ANSI_COLOR_BLUE "Номер какого студента желаете редактировать:\n" ANSI_COLOR_RESET);
            int select_stud_for_del = 0;
            int choice_e = scanf("%d", &select_stud_for_del);
            while(select_stud_for_del < 1 || select_stud_for_del > SIZE || choice_e == 0){
                printf(ANSI_COLOR_RED "Введен нверный номер студента для редактирования!\n" ANSI_COLOR_RESET);
                getchar();
                choice_e = scanf("%d", &select_stud_for_del);
            }
            edit_parametrs(students + select_stud_for_del - 1);

        }
        if(choice == 3){
            SIZE += 1;
            students = realloc(students, sizeof(student_def) * SIZE);
            system("clear");
            getchar();
            printf(ANSI_COLOR_BLUE "Введите имя:\n" ANSI_COLOR_RESET);
            fgets((students + SIZE - 1) -> info_stud.f_name, SIZE_FOR_STR, stdin);
            printf(ANSI_COLOR_BLUE "Введите фамилию:\n" ANSI_COLOR_RESET);
            fgets((students + SIZE - 1) -> info_stud.surname, SIZE_FOR_STR, stdin);
            printf(ANSI_COLOR_BLUE "Введите отчество:\n" ANSI_COLOR_RESET);
            fgets((students + SIZE - 1) -> info_stud.s_name, SIZE_FOR_STR, stdin);
            printf(ANSI_COLOR_BLUE "Введите номер семестра:\n" ANSI_COLOR_RESET);
            int check_vvod = scanf("%d", &((students + SIZE - 1) -> info_stud.semestr_number));
            while(check_vvod == 0 || (students + SIZE - 1) -> info_stud.semestr_number < 1 || (students + SIZE - 1) -> info_stud.semestr_number > 4){
                printf(ANSI_COLOR_RED "Введен неверный номер семетра, повторите ввод.\n" ANSI_COLOR_RESET);
                getchar();
                int check_vvod = scanf("%d", &((students + SIZE - 1) -> info_stud.semestr_number));
            }
            (students + SIZE - 1) -> student_exams[0].numbers = malloc(sizeof(int) * SIZE_FOR_ARR);
            (students + SIZE - 1) -> student_exams[1].numbers = malloc(sizeof(int) * SIZE_FOR_ARR);
            if((students + SIZE - 1) -> info_stud.semestr_number == 1){
                (students + SIZE - 1) -> student_exams[0].numbers[0] = MATH;
                (students + SIZE - 1) -> student_exams[0].numbers[1] = PHYSICS;
                (students + SIZE - 1) -> student_exams[0].numbers[2] = PI;
                (students + SIZE - 1) -> student_exams[0].numbers[3] = IKG;
                (students + SIZE - 1) -> student_exams[0].numbers[4] = PHILOSOPHY;

                for(int i = 0; i < SIZE_FOR_ARR; i++){
                    printf(ANSI_COLOR_BLUE "Введите оценку для %d." ANSI_COLOR_RESET, (students + SIZE - 1) -> student_exams[0].numbers[i]); fputs(f_sem[i], stdout); printf(": ");
                    int check_result = scanf("%d", &((students + SIZE - 1) -> student_exams[1].numbers[i]));
                    while(check_result == 0 || ((students + SIZE - 1) -> student_exams[1].numbers[i]) < 1 || ((students + SIZE - 1) -> student_exams[1].numbers[i]) > 10){
                        printf(ANSI_COLOR_RED "Введена неверная оценка!\n" ANSI_COLOR_RESET);
                        getchar();
                        check_result = scanf("%d", &((students + SIZE - 1) -> student_exams[1].numbers[i]));
                    }
                }
            }
            if((students + SIZE - 1) -> info_stud.semestr_number == 2){
                (students + SIZE - 1) -> student_exams[0].numbers[0] = LOGIC;
                (students + SIZE - 1) -> student_exams[0].numbers[1] = POLITOLOGY;
                (students + SIZE - 1) -> student_exams[0].numbers[2] = ENGLISH;
                (students + SIZE - 1) -> student_exams[0].numbers[3] = AILOVT;
                (students + SIZE - 1) -> student_exams[0].numbers[4] = HISTORY;

                for(int i = 0; i < SIZE_FOR_ARR; i++){
                    printf(ANSI_COLOR_BLUE "Введите оценку для %d." ANSI_COLOR_RESET, (students + SIZE - 1) -> student_exams[0].numbers[i]); fputs(s_sem[i], stdout); printf(": ");
                    int check_result = scanf("%d", &((students + SIZE - 1) -> student_exams[1].numbers[i]));
                    while(check_result == 0 || ((students + SIZE - 1) -> student_exams[1].numbers[i]) < 1 || ((students + SIZE - 1) -> student_exams[1].numbers[i]) > 10){
                        printf(ANSI_COLOR_RED "Введена неверная оценка!\n" ANSI_COLOR_RESET);
                        getchar();
                        check_result = scanf("%d", &((students + SIZE - 1) -> student_exams[1].numbers[i]));
                    }
                }
            }
            
            if((students + SIZE - 1) -> info_stud.semestr_number == 3){
                (students + SIZE - 1) -> student_exams[0].numbers[0] = NETWORKS;
                (students + SIZE - 1) -> student_exams[0].numbers[1] = SYS_PROGRAMMING;
                (students + SIZE - 1) -> student_exams[0].numbers[2] = KPIYAP;
                (students + SIZE - 1) -> student_exams[0].numbers[3] = RUSSIAN;
                (students + SIZE - 1) -> student_exams[0].numbers[4] = BELARRUSIAN;

                for(int i = 0; i < SIZE_FOR_ARR; i++){
                    printf(ANSI_COLOR_BLUE "Введите оценку для %d." ANSI_COLOR_RESET, (students + SIZE - 1) -> student_exams[0].numbers[i]); fputs(t_sem[i], stdout); printf(": ");
                    int check_result = scanf("%d", &((students + SIZE - 1) -> student_exams[1].numbers[i]));
                    while(check_result == 0 || ((students + SIZE - 1) -> student_exams[1].numbers[i]) < 1 || ((students + SIZE - 1) -> student_exams[1].numbers[i]) > 10){
                        printf(ANSI_COLOR_RED "Введена неверная оценка!\n" ANSI_COLOR_RESET);
                        getchar();
                        check_result = scanf("%d", &((students + SIZE - 1) -> student_exams[1].numbers[i]));
                    }
                }
            }
            if((students + SIZE - 1) -> info_stud.semestr_number == 4){
                (students + SIZE - 1) -> student_exams[0].numbers[0] = ALGHORITMS;
                (students + SIZE - 1) -> student_exams[0].numbers[1] = DATA_STRUCTURS;
                (students + SIZE - 1) -> student_exams[0].numbers[2] = CRIPTOGRAPHY;
                (students + SIZE - 1) -> student_exams[0].numbers[3] = OOP;
                (students + SIZE - 1) -> student_exams[0].numbers[4] = KPP;

                for(int i = 0; i < SIZE_FOR_ARR; i++){
                    printf(ANSI_COLOR_BLUE "Введите оценку для %d." ANSI_COLOR_RESET, (students + SIZE - 1) -> student_exams[0].numbers[i]); fputs(c_sem[i], stdout); printf(": ");
                    int check_result = scanf("%d", &((students + SIZE - 1) -> student_exams[1].numbers[i]));
                    while(check_result == 0 || ((students + SIZE - 1) -> student_exams[1].numbers[i]) < 1 || ((students + SIZE - 1) -> student_exams[1].numbers[i]) > 10){
                        printf(ANSI_COLOR_RED "Введена неверная оценка!\n" ANSI_COLOR_RESET);
                        getchar();
                        check_result = scanf("%d", &((students + SIZE - 1) -> student_exams[1].numbers[i]));
                    }
                }
            }
        }

        if(choice == 4){
            system("clear");
            printf(ANSI_COLOR_BLUE "Введите номер студента для удаления: \n" ANSI_COLOR_RESET);
            int choice_f = 0;
            scanf("%d", &(choice_f));
            delete_struct(students, &SIZE, choice_f - 1);
        }
        if(choice == 5) struct_search(students, SIZE);
        if(choice == 6) readers_sort(students, SIZE);
        if(choice == 7) search_reader2(students, SIZE);
        if(choice == 8){
            int stud_num = 0;
            int sum = 0;
            for(int i = 0; i < SIZE; i++){
                if(sum_marks(students + i) > sum){
                    sum = sum_marks(students + i);
                    stud_num = i + 1;
                }
            }
            printf(ANSI_COLOR_BLUE "Наибольший средний балл у студента под номером %d: %d\n", stud_num, sum); printf(ANSI_COLOR_RESET);
        }
        if(choice == 9){
            int stud_num = 0;
            int sum = 40;
            for(int i = 0; i < SIZE; i++){
                if(sum_marks(students + i) < sum){
                    sum = sum_marks(students + i);
                    stud_num = i + 1;
                }
            }
            printf(ANSI_COLOR_BLUE "Наименьший средний балл у студента под номером %d: %d\n", stud_num, sum); printf(ANSI_COLOR_RESET);
        }
        if(choice == 10){
            struct student * for_sort = malloc(sizeof(student_def));
            (for_sort) -> student_exams[0].numbers = malloc(sizeof(int) * SIZE_FOR_ARR);
            (for_sort) -> student_exams[1].numbers = malloc(sizeof(int) * SIZE_FOR_ARR);
            for(int i = 0; i < SIZE; i++){
                for(int b = 0; b < SIZE - 1; b++){
                    if(sum_marks(students + b) > sum_marks(students + b + 1)){
                        strcpy((for_sort) -> info_stud.f_name, (students + b) -> info_stud.f_name);
                        strcpy((for_sort) -> info_stud.s_name, (students + b) -> info_stud.s_name);
                        strcpy((for_sort) -> info_stud.surname, (students + b) -> info_stud.surname);
                        (for_sort) -> info_stud.semestr_number = (students + b) -> info_stud.semestr_number;
                        for(int j = 0; j < SIZE_FOR_ARR; j++){
                            (for_sort) -> student_exams[0].numbers[j] = (students + b) -> student_exams[0].numbers[j];
                            (for_sort) -> student_exams[1].numbers[j] = (students + b) -> student_exams[1].numbers[j];                
                        }
                        strcpy((students + b) -> info_stud.f_name, (students + b + 1) -> info_stud.f_name);
                        strcpy((students + b) -> info_stud.s_name, (students + b + 1) -> info_stud.s_name);
                        strcpy((students + b) -> info_stud.surname, (students + b + 1) -> info_stud.surname);
                        (students + b) -> info_stud.semestr_number = (students + b + 1) -> info_stud.semestr_number;
                        for(int j = 0; j < SIZE_FOR_ARR; j++){
                            (students + b) -> student_exams[0].numbers[j] = (students + b + 1) -> student_exams[0].numbers[j];
                            (students + b) -> student_exams[1].numbers[j] = (students + b + 1) -> student_exams[1].numbers[j];                
                        }
                        strcpy((students + b + 1) -> info_stud.f_name, (for_sort) -> info_stud.f_name);
                        strcpy((students + b + 1) -> info_stud.s_name, (for_sort) -> info_stud.s_name);
                        strcpy((students + b + 1) -> info_stud.surname, (for_sort) -> info_stud.surname);
                        (students + b + 1) -> info_stud.semestr_number = (for_sort) -> info_stud.semestr_number;
                        for(int j = 0; j < SIZE_FOR_ARR; j++){
                            (students + b + 1) -> student_exams[0].numbers[j] = (for_sort) -> student_exams[0].numbers[j];
                            (students + b + 1) -> student_exams[1].numbers[j] = (for_sort) -> student_exams[1].numbers[j];                     
                        }
                    }
                }
            }
            show_struct(students, SIZE);
            free(for_sort -> student_exams[0].numbers);
            free(for_sort -> student_exams[1].numbers);
            free(for_sort);
        }    
        if(choice == 11) break;
    }
}

int sum_marks(struct student * tt){
    int result = 0;
    for(int i = 0; i < SIZE_FOR_ARR; i++){
        result += (tt) -> student_exams[1].numbers[i];
    }
    return result;
}

void search_reader2(struct student * tt, int size){
    struct student * temp_for_search = malloc(sizeof(student_def) * size);
    int choice6 = 0;
    printf(ANSI_COLOR_BLUE "Введите параметр для поиска на частичное совпадение: \n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE "1 - имя, 2 - фамилия, 3 - отчество, номер семестра - 4\n" ANSI_COLOR_RESET);
    if (scanf("%d", &choice6) == 0){
        return;
    }
    if(choice6 < 1 || choice6 > 4 || choice6 == 0){
        printf(ANSI_COLOR_RED "Введен неверный аргумент, повторите попытку снова.\n" ANSI_COLOR_RESET);
        return;
    }

    int schetchik = 0;
    if(choice6 == 1){
        char search_n_s[100];
        printf(ANSI_COLOR_BLUE "Введите имя для проверки на част. совп: \n" ANSI_COLOR_RESET);
        getchar();
        fgets(search_n_s, 100, stdin);
        for(int i = 0; i < size; i++){
            if(chastichnoe_sr_strok(search_n_s, (tt + i) -> info_stud.f_name)){
                strcpy((temp_for_search + schetchik) -> info_stud.f_name, (tt + i) -> info_stud.f_name);
                strcpy((temp_for_search + schetchik) -> info_stud.s_name, (tt + i) -> info_stud.s_name);
                strcpy((temp_for_search + schetchik) -> info_stud.surname, (tt + i) -> info_stud.surname);
                (temp_for_search + schetchik) -> info_stud.semestr_number = (tt + i) -> info_stud.semestr_number;
                (temp_for_search + schetchik) -> student_exams[0].numbers = malloc(sizeof(int) * SIZE_FOR_ARR);
                (temp_for_search + schetchik) -> student_exams[1].numbers = malloc(sizeof(int) * SIZE_FOR_ARR);
                for(int b = 0; b < SIZE_FOR_ARR; b++){
                    (temp_for_search + schetchik) -> student_exams[0].numbers[b] = (tt + i) -> student_exams[0].numbers[b];
                    (temp_for_search + schetchik) -> student_exams[1].numbers[b] = (tt + i) -> student_exams[1].numbers[b];
                }
                schetchik++;
            }
        }
        temp_for_search = realloc(temp_for_search, sizeof(student_def) * schetchik);
        show_struct(temp_for_search, schetchik);
        for(int i = 0; i < schetchik; i++){
            free((temp_for_search + i) -> student_exams[0].numbers);
            free((temp_for_search + i) -> student_exams[1].numbers);
        }
        free(temp_for_search);
    }

    if(choice6 == 2){
        char serch_b_s[100];
        printf(ANSI_COLOR_BLUE "Введите фамилию для проверки на част. совп: \n" ANSI_COLOR_RESET);
        getchar();
        fgets(serch_b_s, 100, stdin);
        for(int i = 0; i < size; i++){
            if(chastichnoe_sr_strok(serch_b_s, (tt + i) -> info_stud.surname)){
                strcpy((temp_for_search + schetchik) -> info_stud.f_name, (tt + i) -> info_stud.f_name);
                strcpy((temp_for_search + schetchik) -> info_stud.s_name, (tt + i) -> info_stud.s_name);
                strcpy((temp_for_search + schetchik) -> info_stud.surname, (tt + i) -> info_stud.surname);
                (temp_for_search + schetchik) -> info_stud.semestr_number = (tt + i) -> info_stud.semestr_number;
                (temp_for_search + schetchik) -> student_exams[0].numbers = malloc(sizeof(int) * SIZE_FOR_ARR);
                (temp_for_search + schetchik) -> student_exams[1].numbers = malloc(sizeof(int) * SIZE_FOR_ARR);
                for(int b = 0; b < SIZE_FOR_ARR; b++){
                    (temp_for_search + schetchik) -> student_exams[0].numbers[b] = (tt + i) -> student_exams[0].numbers[b];
                    (temp_for_search + schetchik) -> student_exams[1].numbers[b] = (tt + i) -> student_exams[1].numbers[b];
                }
                schetchik++;
            }
        }
        temp_for_search = realloc(temp_for_search, sizeof(student_def) * schetchik);
        show_struct(temp_for_search, schetchik);
        for(int i = 0; i < schetchik; i++){
            free((temp_for_search + i) -> student_exams[0].numbers);
            free((temp_for_search + i) -> student_exams[1].numbers);
        }
        free(temp_for_search);
    }

    
    if(choice6 == 3){
        char serch_b_s[100];
        printf(ANSI_COLOR_BLUE "Введите отчество для проверки на част. совп: \n" ANSI_COLOR_RESET);
        getchar();
        fgets(serch_b_s, 100, stdin);
        for(int i = 0; i < size; i++){
            if(chastichnoe_sr_strok(serch_b_s, (tt + i) -> info_stud.s_name)){
                strcpy((temp_for_search + schetchik) -> info_stud.f_name, (tt + i) -> info_stud.f_name);
                strcpy((temp_for_search + schetchik) -> info_stud.s_name, (tt + i) -> info_stud.s_name);
                strcpy((temp_for_search + schetchik) -> info_stud.surname, (tt + i) -> info_stud.surname);
                (temp_for_search + schetchik) -> info_stud.semestr_number = (tt + i) -> info_stud.semestr_number;
                (temp_for_search + schetchik) -> student_exams[0].numbers = malloc(sizeof(int) * SIZE_FOR_ARR);
                (temp_for_search + schetchik) -> student_exams[1].numbers = malloc(sizeof(int) * SIZE_FOR_ARR);
                for(int b = 0; b < SIZE_FOR_ARR; b++){
                    (temp_for_search + schetchik) -> student_exams[0].numbers[b] = (tt + i) -> student_exams[0].numbers[b];
                    (temp_for_search + schetchik) -> student_exams[1].numbers[b] = (tt + i) -> student_exams[1].numbers[b];
                }
                schetchik++;
            }
        }
        temp_for_search = realloc(temp_for_search, sizeof(student_def) * schetchik);
        show_struct(temp_for_search, schetchik);
        for(int i = 0; i < schetchik; i++){
            free((temp_for_search + i) -> student_exams[0].numbers);
            free((temp_for_search + i) -> student_exams[1].numbers);
        }
        free(temp_for_search);
    }
    if(choice6 == 4){
        printf(ANSI_COLOR_BLUE "Введите номер семестра для проверки на част. совп: \n" ANSI_COLOR_RESET);
        int chislo = 0;
        scanf("%d", &chislo);
        if(chislo < 0 || chislo == 0) return;
        for(int i = 0; i < size; i++){
            if(chastichnoe_sr_chisel(chislo, (tt + i) -> info_stud.semestr_number)){
                strcpy((temp_for_search + schetchik) -> info_stud.f_name, (tt + i) -> info_stud.f_name);
                strcpy((temp_for_search + schetchik) -> info_stud.s_name, (tt + i) -> info_stud.s_name);
                strcpy((temp_for_search + schetchik) -> info_stud.surname, (tt + i) -> info_stud.surname);
                (temp_for_search + schetchik) -> info_stud.semestr_number = (tt + i) -> info_stud.semestr_number;
                (temp_for_search + schetchik) -> student_exams[0].numbers = malloc(sizeof(int) * SIZE_FOR_ARR);
                (temp_for_search + schetchik) -> student_exams[1].numbers = malloc(sizeof(int) * SIZE_FOR_ARR);
                for(int b = 0; b < SIZE_FOR_ARR; b++){
                    (temp_for_search + schetchik) -> student_exams[0].numbers[b] = (tt + i) -> student_exams[0].numbers[b];
                    (temp_for_search + schetchik) -> student_exams[1].numbers[b] = (tt + i) -> student_exams[1].numbers[b];
                }
                schetchik++;
            }
        }
        temp_for_search = realloc(temp_for_search, sizeof(student_def) * schetchik);
        show_struct(temp_for_search, schetchik);
        for(int i = 0; i < schetchik; i++){
            free((temp_for_search + i) -> student_exams[0].numbers);
            free((temp_for_search + i) -> student_exams[1].numbers);
        }
        free(temp_for_search);
    }
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

void readers_sort(struct student * tt, int size){
    printf(ANSI_COLOR_BLUE "По какому параметру нужно выполнить сортировку? \n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE "имя - 1, фамилия - 3, отчество  - 2, номер семестра - 4\n" ANSI_COLOR_RESET);
    int choice = 0; 
    int check = scanf("%d", &choice);
    if(check == 0 || choice > 4 || choice < 0){
        printf(ANSI_COLOR_RED "Введен неверный аргумент!\n" ANSI_COLOR_RESET);
        return;
    }

    if(choice == 1){
        struct student * for_sort = malloc(sizeof(student_def));
        (for_sort) -> student_exams[0].numbers = malloc(sizeof(int) * SIZE_FOR_ARR);
        (for_sort) -> student_exams[1].numbers = malloc(sizeof(int) * SIZE_FOR_ARR);

        for(int i = 0; i < size; i++){
            for(int b = 0; b < size - 1; b++){
                if((tt + b) -> info_stud.f_name[0] > (tt + b + 1) -> info_stud.f_name[0]){
                    strcpy((for_sort) -> info_stud.f_name, (tt + b) -> info_stud.f_name);
                    strcpy((for_sort) -> info_stud.s_name, (tt + b) -> info_stud.s_name);
                    strcpy((for_sort) -> info_stud.surname, (tt + b) -> info_stud.surname);
                    (for_sort) -> info_stud.semestr_number = (tt + b) -> info_stud.semestr_number;
                    for(int j = 0; j < SIZE_FOR_ARR; j++){
                        (for_sort) -> student_exams[0].numbers[j] = (tt + b) -> student_exams[0].numbers[j];
                        (for_sort) -> student_exams[1].numbers[j] = (tt + b) -> student_exams[1].numbers[j];                
                    }
                    strcpy((tt + b) -> info_stud.f_name, (tt + b + 1) -> info_stud.f_name);
                    strcpy((tt + b) -> info_stud.s_name, (tt + b + 1) -> info_stud.s_name);
                    strcpy((tt + b) -> info_stud.surname, (tt + b + 1) -> info_stud.surname);
                    (tt + b) -> info_stud.semestr_number = (tt + b + 1) -> info_stud.semestr_number;
                    for(int j = 0; j < SIZE_FOR_ARR; j++){
                        (tt + b) -> student_exams[0].numbers[j] = (tt + b + 1) -> student_exams[0].numbers[j];
                        (tt + b) -> student_exams[1].numbers[j] = (tt + b + 1) -> student_exams[1].numbers[j];                
                    }
                    strcpy((tt + b + 1) -> info_stud.f_name, (for_sort) -> info_stud.f_name);
                    strcpy((tt + b + 1) -> info_stud.s_name, (for_sort) -> info_stud.s_name);
                    strcpy((tt + b + 1) -> info_stud.surname, (for_sort) -> info_stud.surname);
                    (tt + b + 1) -> info_stud.semestr_number = (for_sort) -> info_stud.semestr_number;
                    for(int j = 0; j < SIZE_FOR_ARR; j++){
                        (tt + b + 1) -> student_exams[0].numbers[j] = (for_sort) -> student_exams[0].numbers[j];
                        (tt + b + 1) -> student_exams[1].numbers[j] = (for_sort) -> student_exams[1].numbers[j];                
                    }
                }
                else if((tt + b) -> info_stud.f_name[0] == (tt + b + 1) -> info_stud.f_name[0]){
                    if((tt + b) -> info_stud.f_name[1] > (tt + b + 1) -> info_stud.f_name[1]){
                        strcpy((for_sort) -> info_stud.f_name, (tt + b) -> info_stud.f_name);
                        strcpy((for_sort) -> info_stud.s_name, (tt + b) -> info_stud.s_name);
                        strcpy((for_sort) -> info_stud.surname, (tt + b) -> info_stud.surname);
                        (for_sort) -> info_stud.semestr_number = (tt + b) -> info_stud.semestr_number;
                        for(int j = 0; j < SIZE_FOR_ARR; j++){
                            (for_sort) -> student_exams[0].numbers[j] = (tt + b) -> student_exams[0].numbers[j];
                            (for_sort) -> student_exams[1].numbers[j] = (tt + b) -> student_exams[1].numbers[j];                
                        }
                        strcpy((tt + b) -> info_stud.f_name, (tt + b + 1) -> info_stud.f_name);
                        strcpy((tt + b) -> info_stud.s_name, (tt + b + 1) -> info_stud.s_name);
                        strcpy((tt + b) -> info_stud.surname, (tt + b + 1) -> info_stud.surname);
                        (tt + b) -> info_stud.semestr_number = (tt + b + 1) -> info_stud.semestr_number;
                        for(int j = 0; j < SIZE_FOR_ARR; j++){
                            (tt + b) -> student_exams[0].numbers[j] = (tt + b + 1) -> student_exams[0].numbers[j];
                            (tt + b) -> student_exams[1].numbers[j] = (tt + b + 1) -> student_exams[1].numbers[j];                
                        }
                        strcpy((tt + b + 1) -> info_stud.f_name, (for_sort) -> info_stud.f_name);
                        strcpy((tt + b + 1) -> info_stud.s_name, (for_sort) -> info_stud.s_name);
                        strcpy((tt + b + 1) -> info_stud.surname, (for_sort) -> info_stud.surname);
                        (tt + b + 1) -> info_stud.semestr_number = (for_sort) -> info_stud.semestr_number;
                        for(int j = 0; j < SIZE_FOR_ARR; j++){
                            (tt + b + 1) -> student_exams[0].numbers[j] = (for_sort) -> student_exams[0].numbers[j];
                            (tt + b + 1) -> student_exams[1].numbers[j] = (for_sort) -> student_exams[1].numbers[j];                
                        }
                    }
                }
            }
        }
        free(for_sort -> student_exams[0].numbers);
        free(for_sort -> student_exams[1].numbers);
        free(for_sort);
    }
    if(choice == 2){
        struct student * for_sort = malloc(sizeof(student_def));
        (for_sort) -> student_exams[0].numbers = malloc(sizeof(int) * SIZE_FOR_ARR);
        (for_sort) -> student_exams[1].numbers = malloc(sizeof(int) * SIZE_FOR_ARR);

        for(int i = 0; i < size; i++){
            for(int b = 0; b < size - 1; b++){
                if((tt + b) -> info_stud.s_name[0] > (tt + b + 1) -> info_stud.s_name[0]){
                    strcpy((for_sort) -> info_stud.f_name, (tt + b) -> info_stud.f_name);
                    strcpy((for_sort) -> info_stud.s_name, (tt + b) -> info_stud.s_name);
                    strcpy((for_sort) -> info_stud.surname, (tt + b) -> info_stud.surname);
                    (for_sort) -> info_stud.semestr_number = (tt + b) -> info_stud.semestr_number;
                    for(int j = 0; j < SIZE_FOR_ARR; j++){
                        (for_sort) -> student_exams[0].numbers[j] = (tt + b) -> student_exams[0].numbers[j];
                        (for_sort) -> student_exams[1].numbers[j] = (tt + b) -> student_exams[1].numbers[j];                
                    }
                    strcpy((tt + b) -> info_stud.f_name, (tt + b + 1) -> info_stud.f_name);
                    strcpy((tt + b) -> info_stud.s_name, (tt + b + 1) -> info_stud.s_name);
                    strcpy((tt + b) -> info_stud.surname, (tt + b + 1) -> info_stud.surname);
                    (tt + b) -> info_stud.semestr_number = (tt + b + 1) -> info_stud.semestr_number;
                    for(int j = 0; j < SIZE_FOR_ARR; j++){
                        (tt + b) -> student_exams[0].numbers[j] = (tt + b + 1) -> student_exams[0].numbers[j];
                        (tt + b) -> student_exams[1].numbers[j] = (tt + b + 1) -> student_exams[1].numbers[j];                
                    }
                    strcpy((tt + b + 1) -> info_stud.f_name, (for_sort) -> info_stud.f_name);
                    strcpy((tt + b + 1) -> info_stud.s_name, (for_sort) -> info_stud.s_name);
                    strcpy((tt + b + 1) -> info_stud.surname, (for_sort) -> info_stud.surname);
                    (tt + b + 1) -> info_stud.semestr_number = (for_sort) -> info_stud.semestr_number;
                    for(int j = 0; j < SIZE_FOR_ARR; j++){
                        (tt + b + 1) -> student_exams[0].numbers[j] = (for_sort) -> student_exams[0].numbers[j];
                        (tt + b + 1) -> student_exams[1].numbers[j] = (for_sort) -> student_exams[1].numbers[j];                
                    }
                }
                else if((tt + b) -> info_stud.s_name[0] == (tt + b + 1) -> info_stud.s_name[0]){
                    if((tt + b) -> info_stud.s_name[1] > (tt + b + 1) -> info_stud.s_name[1]){
                        strcpy((for_sort) -> info_stud.f_name, (tt + b) -> info_stud.f_name);
                        strcpy((for_sort) -> info_stud.s_name, (tt + b) -> info_stud.s_name);
                        strcpy((for_sort) -> info_stud.surname, (tt + b) -> info_stud.surname);
                        (for_sort) -> info_stud.semestr_number = (tt + b) -> info_stud.semestr_number;
                        for(int j = 0; j < SIZE_FOR_ARR; j++){
                            (for_sort) -> student_exams[0].numbers[j] = (tt + b) -> student_exams[0].numbers[j];
                            (for_sort) -> student_exams[1].numbers[j] = (tt + b) -> student_exams[1].numbers[j];                
                        }
                        strcpy((tt + b) -> info_stud.f_name, (tt + b + 1) -> info_stud.f_name);
                        strcpy((tt + b) -> info_stud.s_name, (tt + b + 1) -> info_stud.s_name);
                        strcpy((tt + b) -> info_stud.surname, (tt + b + 1) -> info_stud.surname);
                        (tt + b) -> info_stud.semestr_number = (tt + b + 1) -> info_stud.semestr_number;
                        for(int j = 0; j < SIZE_FOR_ARR; j++){
                            (tt + b) -> student_exams[0].numbers[j] = (tt + b + 1) -> student_exams[0].numbers[j];
                            (tt + b) -> student_exams[1].numbers[j] = (tt + b + 1) -> student_exams[1].numbers[j];                
                        }
                        strcpy((tt + b + 1) -> info_stud.f_name, (for_sort) -> info_stud.f_name);
                        strcpy((tt + b + 1) -> info_stud.s_name, (for_sort) -> info_stud.s_name);
                        strcpy((tt + b + 1) -> info_stud.surname, (for_sort) -> info_stud.surname);
                        (tt + b + 1) -> info_stud.semestr_number = (for_sort) -> info_stud.semestr_number;
                        for(int j = 0; j < SIZE_FOR_ARR; j++){
                            (tt + b + 1) -> student_exams[0].numbers[j] = (for_sort) -> student_exams[0].numbers[j];
                            (tt + b + 1) -> student_exams[1].numbers[j] = (for_sort) -> student_exams[1].numbers[j];                
                        }
                    }
                }
            }
        }
        free(for_sort -> student_exams[0].numbers);
        free(for_sort -> student_exams[1].numbers);
        free(for_sort);
    }    
    if(choice ==  3){
        struct student * for_sort = malloc(sizeof(student_def));
        (for_sort) -> student_exams[0].numbers = malloc(sizeof(int) * SIZE_FOR_ARR);
        (for_sort) -> student_exams[1].numbers = malloc(sizeof(int) * SIZE_FOR_ARR);

        for(int i = 0; i < size; i++){
            for(int b = 0; b < size - 1; b++){
                if((tt + b) -> info_stud.surname[0] > (tt + b + 1) -> info_stud.surname[0]){
                    strcpy((for_sort) -> info_stud.f_name, (tt + b) -> info_stud.f_name);
                    strcpy((for_sort) -> info_stud.s_name, (tt + b) -> info_stud.s_name);
                    strcpy((for_sort) -> info_stud.surname, (tt + b) -> info_stud.surname);
                    (for_sort) -> info_stud.semestr_number = (tt + b) -> info_stud.semestr_number;
                    for(int j = 0; j < SIZE_FOR_ARR; j++){
                        (for_sort) -> student_exams[0].numbers[j] = (tt + b) -> student_exams[0].numbers[j];
                        (for_sort) -> student_exams[1].numbers[j] = (tt + b) -> student_exams[1].numbers[j];                
                    }
                    strcpy((tt + b) -> info_stud.f_name, (tt + b + 1) -> info_stud.f_name);
                    strcpy((tt + b) -> info_stud.s_name, (tt + b + 1) -> info_stud.s_name);
                    strcpy((tt + b) -> info_stud.surname, (tt + b + 1) -> info_stud.surname);
                    (tt + b) -> info_stud.semestr_number = (tt + b + 1) -> info_stud.semestr_number;
                    for(int j = 0; j < SIZE_FOR_ARR; j++){
                        (tt + b) -> student_exams[0].numbers[j] = (tt + b + 1) -> student_exams[0].numbers[j];
                        (tt + b) -> student_exams[1].numbers[j] = (tt + b + 1) -> student_exams[1].numbers[j];                
                    }
                    strcpy((tt + b + 1) -> info_stud.f_name, (for_sort) -> info_stud.f_name);
                    strcpy((tt + b + 1) -> info_stud.s_name, (for_sort) -> info_stud.s_name);
                    strcpy((tt + b + 1) -> info_stud.surname, (for_sort) -> info_stud.surname);
                    (tt + b + 1) -> info_stud.semestr_number = (for_sort) -> info_stud.semestr_number;
                    for(int j = 0; j < SIZE_FOR_ARR; j++){
                        (tt + b + 1) -> student_exams[0].numbers[j] = (for_sort) -> student_exams[0].numbers[j];
                        (tt + b + 1) -> student_exams[1].numbers[j] = (for_sort) -> student_exams[1].numbers[j];                
                    }
                }
                else if((tt + b) -> info_stud.surname[0] == (tt + b + 1) -> info_stud.surname[0]){
                    if((tt + b) -> info_stud.surname[1] > (tt + b + 1) -> info_stud.surname[1]){
                        strcpy((for_sort) -> info_stud.f_name, (tt + b) -> info_stud.f_name);
                        strcpy((for_sort) -> info_stud.s_name, (tt + b) -> info_stud.s_name);
                        strcpy((for_sort) -> info_stud.surname, (tt + b) -> info_stud.surname);
                        (for_sort) -> info_stud.semestr_number = (tt + b) -> info_stud.semestr_number;
                        for(int j = 0; j < SIZE_FOR_ARR; j++){
                            (for_sort) -> student_exams[0].numbers[j] = (tt + b) -> student_exams[0].numbers[j];
                            (for_sort) -> student_exams[1].numbers[j] = (tt + b) -> student_exams[1].numbers[j];                
                        }
                        strcpy((tt + b) -> info_stud.f_name, (tt + b + 1) -> info_stud.f_name);
                        strcpy((tt + b) -> info_stud.s_name, (tt + b + 1) -> info_stud.s_name);
                        strcpy((tt + b) -> info_stud.surname, (tt + b + 1) -> info_stud.surname);
                        (tt + b) -> info_stud.semestr_number = (tt + b + 1) -> info_stud.semestr_number;
                        for(int j = 0; j < SIZE_FOR_ARR; j++){
                            (tt + b) -> student_exams[0].numbers[j] = (tt + b + 1) -> student_exams[0].numbers[j];
                            (tt + b) -> student_exams[1].numbers[j] = (tt + b + 1) -> student_exams[1].numbers[j];                
                        }
                        strcpy((tt + b + 1) -> info_stud.f_name, (for_sort) -> info_stud.f_name);
                        strcpy((tt + b + 1) -> info_stud.s_name, (for_sort) -> info_stud.s_name);
                        strcpy((tt + b + 1) -> info_stud.surname, (for_sort) -> info_stud.surname);
                        (tt + b + 1) -> info_stud.semestr_number = (for_sort) -> info_stud.semestr_number;
                        for(int j = 0; j < SIZE_FOR_ARR; j++){
                            (tt + b + 1) -> student_exams[0].numbers[j] = (for_sort) -> student_exams[0].numbers[j];
                            (tt + b + 1) -> student_exams[1].numbers[j] = (for_sort) -> student_exams[1].numbers[j];                
                        }
                    }
                }
            }
        }
        free(for_sort -> student_exams[0].numbers);
        free(for_sort -> student_exams[1].numbers);
        free(for_sort);
    }
    if(choice == 4){
        struct student * for_sort = malloc(sizeof(student_def));
        (for_sort) -> student_exams[0].numbers = malloc(sizeof(int) * SIZE_FOR_ARR);
        (for_sort) -> student_exams[1].numbers = malloc(sizeof(int) * SIZE_FOR_ARR);

        for(int i = 0; i < size; i++){
            for(int b = 0; b < size - 1; b++){
                if((tt + b) -> info_stud.semestr_number > (tt + b + 1) -> info_stud.semestr_number){
                    strcpy((for_sort) -> info_stud.f_name, (tt + b) -> info_stud.f_name);
                    strcpy((for_sort) -> info_stud.s_name, (tt + b) -> info_stud.s_name);
                    strcpy((for_sort) -> info_stud.surname, (tt + b) -> info_stud.surname);
                    (for_sort) -> info_stud.semestr_number = (tt + b) -> info_stud.semestr_number;
                    for(int j = 0; j < SIZE_FOR_ARR; j++){
                        (for_sort) -> student_exams[0].numbers[j] = (tt + b) -> student_exams[0].numbers[j];
                        (for_sort) -> student_exams[1].numbers[j] = (tt + b) -> student_exams[1].numbers[j];                
                    }
                    strcpy((tt + b) -> info_stud.f_name, (tt + b + 1) -> info_stud.f_name);
                    strcpy((tt + b) -> info_stud.s_name, (tt + b + 1) -> info_stud.s_name);
                    strcpy((tt + b) -> info_stud.surname, (tt + b + 1) -> info_stud.surname);
                    (tt + b) -> info_stud.semestr_number = (tt + b + 1) -> info_stud.semestr_number;
                    for(int j = 0; j < SIZE_FOR_ARR; j++){
                        (tt + b) -> student_exams[0].numbers[j] = (tt + b + 1) -> student_exams[0].numbers[j];
                        (tt + b) -> student_exams[1].numbers[j] = (tt + b + 1) -> student_exams[1].numbers[j];                
                    }
                    strcpy((tt + b + 1) -> info_stud.f_name, (for_sort) -> info_stud.f_name);
                    strcpy((tt + b + 1) -> info_stud.s_name, (for_sort) -> info_stud.s_name);
                    strcpy((tt + b + 1) -> info_stud.surname, (for_sort) -> info_stud.surname);
                    (tt + b + 1) -> info_stud.semestr_number = (for_sort) -> info_stud.semestr_number;
                    for(int j = 0; j < SIZE_FOR_ARR; j++){
                        (tt + b + 1) -> student_exams[0].numbers[j] = (for_sort) -> student_exams[0].numbers[j];
                        (tt + b + 1) -> student_exams[1].numbers[j] = (for_sort) -> student_exams[1].numbers[j];                
                    }
                }
            }
        }
        free(for_sort -> student_exams[0].numbers);
        free(for_sort -> student_exams[1].numbers);
        free(for_sort);
    }
}

void struct_search(struct student * tt, int size){
    system("clear");
    printf(ANSI_COLOR_BLUE "Введите по какому параметру нужно выполнить поиск: \n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE "1 - имя, 2 - фамилия, 3 - отчество, 4 - номер семестра, 5 - оценка\n" ANSI_COLOR_RESET);

    int choice_r = 0;
    int check_on6 = scanf("%d", &(choice_r));
    while(check_on6 == 0 || choice_r < 1 || choice_r > 5){
        printf(ANSI_COLOR_RED "Введен неверный аргумент, повторите попытку!\n" ANSI_COLOR_RESET);
        getchar();
        check_on6 = scanf("%d", &(choice_r));
    }

    struct student * temp = malloc(sizeof(student_def) * size);


    if(choice_r == 1){
        char * name_for_search = malloc(sizeof(char) * SIZE_FOR_STR);
        int temp_perem = 0;
        printf(ANSI_COLOR_BLUE "Введите имя для поиска:\n" ANSI_COLOR_RESET);
        getchar();
        fgets(name_for_search, SIZE_FOR_STR, stdin);
        for(int i = 0; i < size; i++){
            if(strcmp(name_for_search, (tt + i) -> info_stud.f_name) == 0){
                strcpy((temp + temp_perem) -> info_stud.f_name, (tt + i) -> info_stud.f_name);
                strcpy((temp + temp_perem) -> info_stud.surname, (tt + i) -> info_stud.surname);
                strcpy((temp + temp_perem) -> info_stud.s_name, (tt + i) -> info_stud.s_name);
                (temp + temp_perem) -> info_stud.semestr_number = (tt + i) -> info_stud.semestr_number;
                (temp + temp_perem) -> student_exams[0].numbers = malloc(sizeof(int) * SIZE_FOR_ARR);
                (temp + temp_perem) -> student_exams[1].numbers = malloc(sizeof(int) * SIZE_FOR_ARR);
                for(int b = 0; b < SIZE_FOR_ARR; b++){
                    (temp + temp_perem) -> student_exams[0].numbers[b] = (tt + i) -> student_exams[0].numbers[b];
                    (temp + temp_perem) -> student_exams[1].numbers[b] = (tt + i) -> student_exams[1].numbers[b]; 
                }
                temp_perem++;
            }
        }
        show_struct(temp, temp_perem);
        for(int i = 0; i < temp_perem; i++){
            free((temp + i) -> student_exams[0].numbers);
            free((temp + i) -> student_exams[1].numbers);
        }
        free(temp);
    }
    if(choice_r == 2){
        char * name_for_search = malloc(sizeof(char) * SIZE_FOR_STR);
        int temp_perem = 0;
        printf(ANSI_COLOR_BLUE "Введите фамилию для поиска:\n" ANSI_COLOR_RESET);
        getchar();
        fgets(name_for_search, SIZE_FOR_STR, stdin);
        for(int i = 0; i < size; i++){
            if(strcmp(name_for_search, (tt + i) -> info_stud.surname) == 0){
                strcpy((temp + temp_perem) -> info_stud.f_name, (tt + i) -> info_stud.f_name);
                strcpy((temp + temp_perem) -> info_stud.surname, (tt + i) -> info_stud.surname);
                strcpy((temp + temp_perem) -> info_stud.s_name, (tt + i) -> info_stud.s_name);
                (temp + temp_perem) -> info_stud.semestr_number = (tt + i) -> info_stud.semestr_number;
                (temp + temp_perem) -> student_exams[0].numbers = malloc(sizeof(int) * SIZE_FOR_ARR);
                (temp + temp_perem) -> student_exams[1].numbers = malloc(sizeof(int) * SIZE_FOR_ARR);
                for(int b = 0; b < SIZE_FOR_ARR; b++){
                    (temp + temp_perem) -> student_exams[0].numbers[b] = (tt + i) -> student_exams[0].numbers[b];
                    (temp + temp_perem) -> student_exams[1].numbers[b] = (tt + i) -> student_exams[1].numbers[b]; 
                }
                temp_perem++;
            }
        }
        show_struct(temp, temp_perem);
        for(int i = 0; i < temp_perem; i++){
            free((temp + i) -> student_exams[0].numbers);
            free((temp + i) -> student_exams[1].numbers);
        }
        free(temp);
    }
    if(choice_r == 3){
        char * name_for_search = malloc(sizeof(char) * SIZE_FOR_STR);
        int temp_perem = 0;
        printf(ANSI_COLOR_BLUE "Введите отчество для поиска:\n" ANSI_COLOR_RESET);
        getchar();
        fgets(name_for_search, SIZE_FOR_STR, stdin);
        for(int i = 0; i < size; i++){
            if(strcmp(name_for_search, (tt + i) -> info_stud.s_name) == 0){
                strcpy((temp + temp_perem) -> info_stud.f_name, (tt + i) -> info_stud.f_name);
                strcpy((temp + temp_perem) -> info_stud.surname, (tt + i) -> info_stud.surname);
                strcpy((temp + temp_perem) -> info_stud.s_name, (tt + i) -> info_stud.s_name);
                (temp + temp_perem) -> info_stud.semestr_number = (tt + i) -> info_stud.semestr_number;
                (temp + temp_perem) -> student_exams[0].numbers = malloc(sizeof(int) * SIZE_FOR_ARR);
                (temp + temp_perem) -> student_exams[1].numbers = malloc(sizeof(int) * SIZE_FOR_ARR);
                for(int b = 0; b < SIZE_FOR_ARR; b++){
                    (temp + temp_perem) -> student_exams[0].numbers[b] = (tt + i) -> student_exams[0].numbers[b];
                    (temp + temp_perem) -> student_exams[1].numbers[b] = (tt + i) -> student_exams[1].numbers[b]; 
                }
                temp_perem++;
            }
        }
        show_struct(temp, temp_perem);
        for(int i = 0; i < temp_perem; i++){
            free((temp + i) -> student_exams[0].numbers);
            free((temp + i) -> student_exams[1].numbers);
        }
        free(temp);
    }
    if(choice_r == 4){
        int check_sem = 0;
        int temp_perem = 0;
        printf(ANSI_COLOR_BLUE "Введите семестр для поиска:\n" ANSI_COLOR_RESET);
        getchar();
        int check_sem2 = scanf("%d", &(check_sem));
        while(check_sem > 4 || check_sem < 1 || check_sem2 == 0){
            printf(ANSI_COLOR_RED "Введена неверный семестр! Повторите ввод!\n" ANSI_COLOR_RESET);
            getchar();
            check_sem2 = scanf("%d", &(check_sem));
        }
        
        for(int i = 0; i < size; i++){
            if(check_sem == (tt + i) -> info_stud.semestr_number){
                strcpy((temp + temp_perem) -> info_stud.f_name, (tt + i) -> info_stud.f_name);
                strcpy((temp + temp_perem) -> info_stud.surname, (tt + i) -> info_stud.surname);
                strcpy((temp + temp_perem) -> info_stud.s_name, (tt + i) -> info_stud.s_name);
                (temp + temp_perem) -> info_stud.semestr_number = (tt + i) -> info_stud.semestr_number;
                (temp + temp_perem) -> student_exams[0].numbers = malloc(sizeof(int) * SIZE_FOR_ARR);
                (temp + temp_perem) -> student_exams[1].numbers = malloc(sizeof(int) * SIZE_FOR_ARR);
                for(int b = 0; b < SIZE_FOR_ARR; b++){
                    (temp + temp_perem) -> student_exams[0].numbers[b] = (tt + i) -> student_exams[0].numbers[b];
                    (temp + temp_perem) -> student_exams[1].numbers[b] = (tt + i) -> student_exams[1].numbers[b]; 
                }
                temp_perem++;
            }
        }
        show_struct(temp, temp_perem);
        for(int i = 0; i < temp_perem; i++){
            free((temp + i) -> student_exams[0].numbers);
            free((temp + i) -> student_exams[1].numbers);
        }
        free(temp);
    }
    if(choice_r == 5){
        
    }
}

void delete_struct(struct student * tt, int * size, int delete_arg){
    if((delete_arg > (*(size) - 1)) || (delete_arg < 0)){
        system("clear");
        printf(ANSI_COLOR_RED "Введен неверный аргумент для удаления!\n" ANSI_COLOR_RESET);
        return;
    }
    if((delete_arg + 1) == (*size)){
        free((tt + (*size) - 1) -> student_exams[0].numbers);
        free((tt + (*size) - 1) -> student_exams[1].numbers);
        (*size) -= 1;
        tt = realloc(tt, sizeof(student_def) * (*size));
        return;
    }
    for(int i = delete_arg; i < (*size) - 2; i++){
        strcpy((tt + i) -> info_stud.f_name, (tt + i + 1) -> info_stud.f_name);
        strcpy((tt + i) -> info_stud.s_name, (tt + i + 1) -> info_stud.s_name);
        strcpy((tt + i) -> info_stud.surname, (tt + i + 1) -> info_stud.surname);
        (tt + i) -> info_stud.semestr_number = (tt + i + 1) -> info_stud.semestr_number;
        for(int i = 0; i < SIZE_FOR_ARR - 1; i++){
            (tt + i) -> student_exams[0].numbers[i] = (tt + i + 1) -> student_exams[0].numbers[i];
        }
        for(int i = 0; i < SIZE_FOR_ARR - 1; i++){
            (tt + i) -> student_exams[1].numbers[i] = (tt + i + 1) -> student_exams[1].numbers[i];
        }
    }
    free((tt + (*size) - 1) -> student_exams[0].numbers);
    free((tt + (*size) - 1) -> student_exams[1].numbers);
    *(size) -= 1;
    tt = realloc(tt, sizeof(student_def) * (*(size)));
    
}

void edit_parametrs(struct student * tt){
    system("clear");
    printf(ANSI_COLOR_BLUE "Какой параметр желаете отредактироваить:\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLUE "Имя - 1, фамилия - 2, отчество - 3, номер семестра - 4, оценку - 5\n" ANSI_COLOR_RESET);
    int choice_par = 0;
    int check_on1 = scanf("%d", &choice_par);
    while(choice_par < 1 || choice_par > 5 || check_on1 == 0){
        printf(ANSI_COLOR_RED "Введен неверный параметр для редактированя. Повторите ввод.\n" ANSI_COLOR_RESET);
        getchar();
        check_on1 = scanf("%d", &choice_par);
    }
    if(choice_par == 1){
        printf(ANSI_COLOR_BLUE "Введите новое имя:\n" ANSI_COLOR_RESET);
        getchar();
        fgets(tt -> info_stud.f_name, SIZE_FOR_STR, stdin);
    }
    if(choice_par == 2){
        printf(ANSI_COLOR_BLUE "Введите новую фамилию:\n" ANSI_COLOR_RESET);
        getchar();
        fgets(tt -> info_stud.surname, SIZE_FOR_STR, stdin);
    }
    if(choice_par == 3){
        printf(ANSI_COLOR_BLUE "Введите новое отчество:\n" ANSI_COLOR_RESET);
        getchar();
        fgets(tt -> info_stud.s_name, SIZE_FOR_STR, stdin);
    }
    if(choice_par == 5){
        if(tt -> info_stud.semestr_number == 1){
            for(int i = 0; i < SIZE_FOR_ARR; i++){
                printf(ANSI_COLOR_BLUE "Введите оценку для %d." ANSI_COLOR_RESET, (tt) -> student_exams[0].numbers[i]); fputs(f_sem[i], stdout); printf(": ");
                int check_result = scanf("%d", &((tt) -> student_exams[1].numbers[i]));
                while(check_result == 0 || ((tt) -> student_exams[1].numbers[i]) < 1 || ((tt) -> student_exams[1].numbers[i]) > 10){
                    printf(ANSI_COLOR_RED "Введена неверная оценка!\n" ANSI_COLOR_RESET);
                    getchar();
                    check_result = scanf("%d", &((tt) -> student_exams[1].numbers[i]));
                }
            }
        }
        if(tt -> info_stud.semestr_number == 2){
            for(int i = 0; i < SIZE_FOR_ARR; i++){
                printf(ANSI_COLOR_BLUE "Введите оценку для %d." ANSI_COLOR_RESET, (tt) -> student_exams[0].numbers[i]); fputs(s_sem[i], stdout); printf(": ");
                int check_result = scanf("%d", &((tt) -> student_exams[1].numbers[i]));
                while(check_result == 0 || ((tt) -> student_exams[1].numbers[i]) < 1 || ((tt) -> student_exams[1].numbers[i]) > 10){
                    printf(ANSI_COLOR_RED "Введена неверная оценка!\n" ANSI_COLOR_RESET);
                    getchar();
                    check_result = scanf("%d", &((tt) -> student_exams[1].numbers[i]));
                }
            }
        }
        if(tt -> info_stud.semestr_number == 3){
            for(int i = 0; i < SIZE_FOR_ARR; i++){
                printf(ANSI_COLOR_BLUE "Введите оценку для %d." ANSI_COLOR_RESET, (tt) -> student_exams[0].numbers[i]); fputs(t_sem[i], stdout); printf(": ");
                int check_result = scanf("%d", &((tt) -> student_exams[1].numbers[i]));
                while(check_result == 0 || ((tt) -> student_exams[1].numbers[i]) < 1 || ((tt) -> student_exams[1].numbers[i]) > 10){
                    printf(ANSI_COLOR_RED "Введена неверная оценка!\n" ANSI_COLOR_RESET);
                    getchar();
                    check_result = scanf("%d", &((tt) -> student_exams[1].numbers[i]));
                }
            }
        }
        if(tt -> info_stud.semestr_number == 4){
            for(int i = 0; i < SIZE_FOR_ARR; i++){
                printf(ANSI_COLOR_BLUE "Введите оценку для %d." ANSI_COLOR_RESET, (tt) -> student_exams[0].numbers[i]); fputs(c_sem[i], stdout); printf(": ");
                int check_result = scanf("%d", &((tt) -> student_exams[1].numbers[i]));
                while(check_result == 0 || ((tt) -> student_exams[1].numbers[i]) < 1 || ((tt) -> student_exams[1].numbers[i]) > 10){
                    printf(ANSI_COLOR_RED "Введена неверная оценка!\n" ANSI_COLOR_RESET);
                    getchar();
                    check_result = scanf("%d", &((tt) -> student_exams[1].numbers[i]));
                }
            }
        }
    }
    if(choice_par == 4){
        printf(ANSI_COLOR_BLUE "Введите новый номер семестра: \n" ANSI_COLOR_RESET);
        int check_on3 = scanf("%d", &(tt -> info_stud.semestr_number));
        while(check_on3 == 0 || (tt -> info_stud.semestr_number) < 1 || (tt -> info_stud.semestr_number) > 4){
            printf(ANSI_COLOR_RED "Семестр введен неверно! Повторите попытку!\n" ANSI_COLOR_RESET);
            getchar();
            check_on3 = scanf("%d", &(tt -> info_stud.semestr_number));
        }
        if(tt -> info_stud.semestr_number == 1){
            (tt) -> student_exams[0].numbers[0] = MATH;
            (tt) -> student_exams[0].numbers[1] = PHYSICS;
            (tt) -> student_exams[0].numbers[2] = PI;
            (tt) -> student_exams[0].numbers[3] = IKG;
            (tt) -> student_exams[0].numbers[4] = PHILOSOPHY;

            for(int i = 0; i < SIZE_FOR_ARR; i++){
                printf(ANSI_COLOR_BLUE "Введите оценку для %d." ANSI_COLOR_RESET, (tt) -> student_exams[0].numbers[i]); fputs(f_sem[i], stdout); printf(": ");
                int check_result = scanf("%d", &((tt) -> student_exams[1].numbers[i]));
                while(check_result == 0 || ((tt) -> student_exams[1].numbers[i]) < 1 || ((tt) -> student_exams[1].numbers[i]) > 10){
                    printf(ANSI_COLOR_RED "Введена неверная оценка!\n" ANSI_COLOR_RESET);
                    getchar();
                    check_result = scanf("%d", &((tt) -> student_exams[1].numbers[i]));
                }
            }
        }
        if(tt -> info_stud.semestr_number == 2){
            (tt) -> student_exams[0].numbers[0] = LOGIC;
            (tt) -> student_exams[0].numbers[1] = POLITOLOGY;
            (tt) -> student_exams[0].numbers[2] = ENGLISH;
            (tt) -> student_exams[0].numbers[3] = AILOVT;
            (tt) -> student_exams[0].numbers[4] = HISTORY;

            for(int i = 0; i < SIZE_FOR_ARR; i++){
                printf(ANSI_COLOR_BLUE "Введите оценку для %d." ANSI_COLOR_RESET, (tt) -> student_exams[0].numbers[i]); fputs(s_sem[i], stdout); printf(": ");
                int check_result = scanf("%d", &((tt) -> student_exams[1].numbers[i]));
                while(check_result == 0 || ((tt) -> student_exams[1].numbers[i]) < 1 || ((tt) -> student_exams[1].numbers[i]) > 10){
                    printf(ANSI_COLOR_RED "Введена неверная оценка!\n" ANSI_COLOR_RESET);
                    getchar();
                    check_result = scanf("%d", &((tt) -> student_exams[1].numbers[i]));
                }
            }
        }
        if(tt -> info_stud.semestr_number == 3){
            (tt) -> student_exams[0].numbers[0] = NETWORKS;
            (tt) -> student_exams[0].numbers[1] = SYS_PROGRAMMING;
            (tt) -> student_exams[0].numbers[2] = KPIYAP;
            (tt) -> student_exams[0].numbers[3] = RUSSIAN;
            (tt) -> student_exams[0].numbers[4] = BELARRUSIAN;

            for(int i = 0; i < SIZE_FOR_ARR; i++){
                printf(ANSI_COLOR_BLUE "Введите оценку для %d." ANSI_COLOR_RESET, (tt) -> student_exams[0].numbers[i]); fputs(t_sem[i], stdout); printf(": ");
                int check_result = scanf("%d", &((tt) -> student_exams[1].numbers[i]));
                while(check_result == 0 || ((tt) -> student_exams[1].numbers[i]) < 1 || ((tt) -> student_exams[1].numbers[i]) > 10){
                    printf(ANSI_COLOR_RED "Введена неверная оценка!\n" ANSI_COLOR_RESET);
                    getchar();
                    check_result = scanf("%d", &((tt) -> student_exams[1].numbers[i]));
                }
            }
        }
        if(tt -> info_stud.semestr_number == 4){
            (tt) -> student_exams[0].numbers[0] = ALGHORITMS;
            (tt) -> student_exams[0].numbers[1] = DATA_STRUCTURS;
            (tt) -> student_exams[0].numbers[2] = CRIPTOGRAPHY;
            (tt) -> student_exams[0].numbers[3] = OOP;
            (tt) -> student_exams[0].numbers[4] = KPP;

            for(int i = 0; i < SIZE_FOR_ARR; i++){
                printf(ANSI_COLOR_BLUE "Введите оценку для %d." ANSI_COLOR_RESET, (tt) -> student_exams[0].numbers[i]); fputs(c_sem[i], stdout); printf(": ");
                int check_result = scanf("%d", &((tt) -> student_exams[1].numbers[i]));
                while(check_result == 0 || ((tt) -> student_exams[1].numbers[i]) < 1 || ((tt) -> student_exams[1].numbers[i]) > 10){
                    printf(ANSI_COLOR_RED "Введена неверная оценка!\n" ANSI_COLOR_RESET);
                    getchar();
                    check_result = scanf("%d", &((tt) -> student_exams[1].numbers[i]));
                }
            }
        }
    }
}

void show_struct(struct student * students, int size){
    system("clear");
    printf(ANSI_COLOR_RED "№\tФИО:\t\t\t\t\t\tНомер семестра:\n" ANSI_COLOR_RESET);
    for(int i = 0; i < size; i++){
        printf(ANSI_COLOR_RED "%d" ANSI_COLOR_RESET, i + 1); put_space(8 - amount_of_digits(i + 1));
        print((students + i) -> info_stud.f_name); printf(" "); 
        print((students + i) -> info_stud.surname); printf(" "); 
        print((students + i) -> info_stud.s_name); put_space(46 - text_size((students + i) -> info_stud.f_name) - text_size((students + i) -> info_stud.s_name) - text_size((students + i) -> info_stud.surname));
        printf("%d\n", (students + i) -> info_stud.semestr_number);
        printf(ANSI_COLOR_RED "Предмет:\t\tОценка\n" ANSI_COLOR_RESET);
        if((students + i) -> info_stud.semestr_number == 1){
            fputs(f_sem[0], stdout); put_space(23 - text_size(f_sem[0])); printf("%d\n", (students + i) -> student_exams[1].numbers[0]);
            fputs(f_sem[1], stdout); put_space(23 - text_size(f_sem[1])); printf("%d\n", (students + i) -> student_exams[1].numbers[1]);
            fputs(f_sem[2], stdout); put_space(23 - text_size(f_sem[2])); printf("%d\n", (students + i) -> student_exams[1].numbers[2]);
            fputs(f_sem[3], stdout); put_space(23 - text_size(f_sem[3])); printf("%d\n", (students + i) -> student_exams[1].numbers[3]);
            fputs(f_sem[4], stdout); put_space(23 - text_size(f_sem[4])); printf("%d\n", (students + i) -> student_exams[1].numbers[4]);

        }
        if((students + i) -> info_stud.semestr_number == 2){
            fputs(s_sem[0], stdout); put_space(23 - text_size(s_sem[0])); printf("%d\n", (students + i) -> student_exams[1].numbers[0]);
            fputs(s_sem[1], stdout); put_space(23 - text_size(s_sem[1])); printf("%d\n", (students + i) -> student_exams[1].numbers[1]);
            fputs(s_sem[2], stdout); put_space(23 - text_size(s_sem[2])); printf("%d\n", (students + i) -> student_exams[1].numbers[2]);
            fputs(s_sem[3], stdout); put_space(23 - text_size(s_sem[3])); printf("%d\n", (students + i) -> student_exams[1].numbers[3]);
            fputs(s_sem[4], stdout); put_space(23 - text_size(s_sem[4])); printf("%d\n", (students + i) -> student_exams[1].numbers[4]);
        }
        if((students + i) -> info_stud.semestr_number == 3){
            fputs(t_sem[0], stdout); put_space(23 - text_size(t_sem[0])); printf("%d\n", (students + i) -> student_exams[1].numbers[0]);
            fputs(t_sem[1], stdout); put_space(23 - text_size(t_sem[1])); printf("%d\n", (students + i) -> student_exams[1].numbers[1]);
            fputs(t_sem[2], stdout); put_space(23 - text_size(t_sem[2])); printf("%d\n", (students + i) -> student_exams[1].numbers[2]);
            fputs(t_sem[3], stdout); put_space(23 - text_size(t_sem[3])); printf("%d\n", (students + i) -> student_exams[1].numbers[3]);
            fputs(t_sem[4], stdout); put_space(23 - text_size(t_sem[4])); printf("%d\n", (students + i) -> student_exams[1].numbers[4]);
        }
        if((students + i) -> info_stud.semestr_number == 4){
            fputs(c_sem[0], stdout); put_space(23 - text_size(c_sem[0])); printf("%d\n", (students + i) -> student_exams[1].numbers[0]);
            fputs(c_sem[1], stdout); put_space(23 - text_size(c_sem[1])); printf("%d\n", (students + i) -> student_exams[1].numbers[1]);
            fputs(c_sem[2], stdout); put_space(23 - text_size(c_sem[2])); printf("%d\n", (students + i) -> student_exams[1].numbers[2]);
            fputs(c_sem[3], stdout); put_space(23 - text_size(c_sem[3])); printf("%d\n", (students + i) -> student_exams[1].numbers[3]);
            fputs(c_sem[4], stdout); put_space(23 - text_size(c_sem[4])); printf("%d\n", (students + i) -> student_exams[1].numbers[4]);
        }
    }
}

void put_space(int value){
    for(int i = 0; i < value; i++){
        putchar(' ');
    }
}

int text_size(char * text){
    int i = 0;
    while(text[i] != '\0'){
        i++;
    }
    return i - 1;
}

void print(char * text){
    int index = 0;
    while(text[index] != '\n'){
        putchar(text[index]);
        index++;
    }
    return;
}

int amount_of_digits(int number){
    int k = 0;
    while(number != 0){
        number /= 10;
        k++;
    }
    return k; 
}

int msReverse(int * ms, int size){
    for(int i = 0; i < size / 2; i++){
        int temp = ms[i];
        ms[i] = ms[size - 1 - i];
        ms[size - 1 - i] = temp;
    }
}

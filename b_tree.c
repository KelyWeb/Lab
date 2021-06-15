#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_RESET    "\x1b[0m"


typedef struct tree{
    struct tree * left;
    struct tree * right;
    char symbol;
} tree_default;


void showTree(struct tree * tree_root);
struct tree * addSymbolToTree(char symb, struct tree * tree_root);
bool searchSymbolInTree(char symb, struct tree * tree_root);
struct tree * rootTreeInit();
void print_tree(struct tree * tree_root);
bool isTwo(struct tree * root_tree);

static int value = 0;

int main(int argc, char ** argv){
    struct tree * mainTree = NULL;
    char symbols[100][1];
    int k = 0;

    while(true){
        printf(ANSI_COLOR_GREEN "Добавить символ в бинарное дерево: 2\n");
        printf("Просмотреть бинарное дерево: 3\n");
        printf("Поиск сивола в бинарном дереве: 4\n");
        printf("Проверка на совпадение символов: 5\n" ANSI_COLOR_RESET);

        int choice = 0;
        int check_on_choice = scanf("%d", &choice);
        while(check_on_choice != 1){
            printf(ANSI_COLOR_RED "Введен неверный параметр, повторите ввод!\n" ANSI_COLOR_RESET);
            getchar();
            check_on_choice = scanf("%d", &choice);
        } //Проверка на валидный ввод...



        if(choice == 1){
            if(mainTree != NULL){
                printf(ANSI_COLOR_RED "Дерево уже создано!\n" ANSI_COLOR_RESET);
            }
            if(mainTree == NULL){
                mainTree = malloc(sizeof(struct tree));
                mainTree -> left = NULL;
                mainTree -> right = NULL;
                system("clear");
                printf(ANSI_COLOR_BLUE "Введите символ: \n" ANSI_COLOR_RESET);
                getchar();
                char symb = getchar();
                mainTree -> symbol = symb;
            }
        }
        if(choice == 2){
            system("clear");
            printf(ANSI_COLOR_BLUE "Введите символ для добавления в дерево: \n" ANSI_COLOR_RESET);
            getchar();
            char symbol = getchar();
            symbols[k][0] = symbol;
            k++;
            mainTree = addSymbolToTree(symbol, mainTree);
        }
        if(choice == 3) print_tree(mainTree);
        if(choice == 4){
            system("clear");
            printf(ANSI_COLOR_BLUE "Введите символ для поиска: \n" ANSI_COLOR_RESET);
            getchar();
            char symbol = getchar();
            bool isEnter = searchSymbolInTree(symbol, mainTree);
            if(isEnter == true) printf(ANSI_COLOR_GREEN "Есть!\n" ANSI_COLOR_RESET);
            else printf(ANSI_COLOR_GREEN "Нету!\n" ANSI_COLOR_RESET);
        }
        if(choice == 5){
            bool isInTree = false;
            for(int i = 0; i < k; i++){
                for(int b = 0; b < k; b++){
                    if(i == b){
                        continue;
                    }
                    if(symbols[i][0] == symbols[b][0]){
                        isInTree = true;
                    }
                }
            }
            if(isInTree == true) printf(ANSI_COLOR_GREEN "В дереве есть совпадающие элемменты.\n" ANSI_COLOR_RESET);
            if(isInTree == false) printf(ANSI_COLOR_GREEN "В дереве нет совпадающих элемменты.\n" ANSI_COLOR_RESET);
        }

    }
}


struct tree * addSymbolToTree(char symb, struct tree * tree_root){
    if(tree_root == NULL){
        tree_root = malloc(sizeof(struct tree));
        tree_root -> right = NULL;
        tree_root -> left = NULL;
        tree_root -> symbol = symb;
    }
    else{
        if(symb >= (tree_root -> symbol)){
            tree_root->right = addSymbolToTree(symb, tree_root -> right);
        }
        else if(symb < (tree_root -> symbol)){
            tree_root->left = addSymbolToTree(symb, tree_root -> left);
        }
    }
    return tree_root;
}

bool searchSymbolInTree(char symb, struct tree * tree_root){
    if(tree_root == NULL) return false;
    else{
        if(tree_root -> symbol == symb) return true;
        else{
            if(symb >= tree_root -> symbol) searchSymbolInTree(symb, tree_root -> right);
            else if(symb < tree_root -> symbol) searchSymbolInTree(symb, tree_root -> left);
        }
    }
}

void print_tree(struct tree * tree_root){
    if(tree_root == NULL) return;
    value += 5;
    print_tree(tree_root -> left);
    for(int i = 0; i < value; i++){
        printf(" ");
    }
    printf("%c\n", tree_root -> symbol);

    print_tree(tree_root -> right);
    value -= 5;
    return;
}

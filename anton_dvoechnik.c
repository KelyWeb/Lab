#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct tree * addSymbolToTree(int value, struct tree * tree_root);
void print_tree(struct tree * tree_root);
bool searchSymbolInTree(int value, struct tree * tree_root);
void sqrt_tree(struct tree * tree_root);

typedef struct tree{
    struct tree * left;
    struct tree * right;
    int number;
} tree_default;

static int value = 0;

int main(int argc, char ** argv){
    struct tree * mainTree = NULL;

    while(true){
        printf("Добавить число в бинарное дерево: 1\n");
        printf("Просмотреть бинарное дерево: 2\n");
        printf("Поиск числа в бинарном дереве: 3\n");
        printf("Возведение элементов дерева в квадрат: 4\n");

        int choice = 0;
        int check_on_choice = scanf("%d", &choice);
        while(check_on_choice != 1){
            printf("Введен неверный параметр, повторите ввод!\n");
            getchar();
            check_on_choice = scanf("%d", &choice);
        } //Проверка на валидный ввод...


        if(choice == 1){
            system("clear");
            printf("Введите число для добавления в дерево: \n");
            int number = 0;
            scanf("%d", &number);
            mainTree = addSymbolToTree(number, mainTree);
        }
        if(choice == 2) print_tree(mainTree);
        if(choice == 3){
            system("clear");
            printf("Введите число для поиска в дереве: \n");
            int digit = 0;
            scanf("%d", &digit);
            bool isEnter = searchSymbolInTree(digit, mainTree);
            if(isEnter == true) printf("Есть!\n");
            else printf("Нету!\n");
        }
        if(choice == 4) sqrt_tree(mainTree);
    }

}

struct tree * addSymbolToTree(int value, struct tree * tree_root){
    if(tree_root == NULL){
        tree_root = malloc(sizeof(struct tree));
        tree_root -> right = NULL;
        tree_root -> left = NULL;
        tree_root -> number = value;
    }
    else{
        if(value >= (tree_root -> number)){
            tree_root -> right = addSymbolToTree(value, tree_root -> right);
        }
        else if(value < (tree_root -> number)){
            tree_root -> left = addSymbolToTree(value, tree_root -> left);
        }
    }
    return tree_root;
}

void print_tree(struct tree * tree_root){
    if(tree_root == NULL) return;
    value += 5;
    print_tree(tree_root -> left);
    for(int i = 0; i < value; i++){
        printf(" ");
    }
    printf("%d\n", tree_root -> number);

    print_tree(tree_root -> right);
    value -= 5;
    return;
}

bool searchSymbolInTree(int value, struct tree * tree_root){
    if(tree_root == NULL) return false;
    else{
        if(tree_root -> number == value) return true;
        else{
            if(value >= tree_root -> number) searchSymbolInTree(value, tree_root -> right);
            else if(value < tree_root -> number) searchSymbolInTree(value, tree_root -> left);
        }
    }
}

void sqrt_tree(struct tree * tree_root){
    if(tree_root == NULL) return;
    else{
        tree_root -> number = tree_root -> number * tree_root -> number;
        sqrt_tree(tree_root -> left);
        sqrt_tree(tree_root -> right);
    }
}


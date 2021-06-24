#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct tree{
    struct tree * left;
    struct tree * right;
    char symbol;
} tree_default;

void print_tree(struct tree * tree_root);
bool searchSymbolInTree(char symb, struct tree * tree_root);
struct tree * addSymbolToTree(char symb, struct tree * tree_root);
void creat_string_tree(struct tree * root_tree, char * string);

static int value = 0;
static int position = 0;

int main(void){
    struct tree * mainTree = NULL;
    char str_mas[500];


    while(true){
        printf("Добавить символ в бинарное дерево: 1\n");
        printf("Просмотреть бинарное дерево: 2\n");
        printf("Поиск сивола в бинарном дереве: 3\n");
        printf("Создать строку из символов в дереве: 4\n");

        int choice = 0;
        int check_on_choice = scanf("%d", &choice);
        while(check_on_choice != 1){
            printf("Введен неверный параметр, повторите ввод!\n");
            getchar();
            check_on_choice = scanf("%d", &choice);
        }

        if(choice == 1){
            system("clear");
            printf("Введите символ для добавления в дерево: \n");
            getchar();
            char symbol = getchar();
            mainTree = addSymbolToTree(symbol, mainTree);
        }
        if(choice == 2)print_tree(mainTree);
        if(choice == 3){
            system("clear");
            printf("Введите символ для поиска: \n");
            getchar();
            char symbol = getchar();
            bool isEnter = searchSymbolInTree(symbol, mainTree);
            if(isEnter == true) printf("Есть!\n");
            else printf("Нету!\n");
        }
        if(choice == 4){
            creat_string_tree(mainTree, str_mas);
            printf("Строка из символов дерева:\n");
            fputs(str_mas, stdout);
            printf("\n");
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

void creat_string_tree(struct tree * root_tree, char * string){
    if(root_tree == NULL) return;
    else{
        string[position] = root_tree -> symbol;
        position++;
        creat_string_tree(root_tree -> left, string);
        creat_string_tree(root_tree -> right, string);
    }
}

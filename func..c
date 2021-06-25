void serch_in_info(struct info * INFO, char SYMBOL){
    struct info * temp = INFO;
    while(INFO != NULL){
        if(INFO -> symbol == SYMBOL){
            printf("В очереди есть данный элеемнт.\n");
            INFO = temp;
            break;
        }
        else{
            INFO = INFO -> INFO -> next;
        }
    }
}

void add_to_info(struct info * INFO, char add_element){
    struct info * temp = INFO;
    while(IFNO != NULL){
        INFO = INFO -> next;
    }
    INFO = malloc(sizeof(struct info));
    INFO -> next = NULL;
    INFO -> symbol = add_element;
}

void delete_from_info(struct info * INFO){
    if(IFNO == NULL) return;
    if(INFO -> next == NULL){
        free(INFO);
    }
    else{
        INFO = INFO -> next;
    }
}

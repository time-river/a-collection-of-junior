#include "condition.h"

void assign_condition(struct query_t *query, struct condition_expr_t *condition){
    query->condition = condition;
    return;
}

enum logic_t logic_atoi(char *logic){
    char *str = NULL;
    enum logic_t value;

    str = strdup(logic);
    for(int i = 0; str[i] != '\0'; i++) // convert all to tolower
        str[i] = tolower(str[i]);
    if(strcmp(logic, "g") == 0)
        value = G;
    else if(strcmp(logic, "ge") == 0)
        value = GE;
    else if(strcmp(logic, "is") == 0)
        value = IS;
    else if(strcmp(logic, "l") == 0)
        value = L;
    else if(strcmp(logic, "le") == 0)
        value = LE;
    else if(strcmp(logic, "ne") == 0)
        value = NE;
    else if(strcmp(logic, "and") == 0)
        value = AND;
    else if(strcmp(logic, "or") == 0)
        value = OR;
    else if(strcmp(logic, "not") == 0)
        value = NOT;
    free(str);
    return value;
}

struct condition_expr_leaf_t *create_condition_expr_leaf(char *column,
        char *logic, void *value_ptr, enum datatype_t datatype){
    struct condition_expr_leaf_t *node = NULL;

    node = (struct condition_expr_leaf_t *)malloc(sizeof(struct condition_expr_leaf_t));
    if(node == NULL){
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
    }
    else{
        node->column = strdup(column);
        node->logic = logic_atoi(logic);
        node->datatype = datatype;
        assign_value(&(node->value), value_ptr, datatype);
    }
    return node;
}

void free_condition_expr_leaf(struct condition_expr_leaf_t *node){
    if(node != NULL){
        if(node->column != NULL)
            free(node->column);
        if(node->datatype == STRING && node->value.string != NULL)
            free(node->value.string);
        free(node);
    }
}

struct condition_expr_t *create_condition_expr(void *condition, enum condition_type_t type, int nextinstr){
    struct condition_expr_t *node = NULL;

    node = (struct condition_expr_t *)malloc(sizeof(struct condition_expr_t));
    if(node != NULL){
        switch(type){
            case CONDITION: // assign_condition(query, node)
                memcpy(node, condition, sizeof(struct condition_expr_t));
                /* 这段代码哪里有问题?
                node->prev = ((struct condition_expr_t *)condition)->prev;
                node->prev = ((struct condition_expr_t *)condition)->next;
                node->begin = ((struct condition_expr_t *)condition)->begin;
                node->end = ((struct condition_expr_t *)condition)->end;
                node->truelist = ((struct condition_expr_t *)condition)->truelist;
                node->truelist = ((struct condition_expr_t *)condition)->falselist;
                node->trueinstr = ((struct condition_expr_t *)condition)->trueinstr;
                node->falseinstr = ((struct condition_expr_t *)condition)->falseinstr;
                node->leaf = NULL;*/
                break;
            case CONDITION_LEAF: // create a new node
                node->prev = node->next = node;
                node->begin = node->end = node;
                node->truelist = node->falselist = NULL;
                node->trueinstr = nextinstr; // 偶数
                node->falseinstr = nextinstr + 1; // 奇数
                node->leaf = (struct condition_expr_leaf_t *)condition;
                break;
        }
    }
    else
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
    return node;
}

void free_condition_expr(struct condition_expr_t *node){
    if(node != NULL){
        if(node->leaf != NULL)
            free_condition_expr_leaf(node->leaf);
        free(node);
    }
    return;
}

void free_list(struct list_t *node){
    struct list_t *list;

    while(node != NULL){
        list = node;
        node = list->next;
        free(list);
    }
    return;
}

void free_condition_expr_list(struct condition_expr_t *node){
    struct list_t *list = NULL;
    struct condition_expr_t *expr = NULL, *tmp = NULL;

    if(node != NULL){
        if(node->truelist != NULL)
            free_list(node->truelist);
        if(node->falselist != NULL)
            free_list(node->falselist);
        for(expr=node->begin; expr != NULL && expr!=node->end;){
            tmp = expr;
            expr = expr->next;
            free(tmp);
        }
        free(node);
    }
    return;
}

void leaf_merge(struct condition_expr_t *B1, int flag_1, struct condition_expr_t *B2, int flag_2){
// circular queue, 保证 .begin == 最左边
    if(flag_1 == 1 && flag_2 == 1){ // 两个都是新节点
        // bool || bool or bool && bool
        /* question code
        insque(B1, B1);
        insque(B2, B1);
        B2->begin = B1->begin = B1;
        B2->end = B1->end = B2;
        */
        B2->begin = B1->begin = B1;
        B2->end = B1->end = B2;
        B1->next = B2;
        B2->next = B1;
        B1->prev = B2;
        B2->prev = B1;
    }
    else if(flag_1 == 1 && flag_2 == 0){
        // bool || expr or bool && expr
        /* question code
        insque(B1, B2); 
        B1->begin = B2->begin;
        B1->end = B2->end = B1;
        */
        B1->prev = B2->end;
        B1->next = B2->begin;
        B2->end->next = B1;
        B2->begin->prev = B1;
        B1->begin = B2->begin = B1;
        B1->end = B2->end;
    }
    else if(flag_1 == 0 && flag_2 == 1){
        // expr || bool or expr && bool
        /* question code
        B1->prev = B2->end;
        insque(B2, B1);
        B2->begin = B1->begin;
        B2->end = B2->end = B2;
        */
        B2->prev = B1->end;
        B2->next = B1->begin;
        B1->end->next = B2;
        B1->begin->prev = B2;
        B2->begin = B1->begin;
        B1->end = B2->end = B2;
    }
    else{ /* (flag_1 = 0 && flag_2 == 0) */

    }

    return;
}

void backpatch(struct list_t **prev, int instr){
    struct list_t *node = NULL, *list = *prev;

    node = mklist(instr);
    if(*prev != NULL){
        while(list->next != NULL)
            list = list->next;
        list->next = node;
    }
    else
        *prev = node;
    return;
}

struct list_t *merge(struct list_t *B1, int flag_1, struct list_t *B2, int flag_2){
    struct list_t *node_1 = NULL, *node_2 = NULL;
    struct list_t *node = NULL;

    if(flag_1 == 1){ // new node
        node_1 = (struct list_t *)malloc(sizeof(struct list_t));
        if(node_1 == NULL)
            fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        else{
            node_1->next = NULL; // B1->instr = NULL
            node_1->instr = B1->instr;
        }
    }
    else
        node_1 = B1;
    if(flag_2 == 1){ // new node
        node_2 = (struct list_t *)malloc(sizeof(struct list_t));
        if(node_2 == NULL)
            fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        else{
            node_2->next = NULL; // B2->instr = NULL
            node_2->instr = B2->instr;
        }
    }
    else
        node_2 = B2;

    node = node_1;
    while(node_1->next != NULL)
        node_1 = node_1->next;
    node_1->next = node_2;

    return node;
}

struct list_t *mklist(int nextinstr){
    struct list_t *node = NULL;

    node = (struct list_t *)malloc(sizeof(struct list_t));
    if(node == NULL)
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
    else{
        node->next = NULL;
        node->instr = nextinstr;
    }
    return node;
}

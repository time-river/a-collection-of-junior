#include "common.h"
#include "condition.h"

void backpatch(struct condition_expr_t *prev, int instr){
    struct list_t *node = NULL;

    if(prev != NULL){
        node = (struct list_t *)malloc(sizeof(struct list_t));
        if(node == NULL)
            fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        else{
            node->prev = NULL;
            node->next = NULL;
            node->instr = instr;
            insque(node, prev); // insque(next, prev)
        }
    }
    return;
}

struct condition_expr_t merge(struct condition_expr_t *B1, struct condition_expr_t *B2, enum listtype_t type){
    struct condition_expr_t B = {
        .prev = NULL,
        .next = NULL,
        .truelist = NULL,
        .falselist = NULL
    };

    if(B1 == NULL || B2 == NULL){
        switch(type){
            case TRUELIST:
                break;
            case FALSELIST:
                break;
        }
    }
    return;
}

#ifndef CONDITION_H
#define CONDITION_H

enum listtype_t {
    TRUELIST,
    FALSELIST
};

void backpatch(struct condition_expr_t *prev, int instr);
struct list_t merge(struct list_t B1, struct list_t B2);

#endif

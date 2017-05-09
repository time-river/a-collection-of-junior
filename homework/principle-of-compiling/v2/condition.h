#ifndef CONDITION_H
#define CONDITION_H

#include "common.h"

enum logic_t{
    G,
    GE,
    IS,
    L,
    LE,
    NE,
    AND,
    OR,
    NOT
};

struct condition_expr_leaf_t {
    char *column;
    enum logic_t logic;
    enum datatype_t datatype;
    union _value_t value;
};

struct condition_expr_t {
    /* begin */
    // 标记 condition_expr list
    struct condition_expr_t *prev;
    struct condition_expr_t *next;
    struct condition_expr_t *begin;
    struct condition_expr_t *end;
    /* end */
    struct list_t *truelist;
    struct list_t *falselist;
    int trueinstr; // 《编译原理》P264 布尔表达式的回填
    int falseinstr;
    struct condition_expr_leaf_t *leaf;
};

struct list_t {
    struct list_t *next;
    int instr;
};

enum condition_type_t {
    CONDITION,
    CONDITION_LEAF
};

void assign_condition(struct query_t *query, struct condition_expr_t *condition);

enum logic_t logic_atoi(char *logic);
struct condition_expr_leaf_t *create_condition_expr_leaf(char *column, char *logic, void *value_ptr, enum datatype_t datatype);
void free_condition_expr_leaf(struct condition_expr_leaf_t *node);
struct condition_expr_t *create_condition_expr(void *condition, enum condition_type_t type, int nextinstr);
void free_condition_expr(struct condition_expr_t *node);
void free_condition_expr_list(struct condition_expr_t *node);

void leaf_merge(struct condition_expr_t *B1, int flag_1, struct condition_expr_t *B2, int flag_2);

void backpatch(struct list_t **prev, int instr);
struct list_t *merge(struct list_t *B1, int flag_1, struct list_t *B2, int flag_2);
struct list_t *mklist(int nextinstr);
void free_list(struct list_t *node);

#endif

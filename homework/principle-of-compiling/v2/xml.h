#ifndef XML_H
#define XML_H

#include <math.h>
#include <mxml.h>
#include "common.h"

void create_xml(const struct query_t *query, FILE *fp);
void insert_xml(const struct query_t *query, FILE *fp);
void xml_insert_item(mxml_node_t *row, char *column, struct value_t *value_node);
void xml_assign_data(mxml_node_t *data, union _value_t value, enum datatype_t datatype);
void xml_datatype_not_match(const char *name, struct value_t *node);
struct column_type_t *xml_match_check(mxml_node_t *meters,
        struct column_t *columns, struct value_t *values);
struct column_type_t *xml_get_column_type(mxml_node_t *meters);
char *datatype_to_char(enum datatype_t datatype);

void select_xml(const struct query_t *query, FILE *fp);
void xml_row_output(mxml_node_t *node);

void update_xml(const struct query_t *query, FILE *fp);
void delete_xml(const struct query_t *query, FILE *fp);
int  update_row(mxml_node_t *row, struct assign_expr_t *assign_expr, struct column_type_t *column_type);

#include "condition.h"

int condition_test(struct condition_expr_t *condition, mxml_node_t *row, struct column_type_t *column_type);
int expr_leaf_test(struct condition_expr_leaf_t *leaf, mxml_node_t *row, struct column_type_t *column_type);
int instr_in_list(struct list_t *list, int instr);

#endif

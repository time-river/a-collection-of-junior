#ifndef XML_H
#define XML_H

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

#endif

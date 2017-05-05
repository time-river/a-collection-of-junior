#ifndef XML_H
#define XML_H

#include <mxml.h>
#include "common.h"

void create_xml(const struct query_t *query, FILE *fp);
void insert_xml(const struct query_t *query, FILE *fp);
void xml_insert_item(mxml_node_t *row, char *column, struct value_t *value_node);
void xml_assign_data(mxml_node_t *data, union _value_t value, enum datatype_t datatype);
mxml_node_t *xml_match_check(const mxml_node_t *meters,
        const struct column_t *columns, const struct value_t *values);
#endif

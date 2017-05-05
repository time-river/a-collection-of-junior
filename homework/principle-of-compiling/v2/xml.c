#include "xml.h"

void create_xml(const struct query_t *query, FILE *fp){
    mxml_node_t *xml = NULL;
    mxml_node_t *table = NULL;
    mxml_node_t *row = NULL;
    mxml_node_t *meter = NULL;
    struct column_type_t *node = query->column_type;

    xml = mxmlNewXML("1.0");

    table = mxmlNewElement(xml, "table");
    row = mxmlNewElement(table, "row");

    node = node->prev; // make node became first node
            // circular queue, the value whether is NULL  has already been checked
    // meters: <column_name>datatype</column_name>
    // data:   <column_name>value</column_name>
    do {
        meter = mxmlNewElement(row, node->column);
        mxmlNewInteger(meter, node->datatype);
        node = node->prev;
    } while(node != NULL && node != query->column_type->prev);

    if(mxmlSaveFile(xml, fp, MXML_NO_CALLBACK) == -1)
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
    else
        fprintf(stdout, "Query OK, 0 rows affected\n");

    mxmlDelete(xml);
    return;
}

void insert_xml(const struct query_t *query, FILE *fp){
    mxml_node_t *xml = NULL;
    mxml_node_t *table = NULL;
    mxml_node_t *meters = NULL;
    mxml_node_t *row = NULL;
    mxml_node_t *node = NULL;
    struct column_t *column_node = query->column;
    struct value_t  *value_node  = query->value;
    int iresult = 0;
    char *column = NULL;
    enum datatype_t datatype;

    xml = mxmlLoadFile(NULL, fp, MXML_TEXT_CALLBACK);
    table = mxmlGetNextSibling(xml);
    meters = mxmlGetNextSibling(table);

    if((row = xml_match_check(meters, column_node, value_node)) == NULL){
        fprintf(stderr, "Column count doesn't match value count\n");
    }
    else{
        /* 1. 遍历
         *  2. 类型检查
         */
        value_node = value_node->prev;
        if(column_node == NULL){
            node = mxmlGetFirstChild(row);
            do {
                if(mxmlGetInteger(node) != value_node->datatype){
                    fprintf(stderr, "ERROR: value type is not matched\n");
                    iresult = 1;
                    break;
                }
                node = mxmlWalkNext(node, row, MXML_DESCEND);
                value_node = value_node->prev;
            } while(node != NULL
                    && value_node != NULL
                    && value_node != query->column_type->prev);
        }
        else{
            node = mxmlGetFirstChild(row);
            column_node = column_node->prev;
            do {
                node = mxmlFindPath(row, column_node->column);
                if(node == NULL){
                    fprintf(stderr, "ERROR: column does not exist\n");
                    iresult = 1;
                    break;
                }
                if(mxmlGetInteger(node) != value_node->datatype){
                    fprintf(stderr, "ERROR: value type is not matched\n");
                    iresult = 1;
                    break;
                }
                column_node = column_node->prev;
                value_node = value_node->prev;
            } while(node != NULL);
        }
    }

    if(iresult == 0){
        mxmlAdd(table, MXML_ADD_AFTER, MXML_ADD_TO_PARENT, row);

        fseek(fp, 0, SEEK_SET);
        if(mxmlSaveFile(xml, fp, MXML_NO_CALLBACK) == -1)
            fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        else
            fprintf(stdout, "Query OK, 0 rows affected\n");
    }
    else
        mxmlDelete(row);

    mxmlDelete(xml);
    return;
}

void xml_insert_item(mxml_node_t *row, char *column, struct value_t *value_node){
    mxml_node_t *data = NULL;

    data = mxmlNewElement(row, column);
    xml_assign_data(data, value_node->value, value_node->datatype);
    return; 
}

void xml_assign_data(mxml_node_t *data, union _value_t value, enum datatype_t datatype){
    switch(datatype){
        case FLOAT:
            mxmlNewReal(data, value.numf);
            break;
        case INT:
            mxmlNewInteger(data, value.numi);
            break;
        case STRING:
            mxmlNewText(data, 0, value.string);
            break;
    }
    return;
}

/* the number:
 *   columns == values
 *  or
 *   values == meters
 */
mxml_node_t *xml_match_check(const mxml_node_t *meters,
        const struct column_t *columns, const struct value_t *values){
    int flag = 1;
    int meter_count = 0, column_count = 0, value_count = 0;
    mxml_node_t *meter = NULL, *row = NULL, *node = NULL;
    struct column_t *column = columns;
    struct value_t *value = values;

    row = mxmlNewElement(MXML_NO_PARENT, "row");

    for(meter_count=1, meter = mxmlGetFirstChild(meters);
            meter!=NULL; meter=mxmlWalkNext(meter, meters, MXML_DESCEND)){
        // temp data format: <column_name>datatype</column>
        node = mxmlNewElement(row, mxmlGetText(mxmlGetFirstChild(meter), 0));
        mxmlNewInteger(node, mxmlGetInteger(mxmlGetLastChild(meter)));
    }
    while(++value_count){
        if(value == values)
            break;
        value = value->prev;
    }
    while(++column_count){
        if(column == columns)
            break;
        column = column->prev;
    }
    if(column == NULL && value_count == meter_count){ // value == meters ?
        flag = 0; // match
    }
    else if(value_count == column_count){
        flag = 0; // match
    }
    else{
        flag = 1; // not match
        mxmlDelete(row);
        row = NULL;
    }

    return row;
}

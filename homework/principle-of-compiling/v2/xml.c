#include "xml.h"

void create_xml(const struct query_t *query, FILE *fp){
    mxml_node_t *xml = NULL;
    mxml_node_t *table = NULL;
    mxml_node_t *row = NULL;
    mxml_node_t *meter = NULL;
    struct column_type_t *node = query->column_type;

    xml = mxmlNewXML("1.0");

    table = mxmlNewElement(xml, query->table_name);
    row = mxmlNewElement(table, "meters");

    // meters: <column_name>datatype</column_name>
    // data:   <column_name>value</column_name>
            // circular queue, the value whether is NULL  has already been checked
    do {
        meter = mxmlNewElement(row, node->column);
        mxmlNewInteger(meter, node->datatype);
        node = node->prev;
    } while(node != NULL && node != query->column_type);

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
    struct column_t *column_node = query->column, *first_c = NULL;
    struct value_t  *value_node  = query->value, *first_v = NULL, *insert_value = NULL;
    struct column_type_t *column_type = NULL, *first_ct = NULL;
    int iresult = 0;

    xml = mxmlLoadFile(NULL, fp, MXML_TEXT_CALLBACK);
    if(xml == NULL){
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        return;
    }

    table = mxmlFindElement(xml, xml, query->table_name, NULL, NULL,MXML_DESCEND);
    if(table == NULL){
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        mxmlDelete(xml);
        return;
    }
    meters = mxmlGetFirstChild(table);  // 第一个孩子一定是表头
    if(meters == NULL){
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        mxmlDelete(xml);
        return;
    }

    row = mxmlNewElement(MXML_NO_PARENT, "row");
    if((column_type = xml_match_check(meters, column_node, value_node)) == NULL){
        fprintf(stderr, "Column count doesn't match value count\n");
        iresult = 1;
    }
    else{
        /* 1. 遍历
         *  2. 类型检查
         */
        if(column_node == NULL){
            do {
#ifdef DEBUG_XML
                fprintf(stdout, "node name: %s, node datatype: %d\n",
                        column_type->column, column_type->datatype);
                switch(value_node->datatype){
                    case FLOAT:
                        fprintf(stdout, "value data: %f value datatype: %d\n",
                                value_node->value.numf, value_node->datatype);
                        break;
                    case INT:
                        fprintf(stdout, "value data: %d value datatype: %d\n",
                                value_node->value.numi, value_node->datatype);
                        break;
                    case STRING:
                        fprintf(stdout, "value data: %s value datatype: %d\n",
                                value_node->value.string, value_node->datatype);
                        break;
                }
#endif
                if((column_type->datatype != value_node->datatype) &&
                        (column_type->datatype != FLOAT || value_node->datatype != INT)){
                // (value_node->datatype == node_datatype) ||
                //      (node_datatype == FLOAT && value_node->datatype == INT)
                // 允许 INT 转换成 FLOAT
                    xml_datatype_not_match(column_type->column, value_node);
                    iresult = 1;
                    break;
                }
                if(column_type->datatype == FLOAT && value_node->datatype == INT){
                    value_node->datatype = column_type->datatype;
                    value_node->value.numf = value_node->value.numi;
                }
                xml_insert_item(row, column_type->column, value_node);
                column_type = column_type->prev;
                value_node = value_node->prev;
            } while(column_type != NULL
                    && value_node != NULL
                    && value_node != query->value);
        }
        else{// 超级傻逼的方法...
            first_ct = column_type;
            first_c = column_node;
            first_v = value_node;
            // all column is in column_type ?
            do{
                iresult = 1;
                column_type = first_ct;
                do{
                    if(strcmp(column_node->column, column_type->column) == 0){
                        iresult = 0;
                        break;
                    }
                    column_type = column_type->prev;
                }while(column_type != NULL && column_type != first_ct); 
                if(iresult == 1){
                    fprintf(stderr, "ERROR: Unknow column %s\n", column_node->column);
                    break;
                }
                else
                    column_node = column_node->prev;
            }while(column_node != NULL && column_node != first_c);

            if(iresult != 1){ // all column is in column_type
                column_type = first_ct;
                do {
                    column_node = first_c;
                    value_node = first_v;
                    insert_value = NULL;

                    do{
                        if(strcmp(column_type->column, column_node->column) == 0){
                            if((column_type->datatype != value_node->datatype) &&
                                    (column_type->datatype != FLOAT || value_node->datatype != INT)){
                            // (value_node->datatype == node_datatype) ||
                            //      (node_datatype == FLOAT && value_node->datatype == INT)
                            // 允许 INT 转换成 FLOAT
                                xml_datatype_not_match(column_type->column, value_node);
                                iresult = 1;
                                break;
                            }
                            if(column_type->datatype == FLOAT && value_node->datatype == INT){
                                value_node->datatype = column_type->datatype;
                                value_node->value.numf = value_node->value.numi;
                            }
                            insert_value = value_node;
                            break;
                        }
                        column_node = column_node->prev;
                        value_node = value_node->prev;
                    }while(column_node != NULL && column_node != first_c);

                    if(iresult == 1){
                        break;
                    }
                    xml_insert_item(row, column_type->column, insert_value);
                    column_type = column_type->prev;
                } while(column_type != NULL && column_type != first_ct);
            }
        }
    }

    if(iresult == 0){
        mxmlAdd(table, MXML_ADD_AFTER, MXML_ADD_TO_PARENT, row);

        fseek(fp, 0, SEEK_SET);
        if(mxmlSaveFile(xml, fp, MXML_NO_CALLBACK) == -1)
            fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        else
            fprintf(stdout, "Query OK, 1 rows affected\n");
    }
    else
        mxmlDelete(row);

    free_column_type_list(column_type);
    mxmlDelete(xml);
    return;
}

void xml_insert_item(mxml_node_t *row, char *column, struct value_t *value_node){
    mxml_node_t *data = NULL;

    data = mxmlNewElement(row, column);
    if(value_node != NULL)
        xml_assign_data(data, value_node->value, value_node->datatype);
    return; 
}

void xml_assign_data(mxml_node_t *parent, union _value_t value, enum datatype_t datatype){
    switch(datatype){
        case FLOAT:
            mxmlNewReal(parent, value.numf);
            break;
        case INT:
            mxmlNewInteger(parent, value.numi);
            break;
        case STRING:
            mxmlNewText(parent, 0, value.string);
            break;
    }
    return;
}

void xml_datatype_not_match(const char *name, struct value_t *node){
    switch(node->datatype){
        case FLOAT:
            fprintf(stderr, "ERROR: value '%f', %s's type is not matched\n", node->value.numf, name);
            break;
        case INT:
            fprintf(stderr, "ERROR: value '%d', %s's type is not matched\n", node->value.numi, name);
            break;
        case STRING:
            fprintf(stderr, "ERROR: value '%s', %s's type is not matched\n", node->value.string, name);
            break;
    }
}
/* the number:
 *   columns == values
 *  or
 *   values == meters
 */
struct column_type_t *xml_match_check(mxml_node_t *meters,
        struct column_t *columns, struct value_t *values){
    int meter_count = 0, column_count = 0, value_count = 0;
    struct column_t *column = columns;
    struct value_t *value = values;
    struct column_type_t *column_type_list = NULL, *column_type = NULL;

    column_type = column_type_list = xml_get_column_type(meters);

    if(column_type_list != NULL)
        do{
            meter_count++;
            column_type = column_type->prev;
        } while(column_type != NULL && column_type != column_type_list);

    if(values != NULL)
        do{
            value_count++;
            value = value->next;
        } while(value != NULL && value != values);

    if(columns != NULL)
        do{
            column_count++;
            column = column->next;
        } while(column != NULL && column != columns);

#ifdef DEBUG_XML
    fprintf(stdout, "meter_count: %d, column_count: %d, value_count: %d\n",
            meter_count, column_count, value_count);
#endif

    if(!(columns == NULL && value_count == meter_count) // value == meters ?
            && !(value_count == column_count)){
        free_column_type_list(column_type_list);
        column_type_list = NULL;
    }

    return column_type_list;
}

struct column_type_t *xml_get_column_type(mxml_node_t *meters){
    // 返回第一个元素, 不可能返回 NULL -- 语法保证
    mxml_node_t *meter = NULL;
    struct column_type_t *node = NULL, *prev = NULL;
    const char *column = NULL;
    enum datatype_t datatype;

    for(meter=mxmlGetFirstChild(meters);
            meter!=NULL; meter=mxmlGetNextSibling(meter)){
        column = mxmlGetElement(meter);
        datatype = *mxmlGetText(mxmlGetFirstChild(meter), 0) - '0';
                // mxmlLoadFile(NULL, fp, MXML_TEXT_CALLBACK)
        node = create_column_type(column, datatype_to_char(datatype));
        if(prev == NULL)
            insque(node, node);
        else
            insque(node, prev);
        prev = node;
    }
    return node->prev;
}

char *datatype_to_char(enum datatype_t datatype){
    switch(datatype){
        case 0:
            return "float";
        case 1:
            return "int";
        case 2:
            return "string";
    }
}

void select_xml(const struct query_t *query, FILE *fp){
    mxml_node_t *xml = NULL;
    mxml_node_t *table = NULL;
    mxml_node_t *meters = NULL;
    mxml_node_t *row = NULL;
    mxml_node_t *node = NULL;
    struct column_type_t *column_type = NULL, *first_ct = NULL; 
    struct column_t *column, *first_c = NULL;
    const char *node_name;
    int iresult = 0;

    first_c = column = query->column;

    xml = mxmlLoadFile(NULL, fp, MXML_TEXT_CALLBACK);
    if(xml == NULL){
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        return;
    }

    table = mxmlFindElement(xml, xml, query->table_name, NULL, NULL,MXML_DESCEND);
    if(table == NULL){
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        mxmlDelete(xml);
        return;
    }
    meters = mxmlGetFirstChild(table);  // 第一个孩子一定是表头
    if(meters == NULL){
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        mxmlDelete(xml);
        return;
    }

    first_ct = column_type = xml_get_column_type(meters);

    if(query->condition == NULL){ // no WHERE subsentence
        if(query->column == NULL){ // output all
            for(row=mxmlGetNextSibling(meters);
                        row!=NULL; row=mxmlGetNextSibling(row)){
                for(node=mxmlGetFirstChild(row);
                        node!=NULL; node=mxmlGetNextSibling(node))
                    xml_row_output(node);
                putchar('\n');
            }
        }
        else{
            do{
                iresult = 0; // 0 代表没有找到
                column_type = first_ct;
                do{
                    if(strcmp(column_type->column, column->column) == 0){
                        iresult = 1;
                        break;
                    }
                    column_type = column_type->prev; 
                }while(column_type != NULL && column_type != first_ct);
                if(iresult != 1)
                    break;
                column = column->prev;
            } while(column != NULL && column != first_c);
            if(iresult != 1)
               fprintf(stderr, "ERROR: You have an error in your SQL syntax\n");
            else {
                for(row=mxmlGetNextSibling(meters);
                        row!=NULL; row=mxmlGetNextSibling(row)){
                    for(node=mxmlGetFirstChild(row);
                            node!=NULL; node=mxmlGetNextSibling(node)){
                        node_name = mxmlGetElement(node);
                        column = first_c;
                        do{
                            if(strcmp(column->column, mxmlGetElement(node)) == 0){
                                xml_row_output(node);
                                break;
                            }
                            column = column->prev;
                        }while(column != NULL && column != first_c);
                    }
                    putchar('\n');
                }
            }
        }
    }
    else{
        if(query->column == NULL){ // output all
            for(row=mxmlGetNextSibling(meters);
                        row!=NULL; row=mxmlGetNextSibling(row)){
                if(condition_test(query->condition, row, column_type) == 1){
                    for(node=mxmlGetFirstChild(row);
                            node!=NULL; node=mxmlGetNextSibling(node))
                            xml_row_output(node);
                }
                putchar('\n');
            }
        }
        else{
            do{
                iresult = 0; // 0 代表没有找到
                column_type = first_ct;
                do{
                    if(strcmp(column_type->column, column->column) == 0){
                        iresult = 1;
                        break;
                    }
                    column_type = column_type->prev; 
                }while(column_type != NULL && column_type != first_ct);
                if(iresult != 1)
                    break;
                column = column->prev;
            } while(column != NULL && column != first_c);
            if(iresult != 1)
               fprintf(stderr, "ERROR: You have an error in your SQL syntax\n");
            else {
                for(row=mxmlGetNextSibling(meters);
                        row!=NULL; row=mxmlGetNextSibling(row)){
                    if(condition_test(query->condition, row, column_type) == 1){
                        for(node=mxmlGetFirstChild(row);
                                node!=NULL; node=mxmlGetNextSibling(node)){
                            node_name = mxmlGetElement(node);
                            column = first_c;
                            do{
                                if(strcmp(column->column, mxmlGetElement(node)) == 0){
                                    xml_row_output(node);
                                    break;
                                }
                                column = column->prev;
                            }while(column != NULL && column != first_c);
                        }
                        putchar('\n');
                    }
                }
            }
        }
    }

    free_column_type_list(column_type);
    mxmlDelete(xml);
    return;
}

void xml_row_output(mxml_node_t *node){
    const char *column = NULL;
    const char *text = NULL;

    column = mxmlGetElement(node);
    text = mxmlGetText(mxmlGetFirstChild(node), 0);
    fprintf(stdout, "%-5s:  %-5s  |", column, text == NULL ? "" : text);
    return;
}

int condition_test(struct condition_expr_t *condition, mxml_node_t *row, struct column_type_t *column_type){
    struct condition_expr_t *node = condition;
    int result = 0;
    int instr = -1;
    int iresult = 0;
    
    if(condition == NULL || row == NULL)
        iresult = 0;
    else{
        node = condition->begin;
        iresult = 0;
        do{
            result = expr_leaf_test(node->leaf, row, column_type);
            if(result == 0){
                instr = node->falseinstr;
                if(instr_in_list(condition->falselist, instr) == 1){
                    iresult = 0;
                    break;
                }
            }
            else{
                instr = node->trueinstr;
                if(instr_in_list(condition->truelist, instr) == 1){
                    iresult = 1;
                    break;
                }
            }
            node = node->next;
        } while(node != NULL && node != condition->begin);
    }
    return iresult;
}

int expr_leaf_test(struct condition_expr_leaf_t *leaf, mxml_node_t *row, struct column_type_t *column_type){
// return leaf's bool
    struct column_type_t *node = column_type;
    mxml_node_t *elem = NULL;
    const char *text = NULL;
    float numf = 0.0f;
    int numi = 0;
    int iresult = 0;
    int match = 0; // 0 -- not found, 1 -- found, data type is not matched, 2 -- found, right

    do{
        if(strcmp(leaf->column, node->column) == 0){
            if((leaf->datatype == node->datatype)
                    || (node->datatype == FLOAT && leaf->datatype == INT)){
                match = 2;
            }
            else{
                match = 1;
                fprintf(stderr, "ERROR: data type is not matched.\n");
            }
            break;
        }
        node = node->prev;
    }while(node != NULL && node != column_type); 

    if(match == 0){
        fprintf(stderr, "ERROR: You have an error in your SQL syntax\n");
        iresult = 0; // bool is false
    }
    else if (match == 1){
        iresult = 0;
    }
    else{
        elem = mxmlFindPath(row, leaf->column);
        switch(leaf->datatype){
            case FLOAT:
                text =  mxmlGetText(elem, 0);
                if(text != NULL){
                    numf = atof(text);
                        switch(leaf->logic){
                            case G:
                                if(numf-leaf->value.numf < 0)
                                    iresult = 1;
                                else
                                    iresult = 0;
                                break;
                            case GE:
                                if((numf-leaf->value.numf < 0) || (fabsf(numf-leaf->value.numf) <= 1e-6))
                                    iresult = 1;
                                else
                                    iresult = 0;
                                break;
                            case L:
                                if(numf-leaf->value.numf > 0)
                                    iresult = 1;
                                else
                                    iresult = 0;
                                break;
                            case LE:
                                if((numf-leaf->value.numf > 0) || (fabsf(numf-leaf->value.numf) <= 1e-6))
                                    iresult = 1;
                                else
                                    iresult = 0;
                                break;
                            case NE:
                                if((fabsf(numf-leaf->value.numf) > 1e-6))
                                    iresult = 1;
                                else
                                    iresult = 0;
                                break;
                            case IS:
                                if((fabsf(numf-leaf->value.numf) <= 1e-6))
                                    iresult = 1;
                                else
                                    iresult = 0;
                                break;
                            default:
                                break;
                        }
                }
                else
                    iresult = 0; // false, value doesn't exist
                break;
            case INT:
                text =  mxmlGetText(elem, 0);
                if(text != NULL){
                    numi = atoi(text);
                    switch(leaf->logic){
                        case G:
                            if((numi-leaf->value.numi) < 0)
                                iresult = 1;
                            else
                                iresult = 0;
                            break;
                        case GE:
                            if((numi-leaf->value.numi) <= 0)
                                iresult = 1;
                            else
                                iresult = 0;
                            break;
                        case L:
                            if((numi-leaf->value.numi) > 0)
                                iresult = 1;
                            else
                                iresult = 0;
                            break;
                        case LE:
                            if((numi-leaf->value.numi) >= 0)
                                iresult = 1;
                            else
                                iresult = 0;
                            break;
                        case NE:
                            if(numi != leaf->value.numi)
                                iresult = 1;
                            else
                                iresult = 0;
                            break;
                        case IS:
                            if(numi == leaf->value.numi)
                                iresult = 1;
                            else
                                iresult = 0;
                            break;
                        default:
                            break;
                    }
                }
                else
                    iresult = 0; // false, value doesn't exist
                break;
            case STRING:
                text =  mxmlGetText(elem, 0);
                switch(leaf->logic){
                    case IS:
                        if(strcmp(text, leaf->value.string) == 0)
                            iresult = 1;// true
                        else
                            iresult = 0; // false, value doesn't exist
                        break;
                    case NE:
                        if(strcmp(text, leaf->value.string) != 0)
                            iresult = 1;// true
                        else
                            iresult = 0; // false, value doesn't exist
                        break;
                    default:
                        break;
                }

                break;
        }
    }
    return iresult;
}

int instr_in_list(struct list_t *list, int instr){
    struct list_t *node = list;
    int iresult = 0;

    while(node != NULL){
        if(instr == node->instr){
            iresult = 1;
            break;
        }
        node = node->next;
    }
    return iresult;
}

void delete_xml(const struct query_t *query, FILE *fp){
    mxml_node_t *xml = NULL;
    mxml_node_t *table = NULL;
    mxml_node_t *meters = NULL;
    mxml_node_t *row = NULL;
    mxml_node_t *next_row = NULL;
    struct column_type_t *column_type = NULL;
    int iresult = 0;

    xml = mxmlLoadFile(NULL, fp, MXML_TEXT_CALLBACK);
    if(xml == NULL){
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        return;
    }

    table = mxmlFindElement(xml, xml, query->table_name, NULL, NULL,MXML_DESCEND);
    if(table == NULL){
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        mxmlDelete(xml);
        return;
    }
    meters = mxmlGetFirstChild(table);  // 第一个孩子一定是表头
    if(meters == NULL){
        fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        mxmlDelete(xml);
        return;
    }

    column_type = xml_get_column_type(meters);

    for(row=mxmlGetNextSibling(meters);
            row!=NULL; row=next_row){
        next_row = mxmlGetNextSibling(row);
        if(condition_test(query->condition, row, column_type) == 1){
            iresult++;
            mxmlDelete(row);
        }
    }

    if(iresult != 0){
        if(ftruncate(fileno(fp), 0) == 0){
            fseek(fp, 0, SEEK_SET);
            if(mxmlSaveFile(xml, fp, MXML_NO_CALLBACK) == -1)
                fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        }
        else
            fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
    }
    fprintf(stdout, "Query OK, %d rows affected\n", iresult);

    free_column_type_list(column_type);
    mxmlDelete(xml);
    return;
}

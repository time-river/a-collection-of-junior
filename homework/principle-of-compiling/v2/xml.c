#include "xml.h"

void create_xml(const struct query_t *query, FILE *fp){
    char path[BUFSIZ] = {0};
    mxml_node_t *xml = NULL;
    mxml_node_t *table = NULL;
    mxml_node_t *group = NULL;
    mxml_node_t * data= NULL;
    struct column_type_t *node = query->column_type;

    xml = mxmlNewXML("1.0");

    table = mxmlNewElement(xml, "table");
    node = node->prev; // make node became first node
    do {
        group = mxmlNewElement(table, "row");
            data = mxmlNewElement(group, "column");
            mxmlNewText(data, 0, node->column);
            data = mxmlNewElement(group, "datatype");
            mxmlNewInteger(data, node->datatype);
        node = node->prev;
    } while(node != query->column_type);

    snprintf(path, sizeof(BUFSIZ)-1, "%s/%s/%s", ROOT, query->database_name, query->table_name);
    if(access(path, F_OK&07) == 0){
        fprintf(stderr, "ERROR: Table '%s' already exists\n", query->table_name);
    }
    else{
        if(mxmlSaveFile(xml, fp, MXML_NO_CALLBACK) == -1)
            fprintf(stderr, "%s LINE %d: %s\n", __FILE__, __LINE__, strerror(errno));
        else
            fprintf(stdout, "Query OK, 0 rows affected\n");
    }

    return;
}

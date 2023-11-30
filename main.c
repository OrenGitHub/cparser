#include <stdio.h>
#include <string.h>
#include "tree-sitter/lib/include/tree_sitter/api.h"

extern const TSLanguage *tree_sitter_c();

static TSParser *allocate_c_parser()
{
    TSParser *parser = ts_parser_new();
    const TSLanguage *c_language = tree_sitter_c(); 
    ts_parser_set_language(parser,c_language);
    return parser;
}

static unsigned int c_file_size(const char *filename)
{
    FILE *fl = fopen(filename, "rt");
    if (fl == NULL) { return 0; }

    fseek(fl,0,SEEK_END);
    const unsigned int n = ftell(fl);

    fclose(fl);
    return n;
} 

static char *read_c_file(const char *filename)
{
    FILE *fl = fopen(filename, "rt");
    if (fl == NULL) { return NULL; }

    const unsigned int n = c_file_size(filename);
    char *buffer = (char *) malloc(n*sizeof(char));
    if (buffer == NULL) { return NULL; }

    fread(buffer,sizeof(char),n,fl);
    fclose(fl);

    return buffer;
}

void handle_call(const TSNode call)
{
    const unsigned int n = ts_node_child_count(call);
    for (unsigned int i=0;i<n;i++) {
        const TSNode child_i = ts_node_child(call, i);
        if (ts_node_is_named(child_i)) {
            const char *kind = ts_node_type(child_i);
            if (strcmp(kind, "identifier") == 0) {
                const TSPoint start = ts_node_start_point(child_i);
                printf("found call: [line = %2d : column = %2d]\n", start.row+1, start.column+1);
            }
        }
    }
}

void traverse(const TSNode cst)
{
    const unsigned int n = ts_node_child_count(cst);
    for (unsigned int i=0;i<n;i++) {
       const TSNode child_i = ts_node_child(cst, i);
       if (ts_node_is_named(child_i)) {
           const char *kind = ts_node_type(child_i);
           if (strcmp(kind, "call_expression") == 0) {
               handle_call(child_i);
           } else {
               traverse(child_i);
           }
       } 
    }
}

int main(int argc, char **argv)
{
    const char *filename = argv[1];
    TSParser *c_parser = allocate_c_parser();
    const char *buffer = read_c_file(filename);
    const unsigned int length = strlen(buffer);
    const TSTree *tree = ts_parser_parse_string(c_parser,NULL,buffer,length);
    const TSNode cst = ts_tree_root_node(tree);
    traverse(cst);
    return 0;
}

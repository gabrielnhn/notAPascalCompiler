/* -------------------------------------------------------------------
 *            Arquivo: compiler.h
 * -------------------------------------------------------------------
 *              Autor: Bruno Muller Junior
 *               Data: 08/2007
 *      Atualizado em: [09/08/2020, 19h:01m]
 *
 * -------------------------------------------------------------------
 *
 * Tipos, protótipos e variáveis globais do compiler (via extern)
 *
 * ------------------------------------------------------------------- */

#define TOKEN_SIZE 16

#define YYDEBUG 1

typedef enum symbols
{
    symb_program, symb_var, symb_begin, symb_end,
    symb_identifier, symb_number, symb_dot, symb_comma,
    symb_semicolon, symb_colon, symb_assignment,
    symb_open_parenthesis, symb_close_parenthesis, symb_label,
    symb_type, symb_array, symb_of, symb_procedure, symb_function,
    symb_goto, symb_if, symb_then, symb_else,
    symb_while, symb_do, symb_or, symb_and, symb_not,
    symb_div, symb_asterisk, symb_plus, symb_minus,
    symb_equal, symb_different, symb_less_or_equal, symb_less, symb_more, symb_more_or_equal,
    symb_read, symb_write
} symbols;

/* -------------------------------------------------------------------
 * variáveis globais
 * ------------------------------------------------------------------- */

extern symbols symbol, relation;
extern char token[TOKEN_SIZE];
extern int lexical_level;
extern int desloc;
extern int nl;

/* -------------------------------------------------------------------
 * prototipos globais
 * ------------------------------------------------------------------- */

void generate_code(char *, char *);
int yylex();
void yyerror(const char *s);


///// symbol table
#define MAX_SYMBOLS 420
#define MAX_SYMBOL_NAME 100
#define MAX_PARAMS_SIZE 50

#include <string.h>
#include <stdio.h>
#include <iso646.h>
#include <stdbool.h>


#define INTEGER_TYPE 1
#define BOOL_TYPE 2

#define SIMPLE_VAR_CATEGORY 1
#define PROCEDURE_CATEGORY 2
#define PARAM_CATEGORY 3
#define FUNCTION_CATEGORY 4




typedef struct
{
    int category;
    int type;
    int level, offset;
    char* name;
    bool by_reference;
    int label;

    int param_types[MAX_PARAMS_SIZE];
    int param_byrefs[MAX_PARAMS_SIZE];
    int param_num;

} symbol_t;

typedef struct
{
    symbol_t stack[MAX_SYMBOLS];
    int size;
} symbol_table;



typedef struct 
{
    int top;
    int array[MAX_SYMBOLS];
} stack_t;






int print_error ( char* erro );

void init_symbol_table(symbol_table* table);
void insert_symbol_table_simple_var(symbol_table* table, int level, int offset, char* name);
void update_symbol_table_type(symbol_table* table, int symbols_to_update, int type);
void remove_symbols_from_table(symbol_table* table, int symbols_to_remove);
void print_symbol_table(symbol_table* table);


bool search_symbol_table(symbol_table* table, char* name, int* level, int* offset);

bool search_symbol_table_index(symbol_table* table, char* name, int* index);

int get_type(char* type);


void init_stack(stack_t *stack);
bool stack_push(stack_t *stack, int x);
bool stack_pop(stack_t *stack, int* x);

void assert_symbol_exists(symbol_table *table, char *name);
// void assert_equals(int a, int b);
int assert_equal_types(stack_t* a, stack_t* b);

void insert_symbol_table_param(symbol_table *table, int level, char *name, bool byref);
void update_symbol_table_offset(symbol_table *table, int symbols_to_update, int level);
void insert_symbol_table_proc(symbol_table *table, int level, char *name, int label);

void remove_symbols_from_table_until_proc(symbol_table *table, int level);
bool symbol_table_last_proc_index(symbol_table *table, int *index);

void symbol_table_update_proc_param_array(symbol_table *table, int index, int params_to_update, int type, bool byref);
void symbol_table_get_proc_arrays(symbol_table *table, int index, int** types, int** byrefs, int* num);

int assert_equal_things(int a, int b, char* thing);

void insert_symbol_table_function(symbol_table *table, int level, char *name, int label);
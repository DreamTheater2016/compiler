#ifndef PARSE_H
#define PARSE_H

#include <lex.h>
#include <file.h>
#include <asm.h>

enum
{
	UINT64_t,
};

typedef struct
{
	char *id;
	int type;

	OPERAND op;

	//TODO: add conditions for when all the registers are used up
} VARIABLE;

typedef struct SCOPE
{
	struct SCOPE *parent;
	struct SCOPE *child;

	struct SCOPE *prev;
	struct SCOPE *next;

	int var_length;
	int var_index;
	VARIABLE *vars;
} SCOPE;

typedef struct FUNCTION
{
	char *name;
	VARIABLE *vars;
	int var_count;
	int type;
} FUNCTION;

typedef struct
{
	FUNCTION **funcs;
	int length;
	int index;
} FUNCTION_LIST;

static SCOPE *parent;
static SCOPE *current_scope;

static FUNCTION_LIST func_list;

static void MOVE(OPERAND dest, OPERAND src);

static void parse_factor(OPERAND *dest);
static void parse_term(OPERAND *dest);
static void parse_expression(OPERAND *dest);
static void parse_relation(OPERAND *dest);
static void parse_logic(OPERAND *dest);
static void parse_assignment(OPERAND *dest);


static void parse_declaration(void);
void parse_statement(int stop);

static void parse_scope(void);

static void add_variable(VARIABLE var, SCOPE *scope);

static SCOPE* add_scope(SCOPE *parent, SCOPE *child, SCOPE *prev, SCOPE *next);

void init_scope(void);

static void free_scope(SCOPE *scope);
void free_whole_scope(SCOPE *parent);

static OPERAND *find_var(SCOPE *scope, char *id);

static OPERAND *find_var_in_scope(SCOPE scope, char *id);

static void add_function(FUNCTION *func);
static FUNCTION* create_function(char *name, VARIABLE *vars, int var_count, int type);

static FUNCTION* find_function(char *name);
static void free_functions(void);
static void add_funcvar(FUNCTION *func, VARIABLE var);

static void call_function(char *func_name);

static void parse_loop(void);

#endif

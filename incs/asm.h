#ifndef ASM_H
#define ASM_H

#include "general.h"

static char 		*tokens[] =
		{
			"NEW_LINE",
			"STRING",
			"LABEL",
			"INSTRUCTION",
			"DIRECT",
			"INDIRECT",
			"REGISTER",
			"SEPARATOR",
			"COMMAND",
			"EOF",
			"DIRECT_LABEL",
			"INDERECT_LABEL"
		};

enum tokens			{
	NL,
	STRING,
	LABEL,
	INSTRUCTION,
	DIRECT,
	INDIRECT,
	REGISTER,
	SEPARATOR,
	COMMAND,
	EOF,
	DIRECT_LABEL,
	INDIRECT_LABEL,
};

typedef struct 		s_lab
{
	char 			*name;
	size_t 			row;
	size_t 			col;
	int32_t			code_pos;
	struct s_lab 	*next;
}					t_lab;

typedef struct 		s_ref
{
	size_t 			op_pos;
	size_t 			exact_pos;
	int 			on;
	int32_t 		size;
	char 			*name;
	size_t 			row;
	size_t 			col;
	struct s_ref 	*next;
}					t_ref;


typedef struct 			s_op
{
	size_t 				bytes;
	uint8_t 			code;
	struct s_lab 		*labels;
	struct s_args 		*args;
	struct s_op			*next;
}						t_op;

typedef struct 			s_args
{
	char 				*data;
	uint8_t 			type;
	int32_t  			code;
	size_t 				row;
	size_t 				col;
	struct s_args		*next;
}						t_args;

typedef struct 		s_lex
{
	char 			*lex;
	uint8_t 		type;
	unsigned 		row;
	unsigned 		col;
	struct s_lex 	*next;
}					t_lex;

typedef struct      s_cursor
{
	struct s_vec	*file;
	struct s_vec	*code;
	struct s_lex	*lex;
	struct s_lab	*lab;
	struct s_ref	*ref;
	struct s_op		*root;
	char 			*f_data;
	int             fd;
	char            *name;
	char            *comment;
	size_t			pos;
	size_t 			row;
	size_t 			col;

}                   t_cursor;

void				asm_parser(char *path);

/*
**	syntaxer_tree.c
*/
void 				syntaxer(t_cursor *p);


/*
**	syntaxer_straight.c
*/
void 				handle_expressions(t_cursor *p, t_lex *lx);
t_lex 				*handle_name(t_cursor *p, t_lex *lx);
/*
**	int_converters.c
*/
void 				int32_converter(t_cursor *p, unsigned size, t_int32 k, size_t start);
/*
**	lexer.c
*/
void 				collect_lexemes(t_cursor *p);

/*
**	s_ref_utils.c
*/
void 				print_ref(t_ref *r);
void 				check_unused_refs(t_cursor *p, t_ref *r, t_lab *lab);
void 				push_ref(t_cursor *p, t_lex *lx,
												int32_t size, size_t ex_pos);

/*
**	s_lab_utils.c
*/
void 				push_label(t_cursor *p, t_lex *lx);
int32_t 			find_declared_labs(t_cursor *p, t_lab *lab, char *search);

/*
**	s_lex_utils.c
*/
void 				push_lexeme(t_cursor *p, int type, char *lex);

/*
**	skipers.c
*/
int 				is_whitespace(char c);
int 				is_num(char c);
int 				get_operator(char *name);
int 				is_label_char(char c);
int 				skip_void(t_cursor *p);

/*
**	asm_utilities.c
*/
void 				print_lexical_tree(t_op *root);
void 				print_labels(t_lab *l);
void 				print_tokens(t_lex *l);
void 				free_all(t_cursor *p);
void 				skip_nl(t_cursor *p);
int32_t				core_atoi(const char *str, t_args *ar);

/*
**	init.c
*/
t_cursor			*init_cursor(char *path);

/*
**	errors.c
*/
void 				common_error(int num);
void 				lexical_error(unsigned row, unsigned col);
void 				token_error(t_lex *lx);
void 				argument_error(t_lex *lx, char *op);
void 				undeclared_label_error(t_ref *r);

#endif

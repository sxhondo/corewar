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

typedef struct 			s_ins
{
	size_t 				bytes;
	uint8_t 			code;
	size_t 				row;
	struct s_args		*args;
	struct s_lab 		*lab;
	struct s_ins		*next;
	struct s_ins 		*prev;
}						t_ins;

typedef struct		s_args
{
	char 			*data;
	uint8_t 		type;
	int32_t 		code;
	size_t 			col;
	struct s_args 	*next;
}					t_args;


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
	struct s_ins	*root;
	char 			*f_data;
	int             fd;
	char            *name;
	char            *comment;
	int32_t 		code_size;
	size_t			pos;
	size_t 			row;
	size_t 			col;

}                   t_cursor;


/*
**	analyzer.c
*/
void 				analyzer(t_cursor *p);

/*
**	syntaxer_tree.c
*/
void 				syntaxer(t_cursor *p);


/*
**	syntaxer_straight.c
*/
//void 				handle_expressions(t_cursor *p, t_lex *lx);
//t_lex 				*handle_name(t_cursor *p, t_lex *lx);

/*
**	int_converters.c
*/
void 				int32_converter(t_cursor *p, unsigned size, t_int32 k, size_t start);
int32_t				core_atoi(const char *str, size_t row, size_t col);

/*
**	lexer.c
*/
void 				lexer(t_cursor *p);


/*
**	s_utils.c
*/
void 				push_lexeme(t_cursor *p, int type, char *lex);
void 				add_label(t_lab **dst, t_lex *lx);;
void 				add_ins(t_ins **dst, t_lex *curr, t_lab *lab);
void 				push_back_argument(t_args **args, t_lex *lex);

/*
**	skipers.c
*/
int 				is_liri_attr(char c);
int 				is_whitespace(char c);
int 				is_num(char c);
int 				get_operator(char *name);
int 				is_label_char(char c);
int 				skip_void(t_cursor *p);

/*
**	asm_utilities.c
*/
void 				print_lexical_tree(t_ins *root, char m);
void 				print_labels(t_lab *l);
void 				print_tokens(t_lex *l);
void 				free_all(t_cursor *p);
int 				skip_nl(t_cursor *p);

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
void 				undeclared_label_error(char *name, size_t row, size_t col);

#endif

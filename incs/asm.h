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

typedef struct 		s_lex
{
	char 			*lex;
	uint8_t 		type;
	unsigned 		row;
	unsigned 		col;
	struct s_lex 	*next;
}					t_lex;

typedef struct      s_asm_parser
{
	t_vec           *file;
	struct s_vec	*code;
	t_lex 			*lex;
	t_lab 			*lab;
	t_ref 			*ref;
	char 			*f_data;
	int             fd;
	char            *name;
	char            *comment;
	size_t			pos;
	size_t 			row;
	size_t 			col;

}                   t_asm_parser;

void				asm_parser(char *path);

/*
**	handle_operations.c
*/
t_lex				*handle_operations(t_asm_parser *p, t_lex *lx);

/*
**	int_converters.c
*/
void 				int32_converter(t_asm_parser *p, unsigned size, t_int32 k, size_t start);
/*
**	lexer.c
*/
void 				parse_expressions(t_asm_parser *p);

/*
**	s_ref_utils.c
*/
void 				print_ref(t_ref *r);
void 				check_unused_refs(t_asm_parser *p, t_ref *r, t_lab *lab);
void 				push_ref(t_asm_parser *p, t_lex *lx,
												int32_t size, size_t ex_pos);

/*
**	s_lab_utils.c
*/
void 				push_label(t_asm_parser *p, t_lex *lx);
int32_t 			find_declared_labs(t_asm_parser *p, t_lab *lab, char *search);

/*
**	s_lex_utils.c
*/
void 				push_lexeme(t_asm_parser *p, int type, char *lex);

/*
**	skipers.c
*/
int 				is_whitespace(char c);
int 				is_num(char c);
int 				get_operator(char *name);
int 				is_label_char(char c);
int 				skip_void(t_asm_parser *p);

/*
**	asm_utilities.c
*/
//void 				print_labels(t_lab *l);
void 				print_tokens(t_lex *l);
void 				free_all(t_asm_parser *p);
t_lex 				*skip_nl(t_lex *lx);
int32_t				core_atoi(const char *str, t_lex *lx);

/*
**	init.c
*/
t_asm_parser		*init_asm_parser(char *path);

/*
**	errors.c
*/
void 				common_error(int num);
void 				lexical_error(unsigned row, unsigned col);
void 				token_error(t_lex *lx);
void 				argument_error(t_lex *lx, char *op);
void 				undeclared_label_error(t_ref *r);

#endif

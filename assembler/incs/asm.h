/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 21:51:44 by sxhondo           #+#    #+#             */
/*   Updated: 2020/02/23 21:51:45 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "general.h"

static char			*g_tokens[] =
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

enum	e_tokens		{
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

typedef struct			s_lab
{
	char				*name;
	size_t				row;
	size_t				col;
	size_t				code_pos;
	struct s_lab		*next;
}						t_lab;

typedef struct			s_ins
{
	size_t				bytes;
	uint8_t				code;
	uint8_t				type_code[3];
	uint8_t				type_code_pos;
	size_t				row;
	struct s_args		*args;
	struct s_lab		*lab;
	struct s_ins		*next;
	struct s_ins		*prev;
}						t_ins;

typedef struct			s_args
{
	char				*data;
	size_t				size;
	uint8_t				type;
	int32_t				code;
	size_t				col;
	struct s_args		*next;
}						t_args;

typedef struct			s_lex
{
	char				*lex;
	uint8_t				type;
	size_t				row;
	size_t				col;
	struct s_lex		*next;
}						t_lex;

typedef struct			s_cursor
{
	struct s_vec		*file;
	struct s_vec		*code;
	struct s_lex		*lex;
	struct s_lab		*lab;
	struct s_ins		*root;
	char				*f_data;
	int					fd;
	char				*name;
	char				*comment;
	int32_t				code_size;
	size_t				pos;
	size_t				row;
	size_t				col;
}						t_cursor;

/*
**	asm.c
*/
void					asm_parser(char *path);

/*
**	analyzer.c
*/
void					analyzer(t_cursor *p);

/*
**	calculate_distance.c
*/
int32_t					calculate_distance(t_cursor *p, t_ins *curr, char *s);

/*
**	write_byte_code.c
*/
t_vec					*write_code(t_cursor *p);

/*
**	syntaxer_tree.c
*/
void					syntaxer(t_cursor *p);

/*
**	int_converters.c
*/
void					int32_converter(t_vec *code, unsigned size, t_int32 k);
int32_t					core_atoi(const char *str, size_t row, size_t col);
void					write_null(t_vec *code, size_t size);

/*
**	lexer.c
*/
void					lexer(t_cursor *p);

/*
**	lexer_utilities.c
*/
int						get_operator(char *name);
int						is_label_char(char c);
int						skip_void(t_cursor *p);

/*
**	s_utils.c
*/
void					push_lexeme(t_cursor *p, int type, char *lex);
void					add_label(t_lab **dst, char *name, size_t row);
void					add_ins(t_ins **dst, t_lex *curr, t_lab *lab);
void					push_back_argument(t_args **args, t_lex *lex, size_t s);

/*
**	is.c
*/
int						is_liri_attr(char c);
int						is_whitespace(char c);
int						is_num(char c);

/*
**	asm_utilities.c
*/
int						is_argument(int type);
int						is_separator(int a, uint8_t code);
void					free_all(t_cursor *p);
int						skip_nl(t_cursor *p);

/*
**	init.c
*/
t_cursor				*init_cursor(char *path);

/*
**	errors.c
*/
void					common_error(int num);
void					lexical_error(unsigned row, unsigned col);
void					token_error(t_lex *lx, t_cursor *p);
void					argument_error(t_lex *lx, char *op);
void					undeclared_label_error(t_lab *l);

void					print_lexical_tree(t_ins *root, char mod);
void					print_tokens(t_lex *l);

#endif

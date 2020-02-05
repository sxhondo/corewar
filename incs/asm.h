#ifndef ASM_H
#define ASM_H

#include "op.h"
#include "libft.h"
#include "ft_printf.h"

static char         *errors[] =
		{
				"invalid file-argument",
				"invalid arguments",
				"invalid file",
				"cannot allocate memory",
				"cannot open file",
				"invalid header",
				"invalid NULL",
				"invalid operation name",
				"invalid type argument",
				"invalid register argument",
				"invalid size of argument",
				"cannot create file",
				"invalid syntax",
				"end of file reached",
				".name or .comment specified twice",
				"len of .name or .comment is too big",
				"instruction does not exist",
				"number not well formatted",
		};

enum errors 		{
	BAD_ARGUMENT_FILE,
	INVALID_ARGUMENT,
	INVALID_FILE,
	CANT_ALLOCATE,
	CANT_OPEN,
	INVALID_HEADER,
	INVALID_NULL,
	INVALID_OP_NAME,
	INVALID_TYPE_ARG,
	REGISTER_OUT_OF_BOUNDS,
	INVALID_ARG_SIZE,
	CANT_CREATE,
	INVALID_SYNTAX,
	EOF,
	DUPL_NAME_COMMENT,
	STR_TOO_BIG,
	BAD_INSTRUCTION,
	INVALID_NUM,
};

typedef struct      s_asm_parser
{
	t_vec           *file;
	char 			*f_data;
	int             fd;
	char            *name;
	char            *comment;
	size_t			pos;
	unsigned 		row;
	unsigned 		col;

}                   t_asm_parser;

typedef struct 		s_ins
{
	int 			code;
	int32_t 		args[3];
	char 			*largs[3];
	struct s_label 	*labels;
	unsigned		row;
	unsigned 		col;
	unsigned 		total_size;
	struct s_ins 	*next;
	struct s_ins 	*prev;

}					t_ins;

typedef struct 			s_label
{
	char 	 			*lab;
	struct s_ins		*in;
	unsigned			row;
	unsigned 			col;
	struct s_label		*next;
}						t_label;


void				asm_parser(char *path);


/*
**	ins_parser.c
*/
void 				ins_parser(t_asm_parser *p, t_label *lab, t_ins **ins);


/*
**	label_parser.c
*/
int 				is_label_char(char ch);
t_label 			*label_parser(t_asm_parser *p);

/*
**	s_ins.c
*/
t_ins 				*init_ins(char *name, unsigned row, unsigned col);
void 				push_back_ins(t_ins **dst, t_ins *elem);

/*
**	s_labels.c
*/
t_label 			*init_label(char *str, int len, t_asm_parser *p);
void				add_label(t_label **dst, t_label *elem);
void 				print_label(t_label *l);

/*
**	skipers.c
*/
int 				is_num(char c);
void 				skip_tab_space(t_asm_parser *p);
int 				skip_empty_space(t_asm_parser *p);
void 				skip_separator(t_asm_parser *p, t_ins *elem, int a);

/*
**	string_parser.c
*/
void 				get_comment_name(t_asm_parser *p);

/*
**	init_asm_parser.c
*/
t_asm_parser		*init_asm_parser(char *path);

/*
**	helper.c
*/
void				asm_error(int num, unsigned row, unsigned col);
int					core_atoi(const char *str, int *num, t_asm_parser *p);
void 				print_collected(t_ins *ins);
void 				free_all(t_asm_parser *p, t_ins *ins);


typedef struct 		s_op_tab
{
	uint8_t			code;
	char			*name;
	uint8_t			args_num;
	uint8_t			args_type_code;
	uint8_t			args_types[3];
	uint8_t			t_dir_size;
}					t_op_tab;


static t_op_tab		op_tab[] =
		{
				{
/* code */			0x01,
/* name */			"live",
/* args_num */		1,
/* args_t_code*/	0,
/* args_types */	{T_DIR, 0, 0},
/* T_DIR size */	4
				},
				{
/* code */			0x02,
/* name */			"ld",
/* args_num */		2,
/* args_t_code*/	1,
/* args_types */	{T_DIR | T_IND, T_REG, 0},
/* T_DIR size */	4
				},
				{
/* code */			0x03,
/* name */			"st",
/* args_num */		2,
/* args_t_code*/	1,
/* args_types */	{T_REG, T_REG | T_IND, 0},
/* T_DIR size */	4
				},
				{
/* code */			0x04,
/* name */			"add",
/* args_num */		3,
/* args_t_code*/	1,
/* args_types */	{T_REG, T_REG, T_REG},
/* T_DIR size */	4
				},
				{
/* code */			0x05,
/* name */			"sub",
/* args_num */		3,
/* args_t_code*/	1,
/* args_types */	{T_REG, T_REG, T_REG},
/* T_DIR size */	4
				},
				{
/* code */			0x06,
/* name */			"and",
/* args_num */		3,
/* args_t_code*/	1,
/* args_types */	{T_REG | T_DIR | T_IND,  T_REG |  T_DIR | T_IND, T_REG},
/* T_DIR size */	4
				},
				{
/* code */			0x07,
/* name */			"or",
/* args_num */		3,
/* args_t_code*/	1,
/* args_types */	{T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
/* T_DIR size */	4
				},
				{
/* code */			0x08,
/* name */			"xor",
/* args_num */		3,
/* args_t_code*/	1,
/* args_types */	{T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
/* T_DIR size */	4
				},
				{
/* code */			0x09,
/* name */			"zjmp",
/* args_num */		1,
/* args_t_code*/	0,
/* args_types */	{T_DIR, 0, 0},
/* T_DIR size */	2
				},
				{
/* code */			0x0a,
/* name */			"ldi",
/* args_num */		3,
/* args_t_code*/	1,
/* args_types */	{T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
/* T_DIR size */	2
				},
				{
/* code */			0x0b,
/* name */			"sti",
/* args_num */		3,
/* args_t_code*/	1,
/* args_types */	{T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
/* T_DIR size */	2
				},
				{
/* code */			0x0c,
/* name */			"fork",
/* args_num */		1,
/* args_t_code*/	0,
/* args_types */	{T_DIR, 0, 0},
/* T_DIR size */	2
				},
				{
/* code */			0x0d,
/* name */			"lld",
/* args_num */		2,
/* args_t_code*/	1,
/* args_types */	{T_DIR | T_IND, T_REG, 0},
/* T_DIR size */	4
				},
				{
/* code */			0x0e,
/* name */			"lldi",
/* args_num */		3,
/* args_t_code*/	1,
/* args_types */	{T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
/* T_DIR size */	2
				},
				{
/* code */			0x0f,
/* name */			"lfork",
/* args_num */		1,
/* args_t_code*/	0,
/* args_types */	{T_DIR, 0, 0},
/* T_DIR size */	2
				},
				{
/* code */			0x10,
/* name */			"aff",
/* args_num */		1,
/* args_t_code*/	1,
/* args_types */	{T_REG, 0, 0},
/* T_DIR size */	4
				},
		};


#endif

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "op.h"
#include "libft.h"
#include "ft_printf.h"

static char         *errors[] =
		{
				"invalid argument",
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
				"no new line between .name and .comment"
		};

enum errors 		{
	BAD_ARGUMENT,
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
	SYNTAX_ERROR,
	EOF,
	DUPL_NAME_COMMENT,
	BIG_NAME_COMMENT,
	NO_NEW_LINE
};

typedef struct      s_asm_parser
{
	t_vec           *file;
	char 			*f_data;
	int             fd;
	char            *name;
	char            *comment;
	int 			pos;
	unsigned 		row;
	unsigned 		col;

}                   t_asm_parser;


void				asm_parser(char *path);
void 				skip_empty_space(t_asm_parser *p);

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

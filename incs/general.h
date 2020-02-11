#ifndef GENERAL_H
#define GENERAL_H

#include "op.h"
#include "libft.h"
#include "ft_printf.h"

typedef union 			s_int32
{
	struct
	{
		uint8_t 		o1 : 8;
		uint8_t 		o2 : 8;
		uint8_t 		o3 : 8;
		uint8_t 		o4 : 8;
	}					octets;
	struct
	{
		uint8_t 		b1 : 2;
		uint8_t 		b2 : 2;
		uint8_t 		b3 : 2;
		uint8_t 		b4 : 2;
	}					bin;
	int32_t 			num;
}						t_int32;


static char         *errors[] =
		{
				"invalid file-argument",
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
				"name is too big",
				"comment is too big"
		};

enum errors 		{
	BAD_ARGUMENT_FILE,
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
	NAME_TOO_BIG,
	COMM_TOO_BIG
};

void				display_grid(uint8_t g[], unsigned size, size_t hl);

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:14:03 by sxhondo           #+#    #+#             */
/*   Updated: 2020/01/28 19:55:39 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DASM_H
# define DASM_H

#include <stdio.h>
#include "libft.h"
#include "ft_printf.h"
#include "op.h"

static char         *errors[] = 
{
	"invalid argument",
	"invalid file",
    "cannot allocate memory",
    "cannot open file",
	"invalid header",
	"invalid NULL",
	"invalid operation name",
	"invalid type argument"
};

enum errors 		{
					BAD_ARGUMENT,
					INVALID_FILE,
   					CANT_ALLOCATE,
					CANT_OPEN,
					INVALID_HEADER,
					INVALID_NULL,
					INVALID_OP_NAME,
					INVALID_TYPE_ARG
					
};

typedef struct 		s_op
{
	uint8_t 		op;
	uint8_t			args_type_code[3];
	uint8_t			args[3];
	struct s_op		*next;
}					t_op;

typedef struct      s_parser
{
    int             fd;
    char            *name;
    char            *comment;
	unsigned		exe_code_size;
	int 			pos;
	t_op			*ops;
}                   t_parser;



typedef struct 		s_op_tab
{
	uint8_t			code;
	char			*name;
	uint8_t			args_num;
	uint8_t			args_type_code;
	uint8_t			args_types[3];
	uint8_t			t_dir_size;	
}					t_op_tab;


void                dasm_parser(char *path);


void 				add_operation(t_op **ops, t_op *elem);
t_parser            *init_parser(char *path);
t_op 				*init_operation();

void 				display_grid(uint8_t g[], unsigned size, int hl);
void                display_error(int err);

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

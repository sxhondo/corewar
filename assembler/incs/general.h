/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 20:38:10 by sxhondo           #+#    #+#             */
/*   Updated: 2020/02/23 20:38:10 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_H
# define GENERAL_H

# include "op.h"
# include "libft.h"
# include "ft_printf.h"

typedef struct				s_octets
{
	uint8_t					o1 : 8;
	uint8_t					o2 : 8;
	uint8_t					o3 : 8;
	uint8_t					o4 : 8;
}							t_octets;

typedef struct				s_bin
{
	uint8_t					b1 : 2;
	uint8_t					b2 : 2;
	uint8_t					b3 : 2;
	uint8_t					b4 : 2;
}							t_bin;

typedef union				u_int32
{
	struct s_octets			octets;
	struct s_bin			bin;
	int32_t					num;
}							t_int32;

static char					*g_errors[] = {
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

enum	e_errors
{
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

void						display_grid(uint8_t g[], unsigned size, size_t hl);

typedef struct				s_op_tab
{
	uint8_t					code;
	char					*name;
	uint8_t					args_num;
	uint8_t					args_type_code;
	uint8_t					args_types[3];
	uint8_t					t_dir_size;
}							t_op_tab;

static t_op_tab				g_op_tab[] =
{
	{
		0x01,
		"live",
		1,
		0,
		{T_DIR, 0, 0},
		4
	},
	{
		0x02,
		"ld",
		2,
		1,
		{T_DIR | T_IND, T_REG, 0},
		4
	},
	{
		0x03,
		"st",
		2,
		1,
		{T_REG, T_REG | T_IND, 0},
		4
	},
	{
		0x04,
		"add",
		3,
		1,
		{T_REG, T_REG, T_REG},
		4
	},
	{
		0x05,
		"sub",
		3,
		1,
		{T_REG, T_REG, T_REG},
		4
	},
	{
		0x06,
		"and",
		3,
		1,
		{T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		4
	},
	{
		0x07,
		"or",
		3,
		1,
		{T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		4
	},
	{
		0x08,
		"xor",
		3,
		1,
		{T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		4
	},
	{
		0x09,
		"zjmp",
		1,
		0,
		{T_DIR, 0, 0},
		2
	},
	{
		0x0a,
		"ldi",
		3,
		1,
		{T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		2
	},
	{
		0x0b,
		"sti",
		3,
		1,
		{T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
		2
	},
	{
		0x0c,
		"fork",
		1,
		0,
		{T_DIR, 0, 0},
		2
	},
	{
		0x0d,
		"lld",
		2,
		1,
		{T_DIR | T_IND, T_REG, 0},
		4
	},
	{
		0x0e,
		"lldi",
		3,
		1,
		{T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		2
	},
	{
		0x0f,
		"lfork",
		1,
		0,
		{T_DIR, 0, 0},
		2
	},
	{
		0x10,
		"aff",
		1,
		1,
		{T_REG, 0, 0},
		4
	},
};
#endif

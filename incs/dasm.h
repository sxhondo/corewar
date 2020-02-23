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

# include "general.h"

typedef struct			s_op
{
	uint8_t				op;
	uint8_t				args_type_code[3];
	int32_t				args[3];
	struct s_op			*next;
}						t_op;

typedef struct			s_parser
{
	int					fd;
	char				*name;
	char				*comment;
	unsigned			exe_code_size;
	size_t				pos;
	t_op				*ops;
}						t_parser;

/*
**	dasm_parser.c
*/
void					dasm_parser(char *path);

/*
**	get_arg.c
*/
uint8_t					get_size(uint8_t arg_type_code, uint8_t op);
int32_t					get_dir_undir(const uint8_t code[], int pos, int arg_s);
uint8_t					get_reg(const uint8_t code[], int pos);

/*
**	check_exec_code.c
*/
void					check_exec_code(t_parser *p);

/*
**	d_init.c
*/
void					add_operation(t_op **ops, t_op *elem);
t_parser				*init_parser(char *path);
t_op					*init_operation();

/*
**	write_asm_file.c
*/
void					write_to_file(t_parser *p, char *path);

/*
**	dasm_utilities.c
*/
void					free_allocated(t_parser *p);
void					d_error(int err);
void					display_collected(t_parser *p);

#endif

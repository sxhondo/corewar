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

#include <asm.h>

typedef struct 			s_op
{
	uint8_t 			op;
	uint8_t				args_type_code[3];
	int32_t				args[3];
	struct s_op			*next;
}						t_op;

typedef struct			s_parser
{
    int             	fd;
    char            	*name;
    char            	*comment;
	unsigned			exe_code_size;
	int 				pos;
	t_op				*ops;
}                   	t_parser;

void                	dasm_parser(char *path);

void 					add_operation(t_op **ops, t_op *elem);
t_parser				*init_dasm_parser(char *path);
t_op					*init_operation();

void					write_to_file(t_parser *p, char *path);


/*
**	helper.c
*/

void					free_allocated(t_parser *p);
void					display_collected(t_parser *p);
void					display_grid(uint8_t g[], unsigned size, int hl);
void					d_error(int err);


#endif

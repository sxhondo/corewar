/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:14:03 by sxhondo           #+#    #+#             */
/*   Updated: 2020/01/27 14:14:04 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

#include "libft.h"
#include "ft_printf.h"
#include "op.h"

typedef struct      s_parser
{
    unsigned        lc_total;
    int             fd;
    char            *name;
    char            *comment;

}                   t_parser;

static char         *errors[] = 
{
	"invalid argument",
	"invalid file",
    "cannot allocate memory",
    "cannot open file",
	"invalid header"
};

enum errors {
	BAD_ARGUMENT,
	INVALID_FILE,
    CANT_ALLOCATE,
	CANT_OPEN,
	INVALID_HEADER
};

void                d_asm_parser(char *path);
t_parser            *init_parser(char *path);

void                display_error(int err);
#endif
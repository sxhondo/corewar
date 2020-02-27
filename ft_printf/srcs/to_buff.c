/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_buff.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 23:05:05 by mdeanne           #+#    #+#             */
/*   Updated: 2019/12/05 23:05:09 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ptintf.h"

char	*ft_strncropcat(char *dst_start, char *src, size_t n)
{
	size_t	i;
	char	*s1_ret;

	s1_ret = dst_start;
	i = 0;
	while (i < n)
	{
		*dst_start++ = src[i];
		i++;
	}
	return (s1_ret);
}

void	write_str(t_prsng *tools, char *str, int *len, int type_output)
{
	tools->counter += write(1, str, *len);
	if (type_output == NON_FORMAT)
		ft_bzero(str, *len);
	*len = 0;
}

void	buffer_managment(t_prsng *tools, char *str, int len, int type_output)
{
	static int lenbuf;

	if (lenbuf && (len + lenbuf >= BUFF_SIZE || type_output == LAST))
		write_str(tools, tools->buff, &lenbuf, type_output);
	if (len >= BUFF_SIZE && type_output != LAST)
		write_str(tools, str, &len, type_output);
	else if (type_output != LAST)
	{
		ft_strncropcat(&tools->buff[lenbuf], str, len);
		lenbuf += len;
		tools->flags &= ~M_ZERO_CHAR;
	}
}

void	add_str_to_buff(char **format, t_prsng *tools)
{
	int len;

	len = 0;
	while ((*format)[len] && (*format)[len] != '%')
		len++;
	buffer_managment(tools, *format, len, FORMAT);
	*format += len;
}

void	to_buff(char *str, t_prsng *tools, t_mkfld *field)
{
	int	len;

	len = ft_strlen(str) + ((tools->type == 'c' && !field->nmbr.c) ? 1 : 0) +
		((tools->type == 'c' && (tools->flags & M_MINUS) && !field->nmbr.c) ?
		field->len_empty_field : 0);
	buffer_managment(tools, str, len, NON_FORMAT);
}

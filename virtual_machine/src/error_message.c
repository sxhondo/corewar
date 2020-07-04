/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 14:11:20 by rgyles            #+#    #+#             */
/*   Updated: 2020/01/19 14:56:06 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "visual.h"

int	error_message(const char *subject, const char *message)
{
	char	error[50];

	ft_strcpy(error, RED_TERM);
	ft_strcat(error, "Error:");
	ft_strcat(error, NC_TERM);
	ft_putendl(error);
	ft_strcpy(error, subject);
	ft_strcat(error, ": ");
	ft_strcat(error, message);
	ft_putendl(error);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 21:05:05 by ylila             #+#    #+#             */
/*   Updated: 2019/08/10 19:41:04 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static _Bool	ft_isspace(const char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

static size_t	strlen_out_end_space(const char *s)
{
	size_t	len;
	size_t	space_count;

	len = 0;
	space_count = 0;
	while (*s)
	{
		if (ft_isspace(*s++))
		{
			++space_count;
			continue ;
		}
		len += space_count;
		space_count = 0;
		++len;
	}
	return (len);
}

char			*ft_strtrim(const char *s)
{
	size_t	len;
	char	*new_str;

	if (s == NULL)
		return (NULL);
	else if (*s == '\0')
		return (ft_strnew(0));
	while (ft_isspace(*s))
		++s;
	len = strlen_out_end_space(s);
	if (!(new_str = ft_strnew(len)))
		return (NULL);
	new_str = ft_strncpy(new_str, s, len);
	return (new_str);
}

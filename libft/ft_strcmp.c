/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 14:13:00 by ylila             #+#    #+#             */
/*   Updated: 2019/08/10 19:41:04 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char c1;
	unsigned char c2;

	c1 = (unsigned char)*s1;
	c2 = (unsigned char)*s2;
	while (!(c1 - c2) && (c1 || c2))
	{
		++s1;
		++s2;
		c1 = (unsigned char)*s1;
		c2 = (unsigned char)*s2;
	}
	if ((c1 < c2) && ((c1 == '\0') || (c2 != '\0')))
		return (c1 - c2);
	else if ((c1 > c2) && ((c2 == '\0') || (c1 != '\0')))
		return (c1 - c2);
	else
		return (0);
}

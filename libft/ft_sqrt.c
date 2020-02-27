/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 21:01:50 by mdeanne           #+#    #+#             */
/*   Updated: 2019/08/17 21:01:53 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_sqrt(int num, _Bool precision)
{
	int root;

	if (num < 0)
		return (-1);
	if (!num)
		return (0);
	root = 1;
	while (root < num / root && (root + 1) <= num / (root + 1))
		++root;
	if (root * root == num)
		return (root);
	if (precision)
		return (-1);
	return (root);
}

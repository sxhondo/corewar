/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_to_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 20:00:43 by rgyles            #+#    #+#             */
/*   Updated: 2020/01/12 15:27:08 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	get_size(int number)
{
	int	size;

	size = 0;
	if (number < 0)
	{
		number *= -1;
		size++;
	}
	while (number > 0)
	{
		number /= 10;
		size++;
	}
	return (size);
}

void		int_to_char(int number, char *str)
{
	int		index;

	if (number == 0)
	{
		str[0] = '0';
		str[1] = '\0';
	}
	else
	{
		index = get_size(number);
		str[index] = '\0';
		if (number < 0)
		{
			number *= -1;
			str[0] = '-';
		}
		while (number > 0)
		{
			str[--index] = (number % 10) + '0';
			number /= 10;
		}
	}
}

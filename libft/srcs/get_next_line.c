/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 17:58:41 by sxhondo           #+#    #+#             */
/*   Updated: 2019/12/26 13:28:26 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list		*search_entry(t_list **file, int fd)
{
	t_list			*tmp;

	tmp = *file;
	while (tmp)
	{
		if (tmp->content_size == (size_t)fd)
			if (tmp->content)
				return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static char			*add_entry(t_list **file, int fd)
{
	t_list			*tmp;

	if (!(tmp = search_entry(file, fd)))
	{
		tmp = ft_lstnew("", 1);
		tmp->content_size = (size_t)fd;
		ft_lstadd(file, tmp);
	}
	return ((char *)tmp->content);
}

static int			convert(t_list **file, char *tmp, char **line, int fd)
{
	int				i;
	char			*left;
	t_list			*node;

	i = 0;
	left = ft_strchr(tmp, '\n');
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (!(*line = ft_strndup(tmp, i)))
		return (0);
	if (left)
	{
		node = search_entry(file, fd);
		if (!(node->content = ft_strdup(left + 1)))
			return (0);
		ft_strdel(&tmp);
		return (1);
	}
	(search_entry(file, fd))->content_size = -1;
	ft_strdel(&tmp);
	return (1);
}

int					get_next_line(const int fd, char **line)
{
	static t_list	*file;
	char			*tmp;
	int				bytes;
	char			buf[BUFF_SIZE + 1];

	if (fd < 0 || !line || BUFF_SIZE < 1 || read(fd, buf, 0) < 0)
		return (-1);
	tmp = add_entry(&file, fd);
	while ((bytes = read(fd, buf, BUFF_SIZE)))
	{
		buf[bytes] = '\0';
		tmp = ft_strjoin_free(tmp, buf, 1);
		if (ft_strchr(tmp, '\n'))
			break ;
	}
	if (!ft_strlen(tmp))
		return (0);
	return (convert(&file, tmp, line, fd));
}

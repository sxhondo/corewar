/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:31:29 by ylila             #+#    #+#             */
/*   Updated: 2020/01/22 20:51:38 by ylila            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

t_gnl	*new_node(const int fd)
{
	t_gnl *new;

	if (!(new = (t_gnl *)malloc(sizeof(t_gnl))))
		return (NULL);
	new->fd_ = fd;
	new->str = ft_strnew(0);
	new->lb = NULL;
	new->next = new;
	return (new);
}

int		find_fd(t_gnl **lst, const int fd)
{
	t_gnl *begin;

	if (!lst || !*lst)
		return (0);
	if ((*lst)->fd_ == fd)
		return (1);
	begin = *lst;
	*lst = (*lst)->next;
	while (*lst != begin)
	{
		if ((*lst)->fd_ == fd)
			return (1);
		*lst = (*lst)->next;
	}
	return (0);
}

int		ad_fd(t_gnl **lst, t_gnl *new)
{
	t_gnl *nx_node;

	if (!new && !lst)
		return (0);
	if (!*lst)
		*lst = new;
	else if (lst && *lst)
	{
		nx_node = (*lst)->next;
		(*lst)->next = new;
		new->next = nx_node;
	}
	return (1);
}

int		free_node(t_gnl **lst)
{
	t_gnl *curr;

	if (lst && *lst)
	{
		curr = *lst;
		while ((*lst)->next != curr)
			*lst = (*lst)->next;
		(*lst)->next = curr->next;
		free(curr->str);
		curr->str = NULL;
		free(curr);
		curr = NULL;
		return (1);
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	char			buf[BF_SZ_GNL + 1];
	static t_gnl	*lst;
	char			*tmp;
	ssize_t			b;

	if (fd < 0 || !line || (!find_fd(&lst, fd) && !(ad_fd(&lst, new_node(fd)))))
		return (-1);
	find_fd(&lst, fd);
	while (!(ft_strchr(lst->str, '\n')) && (b = read(fd, &buf, BF_SZ_GNL)) > 0)
	{
		buf[b] = '\0';
		tmp = lst->str;
		lst->str = ft_strjoin(lst->str, buf);
		ft_strdel(&tmp);
	}
	if (b == -1 || (!*(tmp = lst->str) && free_node(&lst)))
		return (b == -1 ? -1 : 0);
	if (!(lst->lb = ft_strchr(lst->str, '\n')))
		*line = ft_strdup(lst->str);
	else
		*line = ft_strsub(lst->str, 0, lst->lb - lst->str);
	lst->str = ft_strsub(lst->str, (unsigned int)(ft_strlen(*line) + 1),
			ft_strlen(lst->str) - ft_strlen(*line));
	ft_strdel(&tmp);
	return (1);
}

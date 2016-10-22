/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleury <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 21:58:52 by bfleury           #+#    #+#             */
/*   Updated: 2016/10/22 11:47:34 by bfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_gnl	*new_elem(int fd)
{
	t_gnl	*elem;

	if (!(elem = (t_gnl*)ft_memalloc(sizeof(t_gnl))))
		return (NULL);
	elem->fd = fd;
	return (elem);
}

t_gnl	*check_lst(t_gnl *list, int fd)
{
	t_gnl	*elem;
	t_gnl	*last;

	elem = list;
	while (elem)
	{
		if (elem->fd == fd)
			return (elem);
		last = elem;
		elem = elem->next;
	}
	last->next = new_elem(fd);
	last->next->prev = last;
	return (last->next);
}

int		del_elem(t_gnl *elem, char **line)
{
	if (elem->data && *elem->data)
	{
		*line = ft_strdup(elem->data);
		ft_strdel(&elem->data);
		return (1);
	}
	if (elem->prev)
		elem->prev->next = elem->next;
	if (elem->next)
		elem->next->prev = elem->prev;
	free(elem);
	return (0);
}

int		check_buffer(char *buffer, t_gnl *elem, char **line)
{
	char	*tmp;

	if (buffer)
	{
		tmp = (elem->data) ? ft_strjoin(elem->data, buffer) : ft_strdup(buffer);
		ft_strdel(&elem->data);
		elem->data = tmp;
	}
	ft_bzero(buffer, BUFF_SIZE);
	if (elem->data && (tmp = ft_strchr(elem->data, '\n')))
	{
		*(tmp++) = 0;
		*line = ft_strdup(elem->data);
		ft_memmove(elem->data, tmp, ft_strlen(tmp) + 1);
		return (1);
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static t_gnl	*list = NULL;
	t_gnl			*elem;
	int				nb_char;
	char			buffer[BUFF_SIZE + 1];

	if (fd < 0 || !line || !(list = (list) ? list : new_elem(fd)))
		return (-1);
	elem = check_lst(list, fd);
	ft_bzero(buffer, BUFF_SIZE + 1);
	while ((nb_char = read(fd, buffer, BUFF_SIZE)) || elem->data)
	{
		if (nb_char < 0)
			return (-1);
		if (check_buffer(buffer, elem, line))
			return (1);
		if (!nb_char)
			return (del_elem(elem, line));
	}
	return (0);
}

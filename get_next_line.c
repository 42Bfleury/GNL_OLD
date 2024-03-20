/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleury <bfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:54:55 by bfleury           #+#    #+#             */
/*   Updated: 2024/03/07 19:14:00 by bfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line(char *buffer, char **result)
{
	int		lenght;
	char	*tmp1;
	char	*tmp2;
	char	*offset;

	tmp1 = NULL;
	if (buffer[0])
	{
		offset = ft_strchr(buffer, '\n');
		if (offset)
		{
			if (*result[0])
				tmp1 = *result;
			lenght = offset - buffer + 1;
			tmp2 = ft_substr(buffer, 0, lenght);
			*result = ft_strjoin(*result, tmp2);
			if (tmp1)
			{
				free(tmp1);
				tmp1 = NULL;
			}
			if (tmp2)
			{
				free(tmp2);
				tmp2 = NULL;
			}
			lenght = BUFFER_SIZE - lenght + 1;
			ft_memcpy(buffer, &offset[1], lenght);
			ft_bzero(&buffer[lenght - 1], BUFFER_SIZE - lenght);
			return (*result);
		}
		else
		{
			if (*result[0])
				tmp1 = *result;
			*result = ft_strjoin(*result, buffer);
			ft_bzero(buffer, BUFFER_SIZE);
			if (tmp1)
			{
				free(tmp1);
				tmp1 = NULL;
			}
		}
	}
	else if (!buffer[0] && *result[0])
		return (*result);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*result;
	int			nb_read;

	if (fd < 0)
		return (NULL);
	if (!buffer)
	{
		buffer = malloc(sizeof(*buffer) * BUFFER_SIZE + 1);
		ft_bzero(buffer, BUFFER_SIZE + 1);
	}
	result = "";
	if (get_line(buffer, &result))
		return (result);
	nb_read = 1;
	while (nb_read)
	{
		nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read < 0)
			return (NULL);
		if (get_line(buffer, &result))
			return (result);

	}
}

	/*char			buffer[BUFFER_SIZE];
	int				nb_read;

	result = malloc((sizeof(*result) * BUFFER_SIZE) + 2);
	if (!result || fd < 0)
	{
		if (result)
			free(result);
		if (DEBBUG)
			printf("%s {get_next_line} - malloc(result) failed...\n", RERROR);
		return (NULL);
	}
	nb_read = read(fd, result, BUFFER_SIZE);
	if (nb_read <= 0 || fd < 0)
	{
		if (result)
			free(result);
		if (!nb_read && DEBBUG)
			printf("%s Nothing to read from [fd: %i]\n", YINFO, fd);
		else if (DEBBUG)
			printf("%s Failed to read from [fd: %i]...\n", RERROR, fd);
		return (NULL);
	}
	else if (DEBBUG)
		printf("%s Read %i char from [fd: %i]\n", GINFO, nb_read, fd);
	result[nb_read] = '\n';
	result[nb_read + 1] = 0;
	return (result);*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 19:15:34 by mbeilles          #+#    #+#             */
/*   Updated: 2017/05/01 20:56:01 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"
#include "libft/includes/libft.h"

static size_t			ft_getic(char const *buff, char c, int *f)
{
	char const	*tmp;

	tmp = buff;
	while (*buff)
	{
		if (*buff == c)
		{
			*f = 1;
			return (buff - tmp);
		}
		buff++;
	}
	*f = 0;
	return (buff - tmp);
}

static t_fd_buffer		*create_buffer(int fd)
{
	t_fd_buffer	*tmp;

	if ((tmp = (t_fd_buffer*)malloc(sizeof(t_fd_buffer))) == NULL ||
		(tmp->buff = (char*)ft_memalloc(BUFF_SIZE + 1)) == NULL)
		return (NULL);
	tmp->fd = fd;
	tmp->j = -1;
	tmp->next = NULL;
	return (tmp);
}

static t_fd_buffer		*allocate_buffers(int fd, t_fd_buffer **b, char **l)
{
	t_fd_buffer	*tmp;

	*l = NULL;
	if (!(*b))
		return (*b = create_buffer(fd));
	tmp = *b;
	while (tmp->fd != fd && tmp->next)
		tmp = tmp->next;
	return ((tmp->fd != fd) ? tmp->next = create_buffer(fd) : tmp);
}

static char				*ft_realloc(char *buff, size_t size, size_t n)
{
	char		*tmp;

	if ((tmp = (char*)ft_memalloc(size + n + 1)) == NULL)
		return (NULL);
	if (buff)
	{
		ft_strncpy(tmp, buff, size);
		free(buff);
	}
	return (tmp);
}

int						get_next_line(int fd, char **line)
{
	static t_fd_buffer		*buffs;
	t_fd_buffer				*loc;
	int						i;
	int						f;
	size_t					size;

	if (fd < 0 || BUFF_SIZE < 1 || !line ||
		(loc = allocate_buffers(fd, &buffs, line)) == NULL)
		return (-1);
	size = 0;
	i = 0;
	while (1)
	{
		if (!loc->buff[0] && ((loc->j = read(fd, loc->buff, BUFF_SIZE)) <= 0))
			return ((!loc->buff[0] && *line) ? 1 : loc->j);
		i = ft_getic(loc->buff, '\n', &f);
		if ((*line = (char*)ft_realloc(*line, size, i)) == NULL)
			return (-1);
		ft_strncpy(*line + size, loc->buff, i);
		ft_strncpy(loc->buff, loc->buff + i + f, BUFF_SIZE - i - f);
		ft_bzero(loc->buff + BUFF_SIZE - i - f, i + f);
		size += i;
		if (f)
			return (1);
	}
}

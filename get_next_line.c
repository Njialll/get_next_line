/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 19:15:34 by mbeilles          #+#    #+#             */
/*   Updated: 2017/04/30 15:26:53 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"
#include "libft/libft.h"

static size_t	ft_getic(char const *buff, size_t len, char c)
{
	char const	*tmp;

	tmp = buff;
	while (*buff && *buff != c && (buff - tmp) < (long)len)
		buff++;
	return (buff - tmp);
}

static int		allocate_buffers(int fd, t_fd_buffer *buffs, char **line)
{
	t_fd_buffer	*tmp;

	if ((*line = (char*)malloc(1)) == NULL)
		return (-1);
	if (!buffs)
	{
		if ((buffs = (t_fd_buffer*)malloc(sizeof(t_fd_buffer))) == NULL)
			return (-1);
		if ((buffs->buffer = (char*)malloc(BUFF_SIZE)) == NULL)
			return (-1);
		buffs->fd = fd;
		buffs->next = NULL;
	}
	while (buffs->next && buffs->fd != fd)
		buffs = buffs->next;
	if ((tmp = (t_fd_buffer*)malloc(sizeof(t_fd_buffer))) == NULL)
		return (-1);
	if ((tmp->buffer = (char*)malloc(BUFF_SIZE)) == NULL)
		return (-1);
	tmp->fd = fd;
	tmp->next = NULL;
	buffs->next = tmp;
	return (1);
}

static char		*ft_realloc(char *buff, size_t n)
{
	char		*tmp;
	size_t		len;

	len = ft_strlen(buff);
	if ((tmp = (char*)malloc(len + n)) == NULL)
		return (NULL);
	ft_bzero(tmp, len);
	ft_strcpy(tmp, buff);
	free(buff);
	return (tmp);
}

int				get_next_line(int fd, char **line)
{
	static t_fd_buffer		*buffs;
	t_fd_buffer				*loc;
	int						i;

	if (fd < 0 || BUFF_SIZE < 1 || !line)
		return (-1);
	if ((allocate_buffers(fd, buffs, line)) < 0)
		return (-1);
	loc = buffs;
	while (loc->next)
		loc = loc->next;
	while ((i = read(fd, loc->buffer, BUFF_SIZE)) < 0)
	{
		if ((*line = (char*)ft_realloc(*line, i)) == NULL)
			return (-1);
		i = ft_getic(loc->buffer, i, '\n');
		if ((ft_strncpy(*line + i, loc->buffer, i)) == NULL)
			return (-1);
		if (i < BUFF_SIZE)
			return (0);
	}
	return (0);
}

int		main(int c, char **v)
{
	int fd = open(v[1], O_RDONLY);
	char	**l;
	get_next_line(fd, l);
	printf("%s\n", *l);
	close (fd);
}

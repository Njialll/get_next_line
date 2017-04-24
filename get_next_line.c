/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 19:15:34 by mbeilles          #+#    #+#             */
/*   Updated: 2017/04/24 21:31:55 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

#define BUFF_SIZE 32

static size_t	ft_getic(char const *buff, char c, int *found)
{
	char	*tmp;

	tmp = (char *)buff;
	while (*tmp && *tmp != c)
		tmp++;
	if (*tmp == c)
		*found = 1;
	return (tmp - buff);
}

static char		*ft_strnjoin(char const *str, char *buff, size_t n)
{
	char	*tab;

	if ((tab = (char*)malloc(sizeof(tab) *
			(ft_strlen(s1) + ft_strlen(s2) + 1))) == NULL)
		return (NULL);
	ft_strcpy(tab, str);
	ft_strncat(tab, buff, n);
	return (tab);
}

int				get_next_line(int fd, char **line)
{
	char	*buff;
	char	*str;
	int		i;
	int		f;

	if ((buff = (char*)malloc(sizeof(char) * BUFF_SIZE)) == NULL)
		return (-1);
	str = "";
	f = 0;
	while ((i = read(fd, &buff, BUFF_SIZE)) < 0)
	{
		if ((str = ft_strnjoin(str, buff, ft_getic(buff, '\n', &f))) == NULL)
			return (-1);
	}
	if (!f)
		return (0);
	*line = str;
	return (1);
}

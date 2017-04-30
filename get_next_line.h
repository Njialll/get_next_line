/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 17:22:36 by mbeilles          #+#    #+#             */
/*   Updated: 2017/04/30 09:36:43 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 32

# include <string.h>
# include "libft/libft.h"

typedef struct	s_fd_buffer
{
	char				*buffer;
	int					fd;
	struct s_fd_buffer	*next;
}				t_fd_buffer;


int				get_next_line(int fd, char **line);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 18:20:56 by sxhondo           #+#    #+#             */
/*   Updated: 2019/06/10 12:59:33 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "./libft/includes/libft.h"
# include <fcntl.h>
# define BUFF_SIZE	42

typedef struct		s_gnl
{
	int				fd;
	char			*line;
	char			*left;
}					t_gnl;

int					get_next_line(const int fd, char **line);

#endif

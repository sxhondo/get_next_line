/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 18:20:21 by sxhondo           #+#    #+#             */
/*   Updated: 2019/06/01 18:00:14 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "get_next_line.h"

int		get_next_line(const int fd, char **line)
{
	static t_list	*lst;
	int				bytes;
	char			buf[BUFF_SIZE + 1];

	if (fd < 0 || !line || BUFF_SIZE < 1 || read(fd, buf, 0) < 0)
		return (-1);
	while ((bytes = read(fd, buf, BUFF_SIZE)))
	{
		buf[bytes] = '\0';
		if (ft_strchr(buf, '\n'))
			break;
	}
	printf("%s", buf);
}

int		main()
{
	char	*line;
	int		fd;

	fd = open("./tests/astronomy_domine.txt", O_RDONLY);
	get_next_line(fd, &line);
	return (0);
}

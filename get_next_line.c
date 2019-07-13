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

t_list		*find_struct(t_list **file, int fd)
{
		t_list	*tmp;

		tmp = *file;
		while (tmp)
		{
			if (tmp->content_size == (size_t)fd)
				if (tmp->content)
					return (tmp);
			tmp = tmp->next;
		}
		tmp = ft_lstnew("", 1);
		tmp->content_size = (size_t)fd;
		ft_lstadd(file, tmp);
		return (tmp);
}

int 	convert(t_list **file, char **line)
{
		int 	i;
		t_list	*tmp;
		char	*buf;
		char	*left;

		i = 0;
		tmp = *file;
		buf = (char *)tmp->content;
		while (buf[i] && buf[i] != '\n')
			i++;
		*line = ft_strndup(buf, i);
		left = (ft_strchr(buf, '\n') + 1);
		tmp->content = left;
		return (1);
}

int		get_next_line(const int fd, char **line)
{
		static t_list	*file;
		int				bytes;
		char			buf[BUFF_SIZE + 1];

		if (fd < 0 || !line || BUFF_SIZE < 1 || read(fd, buf, 0) < 0)
			return (-1);

		file = find_struct(&file, fd);
		// printf("FILE->CONTENT: %s\n", file->content);
		while ((bytes = read(fd, buf, BUFF_SIZE)))
		{
			buf[bytes] = '\0';
			file->content = ft_strjoin(file->content, buf);
			if (ft_strchr(file->content, '\n'))
				break;
		}
		if (!bytes)
			return (0);
		if (bytes < BUFF_SIZE)
		{
			*line = ft_strdup(file->content);
			return (1);
		}
		else
			return (convert(&file, line));
		return (0);
}

// int		main()
// {
// 	char	*line;
// 	int		fd;
//
// 	fd = open("./tests/two.txt", O_RDONLY);
// 	// fd = open("./tests/eof", O_RDONLY);
// 	printf("RETURN: %d\n", get_next_line(fd, &line));
// 	printf("LINE: %s\n", line);
// 	printf("RETURN: %d\n", get_next_line(fd, &line));
// 	printf("LINE: %s\n", line);
// 	return (0);
// }

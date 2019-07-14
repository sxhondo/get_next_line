/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 18:20:21 by sxhondo           #+#    #+#             */
/*   Updated: 2019/07/14 11:03:17 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "get_next_line.h"

void        *ft_realloc(void *ptr, size_t newsize)
{
	char	*str;
	char	*new;

	if (ptr && newsize == 0)
	{
		free(ptr);
		return (NULL);
	}
	str = (char *)ptr;
	if (!(new = ft_strnew(newsize - 1)))
		return (NULL);
	ft_strncpy(new, str, newsize);
	free (str);
	return (new);
}

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

int 		convert(t_list **file, char **line, int bytes)
{
	int 	i;
	char	*cont;
	char	*left;

	cont = (char *)(*file)->content;
	left = (ft_strchr(cont, '\n') + 1);
	if (!bytes) //in case last line
	{
		if (ft_strlen(cont) != 0) //in case eof
		{
			*line = ft_strdup(cont);
		}
		ft_strdel(&cont);
		return (0);
	}
	i = 0;
	while (cont[i] && cont[i] != '\n')
		i++;
	*line = ft_strndup(cont, i);
	ft_strdel(&cont);
	(*file)->content = ft_strdup(left);
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
		file->content = ft_strjoin_free(file->content, buf, 1);
		if (ft_strchr(file->content, '\n'))
			break;
	}
	return (convert(&file, line, bytes));
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

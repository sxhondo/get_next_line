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

t_list				*find_struct(t_list **file, int fd)
{
	t_list			*tmp;

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

int 				convert(t_list **file, char **line)
{
	int 			i;
	char			*cont;
	char			*left;

	i = 0;
	cont = (char *)(*file)->content;
	left = (ft_strchr((*file)->content, '\n') + 1);
	while (cont[i] && cont[i] != '\n')
		i++;
	*line = ft_strndup(cont, i);
	if (ft_strchr(cont, '\n'))
		(*file)->content = ft_strdup(left);
	else
		(*file)->content_size = -1;
	ft_strdel(&cont);
	return (1);
}

int					get_next_line(const int fd, char **line)
{
	static t_list	*file;
	int				bytes;
	char			buf[BUFF_SIZE + 1];

	if (fd < 0 || !line || BUFF_SIZE < 1 || read(fd, buf, 0) < 0)
		return (-1);

	file = find_struct(&file, fd);
	while ((bytes = read(fd, buf, BUFF_SIZE)))
	{
		buf[bytes] = '\0';
		file->content = ft_strjoin_free(file->content, buf, 1);
		if (ft_strchr(file->content, '\n'))
			break;
	}
	if (!ft_strlen(file->content))
		return (0);
	return (convert(&file, line));
}
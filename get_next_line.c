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

#include "get_next_line.h"

char	*ft_add_back(t_list **lst, t_gnl *curr, int fd)
{
	t_list		*l;

	curr->line = NULL;
	curr->left = NULL;
	curr->fd = 0;
	l = *lst;
	while (l)
	{
		if (l->content_size == (size_t)fd)
		{
			if (l->content)
				return ((char *)(l->content));
		}
		l = l->next;
	}
	l = ft_lstnew("", 1);
	l->content_size = (size_t)fd;
	ft_lstadd(lst, l);
	return ((char *)(l->content));
}

char	*ft_connect(t_gnl *curr, t_list **lst)
{
	int		i;
	char	*new;
	char	*left;

	i = 0;
	while (curr->line[i] && curr->line[i] != '\n')
		i++;
	if (!(new = ft_strnew(i)))
		return (NULL);
	ft_memcpy(new, curr->line, i);
	if (!(left = ft_strdup((ft_strchr(curr->line, '\n') + 1))))
		return (NULL);
	free(curr->line);
	(*lst)->content = left;
	return (new);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*lst;
	t_gnl			curr;
	char			buf[BUFF_SIZE + 1];

	if (fd < 0 || !line || BUFF_SIZE < 1 || read(fd, buf, 0) < 0)
		return (-1);
	curr.line = ft_add_back(&lst, &curr, fd);
	while ((curr.fd = read(fd, buf, BUFF_SIZE)))
	{
		buf[curr.fd] = '\0';
		curr.line = ft_strjoin_free(curr.line, buf, 1);
		if (ft_strchr(curr.line, '\n'))
			break ;
	}
	if (!(curr.left = ft_strchr(curr.line, '\n')))
		lst->content_size = -1;
	if (curr.fd < BUFF_SIZE && !ft_strlen(curr.line))
		return (0);
	if (curr.left)
		curr.line = ft_connect(&curr, &lst);
	*line = curr.line;
	return (1);
}
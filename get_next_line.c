/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmottal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 18:14:14 by mmottal           #+#    #+#             */
/*   Updated: 2018/01/16 15:59:12 by mmottal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t		ft_strlen_ligne(char *str)
{
	int		i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

static t_list		*choix_fd(size_t fd, t_list **newliste)
{
	t_list		*liste;

	if (*newliste == NULL)
		*newliste = ft_lstnew("\0", fd);
	liste = *newliste;
	while ((liste)->content_size != fd)
	{
		if ((liste)->next == NULL)
		{
			if ((liste->next = ft_lstnew("\0", fd)) == NULL)
				return (NULL);
		}
		liste = liste->next;
	}
	return (liste);
}

int					get_next_line(const int fd, char **line)
{
	char				buffer[BUFF_SIZE + 1];
	char				*tmp;
	int					r;
	static t_list		*tetedeliste = NULL;
	t_list				*listeactuel;

	if (fd < 0 || BUFF_SIZE < 1 || !line || (r = read(fd, buffer, 0)) < 0)
		return (-1);
	listeactuel = choix_fd((size_t)fd, &tetedeliste);
	tmp = listeactuel->content;
	while ((!(ft_strchr(tmp, '\n'))) && (r = read(fd, buffer, BUFF_SIZE)))
	{
		buffer[r] = '\0';
		if (!(tmp = ft_strfjoin(tmp, buffer)))
			return (-1);
	}
	if (*tmp == '\0')
		return (0);
	*line = ft_strsub(tmp, 0, ft_strlen_ligne(tmp));
	if (ft_strlen(tmp) == ft_strlen_ligne(tmp))
		listeactuel->content = ft_strdup(tmp + ft_strlen_ligne(tmp));
	else
		listeactuel->content = ft_strdup(tmp + ft_strlen_ligne(tmp) + 1);
	free(tmp);
	return (1);
}

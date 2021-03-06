/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matt <maquentr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 20:53:48 by matt              #+#    #+#             */
/*   Updated: 2021/02/05 15:21:47 by matt             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		free_and_null(char **str)
{
	free(*str);
	*str = NULL;
	return (-1);
}

static int		free_if_newline(char **s, char **line)
{
	char	*tmp;
	int		i;

	i = 0;
	while ((*s)[i] != '\n' && (*s)[i] != '\0')
		i++;
	if ((*s)[i] == '\n')
	{
		*line = ft_substr(*s, 0, i);
		tmp = ft_strdup(&((*s)[i + 1]));
		free(*s);
		*s = tmp;
		if ((*s)[0] == '\0')
		{
			free(*s);
			*s = NULL;
		}
	}
	else
	{
		*line = ft_strdup(*s);
		free(*s);
		*s = NULL;
	}
	return (1);
}

static	int		check_end(char **s, char **line, int byte_was_read, int fd)
{
	if (byte_was_read == 0 && !s[fd])
		return (0);
	else
		return (free_if_newline(&s[fd], line));
}

int				get_next_line(int fd, char **line)
{
	static char		*s[2000];
	char			buf[BUFFER_SIZE + 1];
	int				byte_was_read;
	char			*p_n;

	if (fd < 0 || !line)
		return (-1);
	while ((byte_was_read = read(fd, buf, BUFFER_SIZE)))
	{
		if (byte_was_read < 0)
			return (free_and_null(line));
		buf[byte_was_read] = '\0';
		if (!s[fd])
			s[fd] = ft_strdup(buf);
		else
		{
			p_n = ft_strjoin(s[fd], buf);
			free(s[fd]);
			s[fd] = p_n;
		}
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (check_end(s, line, byte_was_read, fd));
}

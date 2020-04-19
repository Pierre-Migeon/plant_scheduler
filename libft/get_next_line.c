/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 12:38:59 by pmigeon           #+#    #+#             */
/*   Updated: 2018/12/11 21:27:02 by pmigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinf(const char *s1, const char *s2)
{
	char	*merge;
	size_t	len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = 0;
	len += ft_strlen(s1);
	len += ft_strlen(s2);
	if (!(merge = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_strcpy(merge, s1);
	ft_strcat(merge, s2);
	free((void *)s1);
	return (merge);
}

int		ft_strchri(const char *s, int c)
{
	size_t i;

	i = -1;
	while (++i < ft_strlen(s) + 1)
		if (s[i] == (char)c)
			return (i);
	return (-1);
}

int		ft_strcmpz(const char *s1, const char *s2)
{
	if (!s1)
		return (0);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int		ft_spool(char **buf, int fd, char *temp)
{
	int bits_read;

	while ((bits_read = read(fd, temp, BUFF_SIZE)) > 0)
	{
		temp[bits_read] = '\0';
		buf[fd] = (!buf[fd] ? ft_strdup(temp) : ft_strjoinf(buf[fd], temp));
		if (ft_strchr(buf[fd], '\n'))
			break ;
	}
	return (bits_read);
}

int		get_next_line(const int fd, char **line)
{
	int				bits_read;
	static char		*buf[FD_MAX];
	char			temp[BUFF_SIZE + 1];
	char			*ptr;
	char			*ptr2;

	if (fd < 0 || BUFF_SIZE < 1 || read(fd, 0, 0) < 0 || fd > FD_MAX)
		return (-1);
	bits_read = ft_spool(buf, fd, temp);
	if (bits_read < 0)
		return (-1);
	ptr2 = buf[fd];
	if (!(ptr = ft_strchr(buf[fd], '\n')) && bits_read < BUFF_SIZE)
		*line = (ft_strcmpz(buf[fd], "") != 0) ? ft_strdup(buf[fd]) : NULL;
	else
		*line = ((size_t)(ptr - buf[fd]) != 0)
			? ft_strsub(buf[fd], 0, (size_t)(ptr - buf[fd])) : NULL;
	buf[fd] = ft_strchr(buf[fd], '\n')
		? ft_strdup(ft_strchr(buf[fd], '\n') + 1) : NULL;
	free(ptr2);
	if (bits_read == 0 && buf[fd] == '\0' && !*line)
		return (0);
	if (!*line)
		line[0] = ft_strnew(0);
	return (1);
}

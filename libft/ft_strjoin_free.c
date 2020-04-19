/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 16:07:23 by pmigeon           #+#    #+#             */
/*   Updated: 2018/10/24 18:37:38 by pmigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char const *s2, char c)
{
	char	*merge;
	size_t	len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = 0;
	len += ft_strlen(s1) + 1;
	len += ft_strlen(s2);
	if (!(merge = (char *)malloc(sizeof(char) * ++len)))
		return (NULL);
	ft_strcpy(merge, s1);
	len = ft_strlen(s1);
	merge[len] = c;
	merge[len + 1] = '\0';
	ft_strcat(merge, s2);
	free(s1);
	return (merge);
}

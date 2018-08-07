/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstreak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 14:52:47 by lstreak           #+#    #+#             */
/*   Updated: 2017/06/06 15:00:18 by lstreak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	l;

	i = 0;
	while (i < size && *dst && *(dst++))
		i++;
	l = size - i;
	if (!l)
		return (i + ft_strlen(src));
	while (*src)
	{
		if (l != 1)
		{
			*(dst++) = *src;
			l--;
		}
		src++;
		i++;
	}
	*dst = '\0';
	return (i);
}

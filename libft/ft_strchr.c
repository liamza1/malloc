/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstreak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 13:58:54 by lstreak           #+#    #+#             */
/*   Updated: 2017/06/02 16:47:48 by lstreak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int			i;
	char		*s1;

	i = 0;
	s1 = (char *)s;
	while (s1[i] && s1[i] != (char)c)
	{
		i++;
	}
	if (s1[i] == (char)c)
		return ((char *)&s1[i]);
	else
		return (NULL);
}

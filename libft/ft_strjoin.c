/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstreak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 14:00:10 by lstreak           #+#    #+#             */
/*   Updated: 2017/06/06 14:05:26 by lstreak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		q;
	char	*ret;

	i = 0;
	q = 0;
	ret = (char *)ft_memalloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if ((ret == NULL) || !s1 || !s2)
		return (NULL);
	while (s1[i] != '\0')
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[q] != '\0')
	{
		ret[i++] = s2[q++];
	}
	ret[i] = '\0';
	return (ret);
}

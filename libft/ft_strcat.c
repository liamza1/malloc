/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstreak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 13:29:45 by lstreak           #+#    #+#             */
/*   Updated: 2017/06/02 16:49:49 by lstreak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int			i;
	int			q;

	i = 0;
	q = 0;
	while (s1[i] != '\0')
		i++;
	while (s2[q] != '\0')
	{
		s1[i] = s2[q];
		i++;
		q++;
	}
	s1[i] = '\0';
	return (s1);
}

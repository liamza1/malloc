/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstreak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 17:34:41 by lstreak           #+#    #+#             */
/*   Updated: 2017/06/10 09:33:09 by lstreak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_itoa(int n)
{
	long	l;
	size_t	cnt;
	char	*str;
	char	neg;

	l = n;
	neg = (l < 0 ? 1 : 0);
	cnt = ft_charcount(l);
	str = ft_strnew(cnt + neg);
	if (str == NULL)
		return (NULL);
	if (neg)
	{
		l = -l;
		str[0] = '-';
	}
	while (cnt > 0)
	{
		str[cnt + neg - 1] = (l % 10) + '0';
		cnt--;
		l /= 10;
	}
	return (str);
}

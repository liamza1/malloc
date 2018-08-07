/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstreak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 15:31:16 by lstreak           #+#    #+#             */
/*   Updated: 2017/06/02 15:35:42 by lstreak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;

	i = ft_strlen(little);
	if (i == 0)
		return ((char *)big);
	while (*big && i <= len--)
		if (ft_memcmp(big++, little, i) == 0)
			return ((char *)big - 1);
	return (NULL);
}

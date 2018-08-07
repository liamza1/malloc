/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstreak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 11:49:21 by lstreak           #+#    #+#             */
/*   Updated: 2017/06/06 11:51:18 by lstreak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int			i;
	char		*ret;
	char		*tmp;

	i = 0;
	tmp = NULL;
	tmp = (char *)s;
	ret = (char *)malloc(sizeof(char) * ft_strlen(tmp) + 1);
	if (ret == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		ret[i] = f(i, tmp[i]);
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstreak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 11:25:56 by lstreak           #+#    #+#             */
/*   Updated: 2017/06/06 11:46:28 by lstreak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int			i;
	char		*ret;
	char		*tmp;

	i = 0;
	tmp = (char *)s;
	ret = (char *)malloc(sizeof(char) * ft_strlen(tmp) + 1);
	if (ret == 0)
		return (NULL);
	while (tmp[i] != '\0')
	{
		if ((ret[i] = f(tmp[i])) && ret[i])
			i++;
		else
		{
			ft_strdel(&ret);
			return (NULL);
		}
	}
	ret[i] = '\0';
	return (ret);
}

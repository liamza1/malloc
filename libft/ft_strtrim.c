/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstreak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 14:34:53 by lstreak           #+#    #+#             */
/*   Updated: 2017/06/06 14:42:32 by lstreak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	unsigned int	i;
	unsigned int	q;
	unsigned int	len;

	if (!s)
		return (NULL);
	i = 0;
	q = ft_strlen(s) - 1;
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && s[i])
		i++;
	if (!s[i])
		return (ft_strsub(s, i, 0));
	while (s[q] == ' ' || s[q] == '\n' || s[q] == '\t')
		q--;
	if (!i && q == ft_strlen(s) - 1)
		return (ft_strdup(s));
	len = q - i;
	return (ft_strsub(s, i, len + 1));
}

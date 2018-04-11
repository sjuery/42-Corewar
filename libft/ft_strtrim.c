/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/20 16:09:12 by anazar            #+#    #+#             */
/*   Updated: 2018/04/11 14:32:36 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	l;
	char	*str;

	if (!s)
		return (NULL);
	i = 0;
	l = ft_strlen(s);
	while (ft_iswhitespace(s[i]) && s[i])
		++i;
	while (l > i && ft_iswhitespace(s[l - 1]))
		--l;
	if (!(str = ft_strsub(s, i, (l - i) + 1)))
		return (NULL);
	return (str);
}

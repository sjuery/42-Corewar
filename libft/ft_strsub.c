/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 15:54:07 by anazar            #+#    #+#             */
/*   Updated: 2018/04/11 13:39:56 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	str_len;

	str_len = ft_strlen(s);
	if (!s || !(substr = ft_strnew(len)))
		return (NULL);
	i = 0;
	while (i < len && start < str_len)
		substr[i++] = s[start++];
	return (substr);
}

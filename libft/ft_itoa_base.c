/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 00:29:29 by sjuery            #+#    #+#             */
/*   Updated: 2017/12/05 03:56:22 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa_base(unsigned long long int value, int base, int lowercase)
{
	long unsigned int		len;
	static char				*str;
	long unsigned int		v;

	len = 1;
	if (base < 2 && base > 36)
		return (0);
	v = value;
	while (v /= base)
		len++;
	str = (char *)malloc(sizeof(char) * (len + 1));
	str[len] = 0;
	while (len-- > 0)
	{
		v = value % base;
		if (lowercase == 1)
			str[len] = (v > 9) ? v + 'a' - 10 : v + '0';
		else
			str[len] = (v > 9) ? v + 'A' - 10 : v + '0';
		value /= base;
	}
	return (str);
}

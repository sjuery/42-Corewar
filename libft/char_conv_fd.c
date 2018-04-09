/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_conv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:15:26 by ihodge            #+#    #+#             */
/*   Updated: 2018/04/07 23:16:02 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	char_conv_fd(t_format *format, unsigned char c)
{
	int i;

	i = 1;
	if (format->mfw)
	{
		format->minus ? ft_putchar_fd(c, format->fd) : 0;
		while (format->mfw > 1)
		{
			ft_putchar_fd(' ', format->fd);
			format->mfw--;
			i++;
		}
		format->minus ? 0 : ft_putchar_fd(c, format->fd);
	}
	else
		ft_putchar_fd(c, format->fd);
	format->strlength = i;
}

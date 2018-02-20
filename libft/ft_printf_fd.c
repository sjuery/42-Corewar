/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 12:06:54 by ihodge            #+#    #+#             */
/*   Updated: 2018/02/19 14:51:07 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	write_arg_fd(va_list ap, t_format *format, char conv)
{
	char *string;

	string = NULL;
	format->conv = conv;
	if (conv == 'i' || conv == 'd' || conv == 'D')
	{
		string = dispatcher(format, va_arg(ap, long long));
		ft_putstr_fd(string, format->fd);
		free(string);
	}
	if (conv == 'u' || conv == 'o' || conv == 'x' || conv == 'X' ||
			conv == 'p' || conv == 'U' || conv == 'O')
	{
		string = u_dispatcher(format, va_arg(ap, unsigned long));
		ft_putstr_fd(string, format->fd);
		free(string);
	}
	if (conv == 'c' || conv == 'C')//char currently doesn't print to fd
		char_conv(format, ((unsigned char)va_arg(ap, int)));
	if (conv == 's' || conv == 'S')
	{
		string = string_conv(format, va_arg(ap, char *));
		ft_putstr_fd(string, format->fd);
		free(string);
	}
}

int		process_arg_fd(va_list ap, char *str, int *length, t_format *format)
{
	int i;

	i = 1;
	save_flag(format, (char*)str + 1);
	while (is_flag(str[i]))
		i++;
	if (str[i] == '%')
	{
		char_conv(format, '%');
		(*length) += format->strlength;
		free(format);
		return (i + 1);
	}
	str += i;
	i += is_length((char*)str, format);
	str += is_length((char*)str, format);
	if (is_conv(*str) == 1)
	{
		write_arg_fd(ap, format, *str);
		(*length) += format->strlength;
		i++;
	}
	free(format);
	return (i);
}

int		ft_printf_fd(int fd, const char *str, ...)
{
	va_list		ap;
	t_format	*format;
	int			length;

	format = NULL;
	length = 0;
	va_start(ap, str);
	while (*str)
	{
		if (*str == '%')
		{
			format = create_format();
			format->fd = fd;
			str += process_arg_fd(ap, (char*)str, &length, format);
		}
		else if (*str)
		{
			ft_putchar_fd(*str, fd);
			length++;
			str++;
		}
	}
	va_end(ap);
	return (length);
}

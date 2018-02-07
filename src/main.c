/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2017/11/18 17:43:16 by mlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#define BUF_SIZE 1

void	ft_streadcat(char *s1, char *s2, unsigned int *size, unsigned int buf)
{
	unsigned int l;
	unsigned int i;

	i = 0;
	if (((*size) > buf) && ((*size) % buf == 0))
		if (s1[*size - buf])
			i = *size - buf;
	l = 0;
	while (s1[i])
		i++;
	while (s2[l] && (l < buf))
	{
		s1[i] = s2[l];
		i++;
		l++;
	}
	while (l-- > 0)
		s2[l] = '\0';
	s1[i] = '\0';
}

char	*read_input(int fd)
{
	char			*temp;
	char			*output;
	char			input[BUF_SIZE + 1];
	unsigned int	memory;

	memory = 0;
	temp = ft_memalloc(sizeof(*output) * (memory + 1));
	output = ft_memalloc(sizeof(*output) * (memory + 1));
	int i = -1;
	while ((read(fd, input, BUF_SIZE)) > 0)
	{
		if (++i >= 2192)
		{
			memory += BUF_SIZE;
			ft_strcpy(temp, output);
			free(output);
			output = ft_memalloc(sizeof(*output) * (memory + 1));
			ft_strcpy(output, temp);
			ft_streadcat(output, input, &memory, BUF_SIZE);
			output[memory] = '\0';
			free(temp);
			temp = ft_memalloc(sizeof(*temp) * (memory + 1));
		}
	}
	free(temp);
	return (output);
}

int main(int ac, char **av)
{
	(void)ac;
	unsigned char test[4096];
	int i = 0;

	ft_bzero(test, 4096);

	char *str;
	int fd = open(av[1], O_RDONLY);
	str = read_input(fd);
	i = -1;
	while (str[++i] != '\0')
		test[i] = str[i];

	fd = open(av[2], O_RDONLY);
	str = read_input(fd);
	i = 1023;
	while (str[++i] != '\0')
		test[i] = str[i];	

	i = 0;
	while (i < 4096)
	{
		if (i % 64 == 0)
			ft_printf("\n");
		if (test[i] < 16 && test[i] >= 0)
			ft_printf("0");
		ft_printf("%hhx ", test[i]);
		i++;
	}

	return 0;
}

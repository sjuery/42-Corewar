/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/02/07 18:21:50 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
//test

void	error()
{
	ft_printf("YOU DUN GOOFED\n");
	exit(0);
}

void get_info(t_io *io, int fd, int *i, unsigned char *test)
{
	int	j;

	if (!read_input(fd, io))
		error();
	j = -1;
	while (++j < io->bytes)
	{
		test[*i] = io->body[j];
		*i = *i + 1;
	}
}

int main(int ac, char **av)
{
	unsigned char test[4096];
	int i = 0;
	int x = 0;
	int	fd;
	t_io info[4];

	ft_bzero(test, 4096);

	while (++i < ac)
	{
		fd = open(av[i], O_RDONLY);
		get_info(&info[i - 1], fd, &x, test);
		x += (1024 - info[i - 1].bytes);
	}

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/02/07 16:56:00 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#define BUF_SIZE 1

int main(int ac, char **av)
{
	(void)ac;
	unsigned char test[4096];
	int i = 0;
	int x = -1;
	t_io info[4];

	ft_bzero(test, 4096);

	int fd = open(av[1], O_RDONLY);
	read_input(fd, &info[0]);
	i = -1;
	while (++i < info[0].bytes)
		test[i] = info[0].body[i];

	fd = open(av[2], O_RDONLY);
	read_input(fd, &info[1]);
	i = 1023;
	while (++x < info[1].bytes)
		test[++i] = info[1].body[x];

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

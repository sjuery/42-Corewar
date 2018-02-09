/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/02/08 16:49:10 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	error(void)
{
	ft_printf("YOU DUN GOOFED\n");
	exit(0);
}

void	write_info(t_io *io, int fd, int *i, unsigned char *test)
{
	int	j;

	if (!read_input(fd, io))
		error();
	j = -1;
	while (++j < io->head.prog_size)
	{
		test[*i] = io->body[j];
		*i = *i + 1;
	}
}

void	print_core(unsigned char *test, int i)
{
	while (++i < 4096)
	{
		if (i % 64 == 0)
			ft_printf("\n");
		if (test[i] < 16 && test[i] >= 0)
			ft_printf("0");
		ft_printf("%hhx ", test[i]);
	}
}

void 	get_n_players(int ac, char **av, t_vm *vm)
{
	int	i;

	i = 0;
	vm->num_players = ac - 1;
	while (++i < ac)
	{
		vm->players[i - 1] = av[i];
	}
}

void 	init_vm(t_vm *vm)
{
	int	i;
	int	x;
	int	fd;

	i = -1;
	x = 0;
	ft_bzero(vm->core, 4096);
	while (++i < vm->num_players)
	{
		fd = open(vm->players[i], O_RDONLY);
		write_info(&vm->info[i], fd, &x, vm->core);
		x += (1024 - vm->info[i].head.prog_size);
	}
	print_core(vm->core, -1);
}

int		main(int ac, char **av)
{
	t_vm			vm;

	get_n_players(ac, av, &vm);
	init_vm(&vm);
	init_curses(&vm);
	print_core(vm.core, -1);
	return (0);
}

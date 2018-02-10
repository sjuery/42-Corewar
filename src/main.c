/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/02/09 19:09:13 by anazar           ###   ########.fr       */
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

int		blank_pos(char **av)
{
	int	i;

	i = 0;
	while (av[i] && i < 4)
		++i;
	return (i);
}

int		get_n_players(int ac, char **av, t_vm *vm, int n_start)
{
	int	n;
	int	i;

	i = -1;
	while (++i < 4)
		vm->players[i] = 0;
	i = 0;
	while (++n_start < ac)
	{
		if (!ft_strcmp(av[n_start], "-n"))
		{
			if (ft_general_validate("%d", av[n_start + 1])
					&& ft_atoi(av[n_start + 1]) < 4)
				vm->players[ft_atoi(av[n_start + 1])] = av[n_start + 2];
			else
				error();
			n_start += 2;
		}
		else
			vm->players[blank_pos(vm->players)] = av[n_start];
		++n;
		++i;
	}
	return (n);
}

void 	init_players(int ac, char **av, t_vm *vm)
{
	int	i;
	int	n_start;

	n_start = 0;
	vm->dump_cycle = -1;
	if (!ft_strcmp(av[1], "-dump"))
	{
		if (ft_general_validate("%d", av[2]) && av[2][0] != '-')
			vm->dump_cycle = ft_atoz(av[2]);
		else
			error();
		n_start = 2;
	}
	vm->num_players = get_n_players(ac, av, vm, n_start);
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
}

int		main(int ac, char **av)
{
	t_vm			vm;

	init_players(ac, av, &vm);
	init_vm(&vm);
	init_curses(&vm);
	print_core(vm.core, -1);
	return (0);
}

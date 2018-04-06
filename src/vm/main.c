/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/04/05 19:10:36 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	introduce_players(t_vm *vm)
{
	int i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < vm->num_players)
	{
		ft_printf("* Player %i, wieghing %i bytes, \"%s\" (\"%s\") !\n", i + 1,
			vm->head[i].prog_size, vm->head[i].prog_name, vm->head[i].comment);
		i++;
	}
}

int		main(int ac, char **av)
{
	t_vm			*vm;
	time_t			t;

	if (ac < 2)
		error();
	srand((unsigned)time(&t));
	vm =(t_vm *)ft_memalloc(sizeof(t_vm));
	init_players(ac, av, vm);
	init_vm(vm);
	if (vm->f.g)
	{
		init_curses();
		keypad(stdscr, TRUE);
   		nodelay(stdscr, TRUE);
		print_curses(vm, -1, 0, 0);
	}
	else
		introduce_players(vm);
	read_bytes(vm, 1, 1);
	free(vm);
	return (0);
}

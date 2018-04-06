/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/04/04 20:11:54 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
	read_bytes(vm, 1, 1);
	free(vm);
	return (0);
}

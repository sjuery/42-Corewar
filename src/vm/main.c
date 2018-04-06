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

	if (ac < 2)
		error();
	vm =(t_vm *)ft_memalloc(sizeof(t_vm));
	init_players(ac, av, vm);
	init_vm(vm);
	if (vm->f.g)
	{
		init_curses();
		print_curses(vm, -1, 0, 0);
	}
	read_bytes(vm, 1, 1);
	free(vm);
	while(1);
	return (0);
}

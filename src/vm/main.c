/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/03/31 15:20:55 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		main(int ac, char **av)
{
	t_vm			vm;

	if (ac < 2)
		error();
	ft_bzero(&vm, sizeof(vm));
	init_players(ac, av, &vm);
	init_vm(&vm);
	ft_printf("%zu %zu\n", sizeof(vm), sizeof(vm.info[0]));
	if (vm.f.g)
	{
		init_curses();
		print_curses(&vm, -1, 0, 0);
	}
	//read_bytes(&vm, 1, 1);
	read_bytes(&vm, -1, 1, 1);
	return (0);
}

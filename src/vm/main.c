/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/04/01 16:53:17 by anazar           ###   ########.fr       */
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
	if (vm.f.g)
	{
		init_curses();
		print_curses(&vm, -1, 0, 0);
	}
	//read_bytes(&vm, 1, 1);
	read_bytes(&vm, -1, 1, 1);
	return (0);
}

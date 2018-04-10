/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/03/31 00:14:50 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	get_champ_position(t_vm *vm, char *str, int pos)
{
	if (vm->players[pos] != NULL)
	{
		ft_printf("You cannot repeat the same -n values");
		ft_printf("for multiple champions\n");
		exit(0);
	}
	vm->players[pos] = str;
	vm->num_players++;
	if (vm->num_players > 4)
		error();
}

void	fill_champ_position(t_vm *vm, char *str)
{
	int i;

	i = 0;
	while (vm->players[i] != NULL)
		i++;
	vm->players[i] = str;
	vm->num_players++;
	if (vm->num_players > 4)
		error();
}

void	check_more_flags(t_vm *vm, char **av, int *i)
{
	if ((!ft_strcmp(av[*i], "-graphic") || !ft_strcmp(av[*i], "-g"))
			&& vm->f.flags == 1 && vm->f.g == 0)
		vm->f.g = 1;
	else if ((!ft_strcmp(av[*i], "-debug") || !ft_strcmp(av[*i], "-b"))
			&& vm->f.flags == 1 && vm->f.b == 0)
		vm->f.b = 1;
	else if ((!ft_strcmp(av[*i], "-rainbow") || !ft_strcmp(av[*i], "-r"))
			&& vm->f.flags == 1 && vm->f.r == 0)
	{
		vm->f.r = 1;
		vm->f.delay = 0;
	}
	else if ((!ft_strcmp(av[*i], "-sound") || !ft_strcmp(av[*i], "-s"))
			&& ft_general_validate("%d", av[*i + 1])
			&& vm->f.flags == 1 && vm->f.s == 0)
	{
		if ((ft_atoi(av[*i + 1]) > 3) || (ft_atoi(av[*i + 1]) < 1))
			error();
		vm->f.s = ft_atoi(av[*i + 1]);
		*i = *i + 1;
	}
	else if (av[*i][0] != '-' && ft_general_validate("%s", av[*i]))
		vm->f.flags = 0;
	else
		error();
}

void	check_flags(t_vm *vm, char **av, int *i)
{
	if ((!ft_strcmp(av[*i], "-dump") || !ft_strcmp(av[*i], "-d")) &&
	ft_general_validate("%d", av[*i + 1]) && vm->f.flags == 1 && vm->f.d == 0)
	{
		vm->f.d = ft_atoi(av[*i + 1]);
		*i = *i + 1;
	}
	else if ((!ft_strcmp(av[*i], "-number") || !ft_strcmp(av[*i], "-n"))
		&& ft_general_validate("%d", av[*i + 1]))
	{
		if ((ft_atoi(av[*i + 1]) > 4) || (ft_atoi(av[*i + 1]) < 1)
			|| !ft_general_validate("%s", av[*i + 2]))
			error();
		get_champ_position(vm, av[*i + 2], (ft_atoi(av[*i + 1]) - 1));
		*i = *i + 2;
		vm->f.flags = 0;
	}
	else if ((!ft_strcmp(av[*i], "-intro") || !ft_strcmp(av[*i], "-i"))
			&& vm->f.flags == 1 && vm->f.i == 0)
		vm->f.i = 1;
	else
		check_more_flags(vm, av, i);
}

void	fill_champs(t_vm *vm, char **av, int *i)
{
	if (!ft_strcmp(av[*i], "-d"))
		*i = *i + 1;
	else if (!ft_strcmp(av[*i], "-s"))
		*i = *i + 1;
	else if (!ft_strcmp(av[*i], "-n"))
		*i = *i + 2;
	else if (av[*i][0] == '-')
		;
	else
		fill_champ_position(vm, av[*i]);
}

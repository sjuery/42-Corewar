/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/03/21 21:49:32 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	error(void)
{
	ft_printf("Corewar Usage\n");
	ft_printf("./corewar { d <value> | g | b | v } { n <value> | champion.cor }\n");
	ft_printf("-dump, -d			dump mode\n");
	ft_printf("-graphic, -g			graphic mode\n");
	ft_printf("-debug, -b			debug mode\n");
	ft_printf("-verbose, -v			verbose mode\n");\
	ft_printf("-number, -n			designate champ slot\n");
	exit(0);
}

void	write_info(t_vm *vm, int fd, int *x, int i)
{
	int	j;
	// char			body[CHAMP_MAX_SIZE + 1];
	char	*body;

	body = ft_memalloc(sizeof(char) * CHAMP_MAX_SIZE + 1);
	ft_printf("write info called, checking %d\n", fd);
	if (!read_input(fd, &vm->info[i], body))
		error();
	j = -1;
	while (++j < vm->info[i].head.prog_size)
	{
		vm->vis[*x].player = i + 1;
		vm->core[*x] = body[j];
		vm->vis[*x].byte = body[j];
		*x = *x + 1;
	}
	free(body);
}

void	print_core(unsigned char *core, int i)
{
	while (++i < MEM_SIZE)
	{
		if (i % 64 == 0)
			ft_printf("\n");
		if (core[i] < 16 && core[i] >= 0)
			ft_printf("0");
		ft_printf("%hhx ", core[i]);
	}
	ft_putchar('\n');
}

int		blank_pos(char **av)
{
	int	i;

	i = 0;
	while (av[i] && i < 4)
		++i;
	return (i);
}

// int		get_n_players(int ac, char **av, t_vm *vm, int n_start)
// {
// 	int	n;
// 	int	i;

// 	i = -1;
// 	while (++i < 4)
// 		vm->players[i] = 0;
// 	i = 0;
// 	while (++n_start < ac)
// 	{
// 		if (!ft_strcmp(av[n_start], "-n"))
// 		{
// 			if (ft_general_validate("%d", av[n_start + 1])
// 					&& ft_atoi(av[n_start + 1]) < MAX_PLAYERS)
// 				vm->players[ft_atoi(av[n_start + 1])] = av[n_start + 2];
// 			else
// 				error();
// 			n_start += 2;
// 		}
// 		else
// 			vm->players[blank_pos(vm->players)] = av[n_start];
// 		++n;
// 		++i;
// 	}
// 	return (n);
// }

void	zero_flags(t_vm *vm)
{
	vm->f.d = 0;
	vm->f.n = 0;
	vm->f.g = 0;
	vm->f.b = 0;
	vm->f.v = 0;
	vm->f.flags = 1;
}

void	get_champ_position(t_vm *vm, char *str, int pos)
{
	if (vm->players[pos] != NULL)
	{
		ft_printf("You cannot repeat the same -n values for multiple champions\n");
		exit(0);
	}
	vm->players[pos] = str;
	vm->num_players++;
	if (vm->num_players > 4)
		error();
	ft_printf("Stored position, champ [%s] in index %i\n", vm->players[pos], pos);
}

void	fill_champ_position(t_vm *vm, char *str)
{
	int i = 0;

	while (vm->players[i] != NULL)
		i++;
	vm->players[i] = str;
	vm->num_players++;
	if (vm->num_players > 4)
		error();
	ft_printf("Stored position, champ [%s] in index %i\n", vm->players[i], i);
}

void	check_flags(t_vm *vm, char **av, int *i)
{
	if ((!ft_strcmp(av[*i], "-dump") || !ft_strcmp(av[*i], "-d")) && ft_general_validate("%d", av[*i + 1])
			&& vm->f.flags == 1 && vm->f.d == 0)
	{
		vm->f.d = ft_atoi(av[*i + 1]);
		*i = *i + 1;
		ft_printf("Dump flag detected, dump value is %i", vm->f.d);
	}
	else if ((!ft_strcmp(av[*i], "-number") || !ft_strcmp(av[*i], "-n")) && ft_general_validate("%d", av[*i + 1]))
	{
		ft_printf("N called, %i and %s\n", ft_atoi(av[*i + 1]), av[*i + 2]);
		if ((ft_atoi(av[*i + 1]) > 4) && (ft_atoi(av[*i + 1]) < 1) && !ft_general_validate("%s", av[*i + 2]))
			error();
		get_champ_position(vm, av[*i + 2], (ft_atoi(av[*i + 1]) - 1));
		*i = *i + 2;
		vm->f.flags = 0;
	}
	else if ((!ft_strcmp(av[*i], "-graphic") || !ft_strcmp(av[*i], "-g"))
			&& vm->f.flags == 1 && vm->f.g == 0)
	{
		vm->f.g = 1;
		ft_printf("Graphic flag detected, value %i", vm->f.g);
	}
	else if ((!ft_strcmp(av[*i], "-debug") || !ft_strcmp(av[*i], "-b"))
			&& vm->f.flags == 1 && vm->f.b == 0)
	{
		vm->f.b = 1;
		ft_printf("Debug flag detected, value %i", vm->f.b);
	}
	else if ((!ft_strcmp(av[*i], "-verbose") || !ft_strcmp(av[*i], "-v"))
			&& vm->f.flags == 1 && vm->f.v == 0)
	{
		vm->f.v = 1;
		ft_printf("Verbose flag detected, value %i", vm->f.v);
	}
	else if (av[*i][0] != '-' && ft_general_validate("%s", av[*i]))
		vm->f.flags = 0;
	else
		error();
}

void	fill_champs(t_vm *vm, char **av, int *i)
{
	if (!ft_strcmp(av[*i], "-d"))
		*i = *i + 1;
	else if (!ft_strcmp(av[*i], "-n"))
		*i = *i + 2;
	else if (av[*i][0] == '-');
	else
		fill_champ_position(vm, av[*i]);
}

void 	init_players(int ac, char **av, t_vm *vm)
{
	int i;

	i = 0;
	zero_flags(vm);
	while (++i < ac)
	{
		printf("%s\n", av[i]);
		check_flags(vm, av, &i);
	}
	i = 0;
	while (++i < ac)
	{
		printf("second time %s\n", av[i]);
		fill_champs(vm, av, &i);
	}
}

// void 	init_players(int ac, char **av, t_vm *vm)
// {
// 	int	i;
// 	int	n_start;

// 	n_start = 0;
// 	vm->dump_cycle = -1;
// 	if (!ft_strcmp(av[1], "-dump"))
// 	{
// 		if (ft_general_validate("%d", av[2]) && av[2][0] != '-')
// 			vm->dump_cycle = ft_atoz(av[2]);
// 		else
// 			error();
// 		n_start = 2;
// 	}
// 	vm->num_players = get_n_players(ac, av, vm, n_start);
// }

void	assign_player_num(t_vm *vm, int i, unsigned char **reg)
{
	*reg = vm->info[i].regs[1];
	(*reg)[0] = 0xff;
	(*reg)[1] = 0xff;
	(*reg)[2] = 0xff;
	(*reg)[3] = 0xff - i;
	vm->info[i].player_num[0] = 0xff;
	vm->info[i].player_num[1] = 0xff;
	vm->info[i].player_num[2] = 0xff;
	vm->info[i].player_num[3] = 0xff - i;
	vm->info[i].player_int = i + 1;
}

void 	init_vm(t_vm *vm)
{
	int	i;
	int	x;
	int	fd;
	unsigned char *reg;
	int j;

	i = -1;
	x = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	ft_bzero(vm->core, MEM_SIZE);
	ft_bzero(vm->vis, MEM_SIZE);
	ft_printf("vm->num_players [%i]\n", vm->num_players);
	while (++i < vm->num_players)
	{
		ft_printf("Checking loop of init vm for %s\n", vm->players[i]);
		vm->process_count++;
		fd = open(vm->players[i], O_RDONLY);
		// fd = open("resources/champs/examples/zork.cor", O_RDONLY);
		write_info(vm, fd, &x, i);
		vm->info[i].location = i * (MEM_SIZE / vm->num_players);
		vm->info[i].start = vm->info[i].location;
		assign_player_num(vm, i, &reg);
		x += ((MEM_SIZE / vm->num_players) - vm->info[i].head.prog_size);
	}
	vm->win_player = vm->num_players;
	ft_printf("Finished loop of init_vm\n");
}

void jumptable(int a, t_vm *vm, int i)
{
	void (*jt[16])(t_vm *vm, int i);

	jt[0] = vm_live;
	jt[1] = vm_ld;
	jt[2] = vm_st;
	jt[3] = vm_add;
	jt[4] = vm_sub;
	jt[5] = vm_and;
	jt[6] = vm_or;
	jt[7] = vm_xor;
	jt[8] = vm_zjmp;
	jt[9] = vm_ldi;
	jt[10] = vm_sti;
	jt[11] = vm_fork;
	jt[12] = vm_lld;
	jt[13] = vm_lldi;
	jt[14] = vm_lfork;
	jt[15] = vm_aff;
	jt[a - 1](vm, i);
}
/*
int		valid_acb(t_instr instr, int b1, int b2, int b3)
{
	int	index;
	int	jumps[4];

	index = instr.vm->info[instr.i].index + 3;
	jumps[0] = 0;
	jumps[1] = 1;
	jumps[2] = 4;
	jumps[3] = 2;
	if (ACB1(instr.acb) != b1)
	{
		//ft_printf("ACB1 doesn't match\n");
		return (0);
	}
	else if (b1 == 1 && (instr.vm->core[index] == 0 || instr.vm->core[index] > REG_NUMBER))
	{
		//ft_printf("invalid reegister number 1: %hhx\n", instr.vm->core[index]);
		return (0);
	}
	index += jumps[b1];
	if (ACB2(instr.acb) != b2)
	{
		//ft_printf("ACB2 doesn't match\n");
		return (0);
	}
	else if (b2 == 1 && (instr.vm->core[index] == 0 || instr.vm->core[index] > REG_NUMBER))
	{
		//ft_printf("invalid reegister number 2: %hhx\n", instr.vm->core[index]);
		return (0);
	}
	index += jumps[b2];
	if (ACB3(instr.acb) != b3)
	{
		//ft_printf("ACB3 doesn't match\n");
		return (0);
	}
	else if (b3 == 1 && (instr.vm->core[index] == 0 || instr.vm->core[index] > REG_NUMBER))
	{
		//ft_printf("invalid reegister number 3: %hhx\n", instr.vm->core[index]);
		return (0);
	}
	index += jumps[b3];
	return (1);
}
*/
int		valid_acb(t_instr instr, int b1, int b2, int b3)
//int		valid_acb(unsigned char acb, int b1, int b2, int b3)
{
	return (ACB1(instr.acb) == b1 && ACB2(instr.acb) == b2 && ACB3(instr.acb) == b3);
}

int		main(int ac, char **av)
{
	t_vm			vm;
	int				ch;

	if (ac < 2)
		error();
	ft_bzero(&vm, sizeof(vm));
	init_players(ac, av, &vm);
	init_vm(&vm);
	if (vm.f.g)
	{
		init_curses();
		print_curses(&vm);
	}
	read_bytes(&vm, -1);
/*	while ((ch = getch()))
	{
		if (ch == 27)
		{
			endwin();
			break ;
		}
	}*/
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/03/19 10:40:37 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	error(void)
{
	ft_printf("YOU DUN GOOFED\n");
	exit(0);
}

void	write_info(t_vm *vm, int fd, int *x, int i)
{
	int	j;

	if (!read_input(fd, &vm->info[i]))
		error();
	j = -1;
	while (++j < vm->info[i].head.prog_size)
	{
		vm->vis[*x].player = i + 1;
		vm->core[*x] = vm->info[i].body[j];
		vm->vis[*x].byte = vm->info[i].body[j];
		*x = *x + 1;
	}
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
					&& ft_atoi(av[n_start + 1]) < MAX_PLAYERS)
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
		vm->process_count++;
		fd = open(vm->players[i], O_RDONLY);
		write_info(vm, fd, &x, i);
		vm->info[i].location = i * (MEM_SIZE / vm->num_players);
		vm->info[i].start = vm->info[i].location;
		assign_player_num(vm, i, &reg);
		x += ((MEM_SIZE / vm->num_players) - vm->info[i].head.prog_size);
	}
	vm->win_player = vm->num_players;
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
	init_curses();
	// print_core(vm.core, -1);
	print_curses(&vm);
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

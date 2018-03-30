/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/03/30 15:47:13 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	zero_flags(t_vm *vm)
{
	vm->f.d = 0;
	vm->f.n = 0;
	vm->f.g = 0;
	vm->f.b = 0;
	vm->f.v = 0;
	vm->f.flags = 1;
}

void	init_vm(t_vm *vm)
{
	int				i;
	int				x;
	int				fd;
	unsigned char	*reg;
	int				j;

	i = -1;
	x = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	ft_bzero(vm->core, MEM_SIZE);
	ft_bzero(vm->vis, MEM_SIZE);
	while (++i < vm->num_players)
	{
		vm->process_count++;
		vm->info[i].head = &vm->head[i];
		fd = open(vm->players[i], O_RDONLY);
		write_info(vm, fd, &x, i);
		vm->info[i].location = i * (MEM_SIZE / vm->num_players);
		vm->info[i].start = vm->info[i].location;
		assign_player_num(vm, i, &reg);
		x += ((MEM_SIZE / vm->num_players) - vm->info[i].head->prog_size);
	}
	vm->win_player = vm->num_players;
}
/*
void	jumptable(int a, t_vm *vm, int i)
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
}*/

void	write_info(t_vm *vm, int fd, int *x, int i)
{
	int		j;
	char	*body;

	body = ft_memalloc(sizeof(char) * CHAMP_MAX_SIZE + 1);
	if (!read_input(fd, &vm->info[i], body))
		error();
	j = -1;
	while (++j < vm->info[i].head->prog_size)
	{
		vm->vis[*x].player = i + 1;
		vm->core[*x] = body[j];
		vm->vis[*x].byte = body[j];
		*x = *x + 1;
	}
	free(body);
}

void	init_players(int ac, char **av, t_vm *vm)
{
	int i;

	i = 0;
	zero_flags(vm);
	while (++i < ac)
		check_flags(vm, av, &i);
	i = 0;
	while (++i < ac)
		fill_champs(vm, av, &i);
}

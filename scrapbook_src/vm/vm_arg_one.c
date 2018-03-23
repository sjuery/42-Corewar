/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_arg_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/03/19 00:31:59 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void get_offset_index(t_vm *vm, int i, unsigned char acb, unsigned char **l)
{
	int	idx;

	*l = NULL;
	idx = ((acb & 0b100) != 0);
	acb = acb & 0b11;
	if (acb == 1)
	{
		*l = vm->info[i].regs[vm->core[vm->info[i].start + vm->info[i].index]];
		vm->info[i].index += 1;
	}
	else if (acb == 2)
	{
		*l = &vm->core[vm->info[i].start + vm->info[i].index];
		vm->info[i].index += 2;
	}
	else if (acb == 3)
	{
		*l = &vm->core[vm->info[i].start + vm->info[i].index + indirect(vm, i, idx)];
		vm->info[i].index += 2;
	}
}
//how does a player win if no one has called live? first or last process to execute?
void	vm_live(t_vm *vm, int i)
{
	int player_int;
	vm->info[i].index++;
	vm->info[i].live++;
	vm->info[i].alive = 1;

	player_int = 0;
	if (vm->core[vm->info[i].start + vm->info[i].index] == 255 &&
			vm->core[vm->info[i].start + vm->info[i].index + 1] == 255
			&& vm->core[vm->info[i].start + vm->info[i].index + 2] == 255)
		player_int = 256 - vm->core[vm->info[i].start + vm->info[i].index + 3];
	if (player_int >= 1 && player_int <= vm->num_players)
		vm->win_player = player_int;
	vm->info[i].index += 4;
	//ft_printf("live called");
}

int		get_index_one(unsigned char *l)
{
	return (VAL(l) & 0xFFFF);
}

int		get_index_two(unsigned char *l1, unsigned char *l2)
{
	unsigned char l3[4];

	reg_add(l1, l2, l3);
	return (VAL(l3));
}

void	vm_zjmp(t_vm *vm, int i)
{

	if (!vm->info[i].carry)
	{
		vm->info[i].index += 3;
		return ;
	}
	vm->info[i].index += get_index_one(&vm->core[vm->info[i].start + vm->info[i].index + 1]);
	vm->info[i].carry = 0;
	//ft_printf("zjmp called;");
}

void	vm_sti(t_vm *vm, int i)
{
	unsigned char	*l1;
	unsigned char	*l2;
	unsigned char	*l3;
	int				acb;
	short			index;
	int				instruct_index;
	int				pos;

	instruct_index = vm->info[i].index;
	vm->info[i].index += 2;
	acb = vm->core[ACB];
	get_offset_index(vm, i, ACB1(acb), &l1);
	get_offset_index(vm, i, ACB2(acb), &l2);
	get_offset_index(vm, i, ACB3(acb), &l3);
	index = ((VAL(l2) + VAL(l3)) & 0xFFFF);
	reg_copy(&vm->core[vm->info[i].start + instruct_index + index], l1);
/*
	vm->core[vm->info[i].start + instruct_index + index] = l1[0];
	vm->core[vm->info[i].start + instruct_index + index + 1] = l1[1];
	vm->core[vm->info[i].start + instruct_index + index + 2] = l1[2];
	vm->core[vm->info[i].start + instruct_index + index + 3] = l1[3];
	vm->vis[vm->info[i].start + instruct_index + index].byte = l1[0];
	vm->vis[vm->info[i].start + instruct_index + index + 1].byte = l1[1];
	vm->vis[vm->info[i].start + instruct_index + index + 2].byte = l1[2];
	vm->vis[vm->info[i].start + instruct_index + index + 3].byte = l1[3];
	vm->vis[vm->info[i].start + instruct_index + index ].player = i + 1;
	vm->vis[vm->info[i].start + instruct_index + index + 1].player = i + 1;
	vm->vis[vm->info[i].start + instruct_index + index + 2].player = i + 1;
	vm->vis[vm->info[i].start + instruct_index + index + 3].player = i + 1;
	attron(COLOR_PAIR(vm->info[i].player_int));
	mvprintw(vm->info[i].start + instruct_index + index / 64 + 1,
			(vm->info[i].start + instruct_index + index * 2 + vm->info[i].start + instruct_index + index) % VWRAP,
			 "%02hhx", vm->vis[vm->info[i].start + instruct_index + index].byte);
	mvprintw((vm->info[i].start + instruct_index + index + 1)/ 64 + 1,
			((vm->info[i].start + instruct_index + index + 1) * 2 + vm->info[i].start + instruct_index + index + 1)
			% VWRAP, "%02hhx", vm->vis[vm->info[i].start + instruct_index + index + 2].byte);
	mvprintw((vm->info[i].start + instruct_index + index + 2)/ 64 + 1,
			((vm->info[i].start + instruct_index + index + 2) * 2 + vm->info[i].start + instruct_index + index + 2)
			% VWRAP, "%02hhx", vm->vis[vm->info[i].start + instruct_index + index + 3].byte);
	mvprintw((vm->info[i].start + instruct_index + index + 3)/ 64 + 1,
			((vm->info[i].start + instruct_index + index + 3) * 2 + vm->info[i].start + instruct_index + index + 3)
			% VWRAP, "%02hhx", vm->vis[vm->info[i].start + instruct_index + index + 1].byte);
	refresh();
	attroff(COLOR_PAIR(vm->info[i].player_int));
*/
	//ft_printf("sti called");
}

void copy_io(t_vm *vm, int dest, int src)
{
	ft_memcpy(&vm->info[dest], &vm->info[src], sizeof(t_io));
}

void	vm_lfork(t_vm *vm, int i)
{

	int j;
	unsigned char *l1;

	j = vm->process_count;
	while (vm->info[j].alive && vm->info[j].executing)
		++j;
	vm->process_count++;
	get_offset_index(vm, i, 2, &l1);
	copy_io(vm, j, i);
	vm->info[j].start = (l1[1] << 8 | l1[0]);
	vm->info[j].index = 0;
	vm->info[i].index += 3;
	//ft_printf("lfork called, process created at %i", j);
}

void	vm_fork(t_vm *vm, int i)
{
	int j;
	unsigned char *l1;

	j = vm->process_count;
	while (vm->info[j].alive && vm->info[j].executing)
		++j;
	vm->process_count++;
	get_offset_index(vm, i, 2, &l1);
	copy_io(vm, j, i);
	vm->info[j].start = (l1[1] << 8 | l1[0]) % IDX_MOD;
	vm->info[j].index = 0;
	vm->info[i].index += 3;
//	int a;

	//a = vm->info[i].body[vm->info[i].index + 1];
	//ft_printf("fork called, process created at %i, [%i]", j, vm->info[j].start);
}

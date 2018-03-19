/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_arg_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/03/18 22:17:38 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#define VWRAP 192

void get_offset_index(t_vm *vm, int i, unsigned char acb, unsigned char **l)
{
	*l = NULL;
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
		*l = &vm->core[vm->info[i].start + vm->info[i].index + indirect(vm, i, vm->core[vm->info[i].start + vm->info[i].index - 2])];
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
	return (l[0] * 0x100 + l[1]);
}

int		get_index_two(unsigned char *l1, unsigned char *l2)
{
	unsigned char l3[4];

	reg_add(l1, l2, l3);
	return (l3[0] * 0x1000000 + l3[1] * 0x10000 + l3[2] * 0x100 + l3[3]);
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
//ask aneesh if he added the macro for start + index//gonna need it to make mvprintw easier for st, sti
//if the byte is less than 16, will not print correctly currently
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
	index = (l2[0] << 8 | l2[1]) + (l3[0] << 8 | l3[1]);
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
	//ft_printf("sti called");
}

void	vm_lfork(t_vm *vm, int i)
{
	(void)vm;
	(void)i;
	//ft_printf("lfork called");
}

void	vm_fork(t_vm *vm, int i)
{
	int a;

	a = vm->info[i].body[vm->info[i].index + 1];
	ft_printf("fork called, label location %i", a);
}

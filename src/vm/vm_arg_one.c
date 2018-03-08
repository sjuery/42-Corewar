/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_arg_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/03/07 23:23:45 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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

void	vm_live(t_vm *vm, int i)
{
	vm->info[i].index += 5;
	vm->info[i].live++;
	vm->info[i].alive = 1;
	ft_printf("live called");
}

void	vm_zjmp(t_vm *vm, int i)
{
	int pc;
	int first_byte;
	int second_byte;

	if (!vm->info[i].carry)
	{
		vm->info[i].index += 3;
		return ;
	}
	first_byte = vm->core[vm->info[i].start + vm->info[i].index + 1];
	second_byte = vm->core[vm->info[i].start + vm->info[i].index + 2];
	first_byte = first_byte << 8;
	pc = first_byte | second_byte;
	//two's complement; do we only need to do this if the sign bit is 1?
	pc = pc ^ 0xFFFF;
	pc++;
	pc *= -1;
	vm->info[i].index += pc;
	vm->info[i].carry = 0;
	ft_printf("zjmp called;");
}

/*
ZJMP.cor
0900 0a09 000a 0900 0a

09 = opcode for jump
000a = location (direct value)
reason this direct is 2 bytes is because in op.c it has a index value of 1 (very last value)
if there is a index value, its 2 bytes for direct, otherwise its 4
*/


void	vm_sti(t_vm *vm, int i)
{
	unsigned char	*l1;
	unsigned char	*l2;
	unsigned char	*l3;
	int				acb;
	short			index;
	int				instruct_index;

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
	ft_printf("sti called");
}

void	vm_lfork(t_vm *vm, int i)
{
	(void)vm;
	(void)i;
	ft_printf("lfork called");
}

void	vm_fork(t_vm *vm, int i)
{
	int a;

	a = vm->info[i].body[vm->info[i].index + 1];
	ft_printf("fork called, label location %i", a);
}

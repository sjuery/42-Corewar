/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_arg_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/03/06 19:39:45 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	vm_live(t_vm *vm, int i)
{
	//this if statement is fucking things up. reseting index to 0 even though index doesn't pass the prog_size
	//if (vm->info[i].index > vm->info[i].head.prog_size) // double check, if index passes prog_size, we reduce to 0
	//	vm->info[i].index = 0;
	vm->info[i].index += 5;
	vm->info[i].live++;
	vm->info[i].alive = 1;
	ft_printf("live called, num of lives called %i", vm->info[i].live);
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
//	first_byte = vm->core[vm->info[i].start + vm->info[i].index + 1];
//	second_byte = vm->core[vm->info[i].start + vm->info[i].index + 2];
//	first_byte = first_byte << 8;
//	pc = first_byte | second_byte;
	//two's complement; do we only need to do this if the sign bit is 1?
//	pc = pc ^ 0xFFFF;
//	pc++;
//	pc *= -1;
//	vm->info[i].index += pc;
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
	int acb;
	int param;

	acb = vm->info[i].body[vm->info[i].index + 1];//might have to read acb from core instead of body
	vm->info[i].index += 3;//opcode, acb, reg
	param = acb >> 4 & 3;
	if (param == T_REG)
		vm->info[i].index += 1;
	else
		vm->info[i].index += 2;
	param = acb >> 2 & 3;
	if (param == T_REG)
		vm->info[i].index += 1;
	else
		vm->info[i].index += 2;
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

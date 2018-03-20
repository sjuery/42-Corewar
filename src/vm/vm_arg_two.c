/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_arg_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/03/19 10:41:40 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	vm_and(t_vm *vm, int i)
{
	unsigned char	*l1;
	unsigned char	*l2;
	unsigned char	*l3;
	unsigned char	acb;

	vm->info[i].index+=2;
	acb = vm->core[ACB];
	if (ACB3(acb) != 1)
	{
		//ft_printf("Burn!\n");
		return ;
	}
	get_offset(vm, i, ACB1(acb) | 0b100, &l1);
	get_offset(vm, i, ACB2(acb) | 0b100, &l2);
	get_offset(vm, i, ACB3(acb), &l3);
	reg_and(l1, l2, l3);
	vm->info[i].carry = 1;
	//ft_printf("and called");
}

void	vm_xor(t_vm *vm, int i)
{
	unsigned char	*l1;
	unsigned char	*l2;
	unsigned char	*l3;
	unsigned char	acb;

	vm->info[i].index+=2;
	acb = vm->core[ACB];
	if (ACB3(acb) != 1)
	{
		//ft_printf("Burn!\n");
		return ;
	}
	get_offset(vm, i, ACB1(acb) | 0b100, &l1);
	get_offset(vm, i, ACB2(acb) | 0b100, &l2);
	get_offset(vm, i, ACB3(acb), &l3);
	reg_xor(l1, l2, l3);
	//ft_printf("xor called");
}

/*

void get_offset(t_vm *vm, int i, unsigned char acb, unsigned char **l)
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
		vm->info[i].index += 4;
	}
	else if (acb == 3)
	{
		*l = &vm->core[vm->info[i].start + vm->info[i].index +
		indirect(vm, i, idx)]; //definitely need to change this - index changes, opcode offset won't be consistent
		vm->info[i].index += 2;
	}
}

*/


void	vm_or(t_vm *vm, int i)
{
	unsigned char	*l1;
	unsigned char	*l2;
	unsigned char	*l3;
	unsigned char	acb;

	vm->info[i].index+=2;
	acb = vm->core[ACB];
	if (ACB3(acb) != 1)
	{
		//ft_printf("Burn!\n");
		return ;
	}
	get_offset(vm, i, ACB1(acb) | 0b100, &l1);
	get_offset(vm, i, ACB2(acb) | 0b100, &l2);
	get_offset(vm, i, ACB3(acb), &l3);
	reg_or(l1, l2, l3);
	//ft_printf("or called");
}

void	vm_aff(t_vm *vm, int i)
{
	unsigned char	*l1;
	unsigned char	acb;

	vm->info[i].index += 1;
	acb = vm->core[ACB];
	if (!valid_acb(acb, 1, 0, 0))
	{
		//ft_printf("Burn!\n");
		return ;
	}
	get_offset(vm, i, ACB1(acb), &l1);
	//ft_printf("%c\n", l1[3]);
	//ft_printf("aff called");
}

void	vm_add(t_vm *vm, int i)
{
	unsigned char	*l1;
	unsigned char	*l2;
	unsigned char	*l3;
	unsigned char	acb;

	vm->info[i].index += 2;
	acb = vm->core[ACB];
	if (!valid_acb(acb, 1, 1, 1))
	{
		//ft_printf("Burn!\n");
		return ;
	}
	get_offset(vm, i, ACB1(acb), &l1);
	get_offset(vm, i, ACB2(acb), &l2);
	get_offset(vm, i, ACB3(acb), &l3);
	reg_add(l1, l2, l3);
	//ft_printf("add called");
	//vm->info[i].index += 3;
}

/*
ADD .cor
0454 0102 0304 5403 0201 0454 0103 0302
9000 0000 0e02 0290 0000 0000 0102 d000
2a03

04 = add
54 = acb
01 = 1st registry
02 = 2nd registry
03 = add 1st + 2nd and place output into this registry
04 = add
54 = acb
03 = 1st
02 = 2nd
04 = output
*/

void	vm_sub(t_vm *vm, int i)
{
	unsigned char	*l1;
	unsigned char	*l2;
	unsigned char	*l3;
	unsigned char	acb;

	vm->info[i].index += 2;
	acb = vm->core[ACB];
	if (!valid_acb(acb, 1, 1, 1))
	{
		//ft_printf("Burn!\n");
		return ;
	}
	get_offset(vm, i, ACB1(acb), &l1);
	get_offset(vm, i, ACB2(acb), &l2);
	get_offset(vm, i, ACB3(acb), &l3);
	reg_sub(l1, l2, l3);
	//ft_printf("sub called");
	//vm->info[i].index += 3;
}

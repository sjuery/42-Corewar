/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_arg_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/02/21 16:00:44 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	vm_and(t_vm *vm, int i)
{
	(void)vm;
	(void)i;
	ft_printf("and called");
}

void	vm_xor(t_vm *vm, int i)
{
	(void)vm;
	(void)i;
	ft_printf("xor called");
}


void	vm_aff(t_vm *vm, int i)
{
	(void)vm;
	(void)i;
	ft_printf("aff called");
}

void	vm_add(t_vm *vm, int i)
{
	// we can skip ACB because its always 01010100
	vm->info[i].index+=2; // skips 2 forward to the first registry
	// may need aneesh to double check this, using the same functionality we used in st/ld to copy the values stored inside registry
	int output;

	// this is taking value in first registry * second registry
	output = (vm->core[vm->info[i].start + vm->info[i].index] * 256) + (vm->core[vm->info[i].start + vm->info[i].index + 1] * 256);
	// this below part is wrong, will have aneesh fix this up so the output works since its bit wise operands
	vm->info[i].regs[vm->core[vm->info[i].start + vm->info[i].index + 2]][0] = output;
	vm->info[i].regs[vm->core[vm->info[i].start + vm->info[i].index + 2]][1] = output;
	vm->info[i].regs[vm->core[vm->info[i].start + vm->info[i].index + 2]][2] = output;
	vm->info[i].regs[vm->core[vm->info[i].start + vm->info[i].index + 2]][3] = output;
	ft_printf("add called");
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

void	vm_or(t_vm *vm, int i)
{
	(void)vm;
	(void)i;
	ft_printf("or called");
}

void	vm_sub(t_vm *vm, int i)
{
	(void)vm;
	(void)i;
	ft_printf("sub called");
}

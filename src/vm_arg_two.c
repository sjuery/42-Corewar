/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_arg_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/02/26 17:34:23 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define ACB			vm->info[i].start + vm->info[i].index - 1
#define PARAM1 		vm->info[i].start + vm->info[i].index
#define PARAM2		vm->info[i].start + vm->info[i].index + 1
#define PARAM3		vm->info[i].start + vm->info[i].index + 2

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

void 	put_in_reg(unsigned char *reg, unsigned char *value)
{
	reg[0] = value[0];
	reg[1] = value[1];
	reg[2] = value[2];
	reg[3] = value[3];
}

unsigned int		char_add(unsigned char v1, unsigned char v2)
{
	int	v3;

	v3 = (unsigned int)v1 + (unsigned int)v2;
	return (v3);
}

void	vm_add(t_vm *vm, int i)
{
	vm->info[i].index+=2;
	if (!valid_acb(vm->core[ACB], 1, 1, 1))
		ft_printf("Burn!\n"); return ;
	// we can skip ACB because its always 01010100
	 // skips 2 forward to the first registry
	// may need aneesh to double check this, using the same functionality we used in st/ld to copy the values stored inside registry
	unsigned char output[4];
	unsigned int	carry;

	// this is taking value in first registry * second registry
	carry = char_add(vm->info[i].regs[PARAM1][3], vm->info[i].regs[PARAM2][3]);
	output[3] = carry % 0xFF;
	output[2] = (carry >> 8) + (carry = char_add(vm->info[i].regs[PARAM1][2], vm->info[i].regs[PARAM2][2]));
	output[1] = (carry >> 8) + (carry = char_add(vm->info[i].regs[PARAM1][1], vm->info[i].regs[PARAM2][1]));
	output[0] = (carry >> 8) + (carry = char_add(vm->info[i].regs[PARAM1][0], vm->info[i].regs[PARAM2][0]));

	put_in_reg(vm->info[i].regs[PARAM3], output);
	//output[0] = (vm->core[vm->info[i].start + vm->info[i].index] * 256) + (vm->core[vm->info[i].start + vm->info[i].index + 1] * 256);
	// this below part is wrong, will have aneesh fix this up so the output works since its bit wise operands
	//vm->info[i].regs[vm->core[vm->info[i].start + vm->info[i].index + 2]][0] = output;
	//vm->info[i].regs[vm->core[vm->info[i].start + vm->info[i].index + 2]][1] = output;
	//vm->info[i].regs[vm->core[vm->info[i].start + vm->info[i].index + 2]][2] = output;
	//vm->info[i].regs[vm->core[vm->info[i].start + vm->info[i].index + 2]][3] = output;
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

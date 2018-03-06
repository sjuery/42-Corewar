/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_arg_three.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/03/06 15:21:39 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void reg_copy(unsigned char *dest, unsigned char *src)
{
	dest[0] = src[0];
	dest[1] = src[1];
	dest[2] = src[2];
	dest[3] = src[3];
}
/*
void	vm_lld(t_vm *vm, int i)
{
	char	acb;
	int		pos;
	int		ind;

	pos = vm->info[i].index + 1;
	acb = vm->info[i].body[pos];
	if (valid_acb(acb, 2, 1, 0))
	{
		vm->info[i].index+=2;
		vm->info[i].regs[vm->core[pos + 5]][0] = vm->core[vm->info[i].start + vm->info[i].index++];
		vm->info[i].regs[vm->core[pos + 5]][1] = vm->core[vm->info[i].start + vm->info[i].index++];
		vm->info[i].regs[vm->core[pos + 5]][2] = vm->core[vm->info[i].start + vm->info[i].index++];
		vm->info[i].regs[vm->core[pos + 5]][3] = vm->core[vm->info[i].start + vm->info[i].index++];
		ft_printf("lld direct %hhx %hhx %hhx %hhx\n", vm->info[i].regs[vm->core[pos + 5]][0], vm->info[i].regs[vm->core[pos + 5]][1], vm->info[i].regs[vm->core[pos + 5]][2], vm->info[i].regs[vm->core[pos + 5]][3]);
		vm->info[i].carry++;
	}
	else if (valid_acb(acb, 3, 1, 0))
	{
		vm->info[i].index+=2;
		ind = (vm->core[vm->info[i].start + vm->info[i].index] * 256) + vm->core[vm->info[i].start + vm->info[i].index + 1];
		vm->info[i].regs[vm->core[pos + 3]][0] = vm->core[vm->info[i].start + vm->info[i].index - 2 + ind++];
		vm->info[i].regs[vm->core[pos + 3]][1] = vm->core[vm->info[i].start + vm->info[i].index - 2 + ind++];
		vm->info[i].regs[vm->core[pos + 3]][2] = vm->core[vm->info[i].start + vm->info[i].index - 2 + ind++];
		vm->info[i].regs[vm->core[pos + 3]][3] = vm->core[vm->info[i].start + vm->info[i].index - 2 + ind++];
		ft_printf("lld indirect %hhx %hhx %hhx %hhx\n", vm->info[i].regs[vm->core[pos + 3]][0], vm->info[i].regs[vm->core[pos + 3]][1], vm->info[i].regs[vm->core[pos + 3]][2], vm->info[i].regs[vm->core[pos + 3]][3]);
		vm->info[i].carry++;
	}
	else
		ft_printf("ld Burn!\n");
		// burn cycle
	//read_acb(vm->info[i].body[vm->info[i].index + 1]);
	//ft_printf("ld called %i", vm->info[i].body[vm->info[i].index + 1]);
}
*/

void	vm_lld(t_vm *vm, int i)
{
	unsigned char	acb;
	unsigned char	*l1;
	unsigned char	*l2;

	vm->info[i].index += 2;
	acb = vm->core[ACB];
	if (!valid_acb(acb, 2, 1, 0) && !valid_acb(acb, 3, 1, 0))
	{
		ft_printf("Burn!\n");
		return ;
	}
	get_offset(vm, i, ACB1(acb), &l1);
	get_offset(vm, i, ACB2(acb), &l2);
	reg_copy(l2, l1);
	ft_printf("lld called: %0.2hhx%0.2hhx%0.2hhx%0.2hhx", l2[0], l2[1], l2[2], l2[3]);
	vm->info[i].carry = 1;
}

void	vm_lldi(t_vm *vm, int i)
{
	(void)vm;
	(void)i;
	ft_printf("lldi called");
}

void	vm_ldi(t_vm *vm, int i)
{
	(void)vm;
	(void)i;
	ft_printf("ldi called");
}

void	vm_ld(t_vm *vm, int i)
{
	unsigned char	acb;
	unsigned char	*l1;
	unsigned char	*l2;

	vm->info[i].index += 2;
	acb = vm->core[ACB];
	if (!valid_acb(acb, 2, 1, 0) && !valid_acb(acb, 3, 1, 0))
	{
		ft_printf("Burn!\n");
		return ;
	}
	get_offset(vm, i, ACB1(acb) | 0b100, &l1);
	get_offset(vm, i, ACB2(acb), &l2);
	reg_copy(l2, l1);
	ft_printf("ld called: %0.2hhx%0.2hhx%0.2hhx%0.2hhx", l2[0], l2[1], l2[2], l2[3]);
	vm->info[i].carry = 1;
}

void	vm_st(t_vm *vm, int i)
{
	unsigned char	acb;
	unsigned char	*l1;
	unsigned char	*l2;

	vm->info[i].index += 2;
	acb = vm->core[ACB];
	if (!valid_acb(acb, 1, 1, 0) && !valid_acb(acb, 1, 3, 0))
	{
		ft_printf("Burn!\n");
		return ;
	}
	get_offset(vm, i, ACB1(acb), &l1);
	get_offset(vm, i, ACB2(acb) | 0b100, &l2);
	reg_copy(l2, l1);
	ft_printf("st called: %0.2hhx%0.2hhx%0.2hhx%0.2hhx", l2[0], l2[1], l2[2], l2[3]);
}

/*
void	vm_ld(t_vm *vm, int i) // missing %idx_mod
{
	char	acb;
	int		pos;
	int		ind;

	pos = vm->info[i].index + 1;
	acb = vm->info[i].body[pos];
	if (valid_acb(acb, 2, 1, 0))
	{
		vm->info[i].index+=2;
		vm->info[i].regs[vm->core[pos + 5]][0] = vm->core[vm->info[i].start + vm->info[i].index++];
		vm->info[i].regs[vm->core[pos + 5]][1] = vm->core[vm->info[i].start + vm->info[i].index++];
		vm->info[i].regs[vm->core[pos + 5]][2] = vm->core[vm->info[i].start + vm->info[i].index++];
		vm->info[i].regs[vm->core[pos + 5]][3] = vm->core[vm->info[i].start + vm->info[i].index++];
		ft_printf("ld direct %hhx %hhx %hhx %hhx\n", vm->info[i].regs[vm->core[pos + 5]][0], vm->info[i].regs[vm->core[pos + 5]][1], vm->info[i].regs[vm->core[pos + 5]][2], vm->info[i].regs[vm->core[pos + 5]][3]);
		vm->info[i].carry++;
	}
	else if (valid_acb(acb, 3, 1, 0))
	{
		vm->info[i].index+=2;
		ind = (vm->core[vm->info[i].start + vm->info[i].index] * 256) + vm->core[vm->info[i].start + vm->info[i].index + 1];
		vm->info[i].regs[vm->core[pos + 3]][0] = vm->core[vm->info[i].start + vm->info[i].index - 2 + ind++];
		vm->info[i].regs[vm->core[pos + 3]][1] = vm->core[vm->info[i].start + vm->info[i].index - 2 + ind++];
		vm->info[i].regs[vm->core[pos + 3]][2] = vm->core[vm->info[i].start + vm->info[i].index - 2 + ind++];
		vm->info[i].regs[vm->core[pos + 3]][3] = vm->core[vm->info[i].start + vm->info[i].index - 2 + ind++];
		ft_printf("ld indirect %hhx %hhx %hhx %hhx\n", vm->info[i].regs[vm->core[pos + 3]][0], vm->info[i].regs[vm->core[pos + 3]][1], vm->info[i].regs[vm->core[pos + 3]][2], vm->info[i].regs[vm->core[pos + 3]][3]);
		vm->info[i].carry++;
	}
	else
		ft_printf("ld Burn!\n");
		// burn cycle
	//read_acb(vm->info[i].body[vm->info[i].index + 1]);
	//ft_printf("ld called %i", vm->info[i].body[vm->info[i].index + 1]);
}
*/
// 0290 0201
// 0290 02 0004

/*
void	vm_st(t_vm *vm, int i)
{
	char	acb;
	int		pos;
	int		ind;

	pos = vm->info[i].index + 1;
	acb = vm->info[i].body[pos];
	if (valid_acb(acb, 1, 1, 0))
	{
		vm->info[i].regs[vm->core[pos + 2]][0] = vm->info[i].regs[vm->core[pos + 1]][0];
		vm->info[i].regs[vm->core[pos + 2]][1] = vm->info[i].regs[vm->core[pos + 1]][1];
		vm->info[i].regs[vm->core[pos + 2]][2] = vm->info[i].regs[vm->core[pos + 1]][2];
		vm->info[i].regs[vm->core[pos + 2]][3] = vm->info[i].regs[vm->core[pos + 1]][3];
		ft_printf("st reg %hhx %hhx %hhx %hhx\n", vm->info[i].regs[vm->core[pos + 2]][0], vm->info[i].regs[vm->core[pos + 2]][1], vm->info[i].regs[vm->core[pos + 2]][2], vm->info[i].regs[vm->core[pos + 2]][3]);

	}
	else if (valid_acb(acb, 1, 3, 0))
	{
		vm->info[i].index+=2;
		ind = (vm->core[vm->info[i].start + vm->info[i].index] * 256) + vm->core[vm->info[i].start + vm->info[i].index + 1];
		vm->core[vm->info[i].start + vm->info[i].index - 2 + ind++] = vm->info[i].regs[vm->core[pos + 1]][0];
		vm->core[vm->info[i].start + vm->info[i].index - 2 + ind++] = vm->info[i].regs[vm->core[pos + 1]][1];
		vm->core[vm->info[i].start + vm->info[i].index - 2 + ind++] = vm->info[i].regs[vm->core[pos + 1]][2];
		vm->core[vm->info[i].start + vm->info[i].index - 2 + ind++] = vm->info[i].regs[vm->core[pos + 1]][3];
		ft_printf("st indirect %hhx %hhx %hhx %hhx\n", vm->core[vm->info[i].start + vm->info[i].index - 2 + ind - 4], vm->core[vm->info[i].start + vm->info[i].index - 2 + ind - 3], vm->core[vm->info[i].start + vm->info[i].index - 2 + ind - 2], vm->core[vm->info[i].start + vm->info[i].index - 2 + ind - 1]);
		// st
	}
	else
		ft_printf("st Burn!\n");
		// burn cycle
	//(void)vm;
	//(void)i;
	//ft_printf("st called");
}
*/
/*
void	vm_ld(t_vm *vm, int i)
{
	char acb[4];
	acb = read_acb(vm->info[i].body[vm->info[i].index + 1]);

	else
		ft_printf("Ignore, need to immplement this later");
	ft_printf("ld called %i", vm->info[i].body[vm->info[i].index + 1]);
}
*/
/*
void	vm_st(t_vm *vm, int i)
{
	(void)vm;
	(void)i;
	ft_printf("st called");
}
*/

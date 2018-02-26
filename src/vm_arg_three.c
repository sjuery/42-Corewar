/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_arg_three.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/02/25 20:24:01 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	vm_lld(t_vm *vm, int i)
{
	(void)vm;
	(void)i;
	ft_printf("lld called");
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
		ft_printf("%hhx %hhx %hhx %hhx\n", vm->info[i].regs[vm->core[pos + 5]][0], vm->info[i].regs[vm->core[pos + 5]][1], vm->info[i].regs[vm->core[pos + 5]][2], vm->info[i].regs[vm->core[pos + 5]][3]);
	}
	else if (valid_acb(acb, 3, 1, 0))
	{
		vm->info[i].index+=2;
		ind = (vm->core[vm->info[i].start + vm->info[i].index] * 256) + vm->core[vm->info[i].start + vm->info[i].index + 1];
		vm->info[i].regs[vm->core[pos + 3]][0] = vm->core[vm->info[i].start + vm->info[i].index - 2 + ind++];
		vm->info[i].regs[vm->core[pos + 3]][1] = vm->core[vm->info[i].start + vm->info[i].index - 2 + ind++];
		vm->info[i].regs[vm->core[pos + 3]][2] = vm->core[vm->info[i].start + vm->info[i].index - 2 + ind++];
		vm->info[i].regs[vm->core[pos + 3]][3] = vm->core[vm->info[i].start + vm->info[i].index - 2 + ind++];
		ft_printf("%hhx %hhx %hhx %hhx\n", vm->info[i].regs[vm->core[pos + 3]][0], vm->info[i].regs[vm->core[pos + 3]][1], vm->info[i].regs[vm->core[pos + 3]][2], vm->info[i].regs[vm->core[pos + 3]][3]);
	}
	else
		ft_printf("Burn!\n");
		// burn cycle
	//read_acb(vm->info[i].body[vm->info[i].index + 1]);
	//ft_printf("ld called %i", vm->info[i].body[vm->info[i].index + 1]);
}

// 0290 0201
// 0290 02 0004

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
		ft_printf("%hhx %hhx %hhx %hhx\n", vm->info[i].regs[vm->core[pos + 2]][0], vm->info[i].regs[vm->core[pos + 2]][1], vm->info[i].regs[vm->core[pos + 2]][2], vm->info[i].regs[vm->core[pos + 2]][3]);
	
	}
	else if (valid_acb(acb, 1, 3, 0))
	{
		vm->info[i].index+=2;
		ind = (vm->core[vm->info[i].start + vm->info[i].index] * 256) + vm->core[vm->info[i].start + vm->info[i].index + 1];
		vm->core[vm->info[i].start + vm->info[i].index - 2 + ind++] = vm->info[i].regs[vm->core[pos + 1]][0];
		vm->core[vm->info[i].start + vm->info[i].index - 2 + ind++] = vm->info[i].regs[vm->core[pos + 1]][1];
		vm->core[vm->info[i].start + vm->info[i].index - 2 + ind++] = vm->info[i].regs[vm->core[pos + 1]][2];
		vm->core[vm->info[i].start + vm->info[i].index - 2 + ind++] = vm->info[i].regs[vm->core[pos + 1]][3];
		ft_printf("%hhx %hhx %hhx %hhx\n", vm->core[vm->info[i].start + vm->info[i].index - 2 + ind - 4], vm->core[vm->info[i].start + vm->info[i].index - 2 + ind - 3], vm->core[vm->info[i].start + vm->info[i].index - 2 + ind - 2], vm->core[vm->info[i].start + vm->info[i].index - 2 + ind - 1]);
		// st
	}
	else
		ft_printf("Burn!\n");
		// burn cycle
	//(void)vm;
	//(void)i;
	//ft_printf("st called");
}
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

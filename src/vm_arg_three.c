/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_arg_three.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/02/23 17:37:33 by anazar           ###   ########.fr       */
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
	char acb[4];
	acb = read_acb(vm->info[i].body[vm->info[i].index + 1]);
	if (acb[0] == 2)
	{
		vm->info[i].index++;
		vm->info[i].reg[acb[1]][0] = vm->core[vm->info[i].start + vm->info[i].index++];
		vm->info[i].reg[acb[1]][1] = vm->core[vm->info[i].start + vm->info[i].index++];
		vm->info[i].reg[acb[1]][2] = vm->core[vm->info[i].start + vm->info[i].index++];
		vm->info[i].reg[acb[1]][3] = vm->core[vm->info[i].start + vm->info[i].index++];
	}
	else if (acb[0] == 3)
	{
		vm->info[i].index++;
		vm->info[i].reg[acb[1]][0] = vm->core[vm->info[i].start + vm->info[i].index++];
		vm->info[i].reg[acb[1]][1] = vm->core[vm->info[i].start + vm->info[i].index++];
	}
	else
		ft_printf("Ignore, need to immplement this later");
	ft_printf("ld called %i", vm->info[i].body[vm->info[i].index + 1]);
}

void	vm_st(t_vm *vm, int i)
{
	(void)vm;
	(void)i;
	ft_printf("st called");
}

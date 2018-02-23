/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_arg_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/02/07 17:43:29 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	vm_live(t_vm *vm, int i)
{
	vm->info[i].index += 5;
	if (vm->info[i].index > vm->info[i].head.prog_size) // double check, if index passes prog_size, we reduce to 0
		vm->info[i].index = 0;
	vm->info[i].live++;
	ft_printf("live called");
}

void	vm_zjmp(t_vm *vm, int i)
{
	(void)vm;
	(void)i;
	ft_printf("zjmp called");
}


void	vm_sti(t_vm *vm, int i)
{
	(void)vm;
	(void)i;
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
	(void)vm;
	(void)i;
	ft_printf("fork called");
}
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
	(void)vm;
	(void)i;
	ft_printf("add called");
}

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

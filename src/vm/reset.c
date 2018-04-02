/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <ihodge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/04/01 20:45:58 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "asm.h"

void	reset_alive_all(t_vm *vm)
{
	t_node	*tmp;

	tmp = vm->q->max_p;
	while (tmp)
	{
		if (!tmp->data->alive)
		{
			tmp->data->executing = 0;
			vis_unhighlight_process(vm, tmp->data);
		}
		tmp->data->alive = 0;
		tmp = tmp->next;
	}
	/*
	while (i < vm->process_count)
	{
		if (vm->info[i].alive == 0)
		{
			vm->info[i].executing = 0;
			vis_unhighlight_process(vm , i);
		}
		vm->info[i].alive = 0;
		i++;
	}*/
}
/*
void	reset_alive(t_vm *vm, int i)
{

	if (vm->info[i].alive == 0)
		vm->info[i].executing = 0;
	vm->info[i].alive = 0;
}*/

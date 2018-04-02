/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <ihodge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/04/02 16:22:38 by ihodge           ###   ########.fr       */
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
		ft_printf("rseting alive\n");
		if (!tmp->data->alive)
		{
			tmp->data->executing = 0;
			vis_unhighlight_process(vm, tmp->data);
		}
		tmp->data->alive = 0;
		tmp = tmp->next;
	}
}

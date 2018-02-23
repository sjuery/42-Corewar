/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bytes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/02/07 17:43:29 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	read_bytes(t_vm *vm, int i)
{
	while (++i < vm->process_count)
	{
		if (vm->info[i].alive == 1)
		{
			ft_printf("\nByte Read [%hhx] ", vm->info[i].body[0]);
			jumptable(vm->info[i].body[0], vm);
		}
	}
}


// ./corewar resources/champs/examples/zork.cor resources/champs/examples/bigzork.cor resources/champs/examples/helltrain.cor resources/champs/examples/turtle.cor
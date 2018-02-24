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

int		read_acb(int a)
{
	int ret;

	ret = 0;
	a += 226;
	while (a >= 2)
	{
		ret = ret * 10 + (a % 2);
		a = a / 2;
	}
	ret = ret * 10 + a;
	ft_printf("\nRET %i\n", ret);
	return (ret);
}

void	read_bytes(t_vm *vm, int i)
{
	while (++i < vm->process_count)
	{
		if (vm->info[i].alive == 1)
		{
			ft_printf("\nByte Read [%hhx] ", vm->info[i].body[vm->info[i].index]);
			jumptable(vm->info[i].body[vm->info[i].index], vm, i);
		}
	}
}


// ./corewar resources/champs/examples/zork.cor resources/champs/examples/bigzork.cor resources/champs/examples/helltrain.cor resources/champs/examples/turtle.cor
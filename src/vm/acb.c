/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by anazar            #+#    #+#             */
/*   Updated: 2018/04/08 15:32:04 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>
#include "asm.h"

int		valid_acb(int op, int acb, t_vm *vm, t_io *proc)
{
	int params;

	params = g_optab[op].params;
	if (params == 1)
		return (valid_acb1(acb, op));
	if (params == 2)
		return (valid_acb2(acb, op) & valid_register(vm, acb, op, proc));
	if (params == 3)
		return (valid_acb3(acb, op) & valid_register(vm, acb, op, proc));
	return (0);
}

int		valid_acb1(int acb, int op)
{
	if (g_optab[op].ptype[0] & ACB1(acb))
		return (1);
	return (0);
}

int		valid_acb2(int acb, int op)
{
	int	param1;
	int	param2;

	param1 = g_optab[op].ptype[0];
	param2 = g_optab[op].ptype[1];
	if (((ACB1(acb) <= param1) && param1 & ACB1(acb))
			&& (ACB2(acb) <= param2 && param2 & ACB2(acb)))
		return (1);
	return (0);
}

int		valid_acb3(int acb, int op)
{
	int	param1;
	int	param2;
	int	param3;

	param1 = g_optab[op].ptype[0];
	param2 = g_optab[op].ptype[1];
	param3 = g_optab[op].ptype[2];
	if ((ACB1(acb) <= param1 && param1 & ACB1(acb)) &&
			(ACB2(acb) <= param2 && param2 & ACB2(acb)) &&
			(ACB3(acb) <= param3 && param3 & ACB3(acb)))
		return (1);
	else if ((op == 9 || op == 13) &&
		(ACB1(acb) <= param1 && param1 & ACB1(acb))
			&& (ACB2(acb) <= param2 && param2 ^ ACB2(acb))
			&& (ACB3(acb) <= param3 && param3 & ACB3(acb)))
		return (1);
	else if (op == 10 && (ACB1(acb) <= param1 && param1 & ACB1(acb))
			&& (ACB2(acb) <= param2 && param2 & ACB2(acb))
			&& (ACB3(acb) <= param3 && param3 ^ ACB3(acb)))
		return (1);
	return (0);
}

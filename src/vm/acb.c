/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by anazar            #+#    #+#             */
/*   Updated: 2018/03/21 23:35:35 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int	get_offset(t_instr *instr, unsigned char acb, unsigned char **l)
{
	int	idx;

	*l = NULL;
	idx = ((acb & 0b100) != 0);
	acb = acb & 0b11;
	if (acb == 1)
	{
		instr->reg_index[instr->ri] = instr->vm->core[OFF1 + OFF2];
		if (REGI >= REG_NUMBER || REGI == 0)
			return (0);
		*l = instr->vm->info[instr->i].regs[instr->reg_index[instr->ri]];
		instr->vm->info[instr->i].index += 1;
		++instr->ri;
	}
	else if (acb == 2)
	{
		*l = &instr->vm->core[OFF1 + OFF2];
		instr->vm->info[instr->i].index += 4;
	}
	else if (acb == 3)
	{
		*l = &instr->vm->core[OFF1 + OPC + indirect(instr->vm, instr->i, idx)];
		instr->vm->info[instr->i].index += 2;
	}
	return (1);
}

int	get_offset_index(t_instr *instr, unsigned char acb, unsigned char **l)
{
	int	idx;

	*l = NULL;
	idx = ((acb & 0b100) != 0);
	acb = acb & 0b11;
	if (acb == 1)
	{
		instr->reg_index[instr->ri] = instr->vm->core[OFF1 + OFF2];
		if (REGI >= REG_NUMBER || REGI == 0)
			return (0);
		*l = instr->vm->info[instr->i].regs[instr->reg_index[instr->ri]];
		instr->vm->info[instr->i].index += 1;
		++instr->ri;
	}
	else if (acb == 2)
	{
		*l = &instr->vm->core[OFF1 + OFF2];
		instr->vm->info[instr->i].index += 2;
	}
	else if (acb == 3)
	{
		*l = &instr->vm->core[OFF1 + OPC + indirect(instr->vm, instr->i, idx)];
		instr->vm->info[instr->i].index += 2;
	}
	return (1);
}

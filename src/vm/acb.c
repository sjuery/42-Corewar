/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by anazar            #+#    #+#             */
/*   Updated: 2018/04/04 14:26:04 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	get_offset(t_instr *instr, unsigned char acb, unsigned char **l)
{
	int	idx;

	*l = NULL;
	idx = ((acb & 0b100) != 0);
	acb = acb & 0b11;
	if (acb == 1)
	{
		instr->reg_index[instr->ri] = instr->vm->core[(OFF2) % MEM_SIZE];
		*l = instr->proc->regs[instr->reg_index[instr->ri]];
		instr->core_index += 1;
		++instr->ri;
	}
	else if (acb == 2)
	{
		*l = &instr->vm->core[(OFF2) % MEM_SIZE];
		instr->core_index += 4;
	}
	else if (acb == 3)
	{
		*l = &instr->vm->core[OPC + indirect(instr->vm, idx, instr)];
		instr->core_index += 2;
	}
}

void	get_offset_index(t_instr *instr, unsigned char acb, unsigned char **l)
{
	int	idx;

	*l = NULL;
	idx = ((acb & 0b100) != 0);
	acb = acb & 0b11;
	if (acb == 1)
	{
		instr->reg_index[instr->ri] = instr->vm->core[OFF2];
		*l = instr->proc->regs[instr->reg_index[instr->ri]];
		instr->core_index += 1;
		++instr->ri;
	}
	else if (acb == 2)
	{
		*l = &instr->vm->core[OFF2];
		instr->core_index += 2;
	}
	else if (acb == 3)
	{
		*l = &instr->vm->core[OPC + indirect(instr->vm, idx, instr)];
		instr->core_index += 2;
	}
}

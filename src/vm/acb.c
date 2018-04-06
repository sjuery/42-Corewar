/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by anazar            #+#    #+#             */
/*   Updated: 2018/04/05 19:43:34 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

t_pos	set_reg(unsigned char *l1)
{
	t_pos	p;

	p.l0 = &l1[0];
	p.l1 = &l1[1];
	p.l2 = &l1[2];
	p.l3 = &l1[3];
	return (p);
}

t_pos	set_pos(t_instr *instr)
{
	t_pos p;

	p.l0 = &instr->vm->core[(OFF2) % MEM_SIZE];
	p.l1 = &instr->vm->core[(OFF2 + 1) % MEM_SIZE];
	p.l2 = &instr->vm->core[(OFF2 + 2) % MEM_SIZE];
	p.l3 = &instr->vm->core[(OFF2 + 3) % MEM_SIZE];
	return (p);
}

t_pos	set_ind(t_instr *instr)
{
	t_pos p;

	p.l0 = &instr->vm->core[(OPC + indirect(instr->vm, idx, instr)) % MEM_SIZE];
	p.l1 = &instr->vm->core[(OPC + 1 + indirect(instr->vm, idx, instr)) % MEM_SIZE];
	p.l2 = &instr->vm->core[(OPC + 2 + indirect(instr->vm, idx, instr)) % MEM_SIZE];
	p.l3 = &instr->vm->core[(OPC + 3 + indirect(instr->vm, idx, instr)) % MEM_SIZE];
	return (p);
}

void	get_offset(t_instr *instr, unsigned char acb, t_pos *l)
{
	int	idx;

	*l = NULL;
	idx = ((acb & 0b100) != 0);
	acb = acb & 0b11;
	if (acb == 1)
	{
		instr->reg_index[instr->ri] = instr->vm->core[(OFF2) % MEM_SIZE];
		*l = set_reg(instr->proc->regs[instr->reg_index[instr->ri]]);
		instr->core_index += 1;
		++instr->ri;
	}
	else if (acb == 2)
	{
		*l = set_pos(instr);
		instr->core_index += 4;
	}
	else if (acb == 3)
	{
		*l = set_ind(instr);
		instr->core_index += 2;
	}
}

void	get_offset_index(t_instr *instr, unsigned char acb, t_pos *l)
{
	int	idx;

	*l = NULL;
	idx = ((acb & 0b100) != 0);
	acb = acb & 0b11;
	if (acb == 1)
	{
		instr->reg_index[instr->ri] = instr->vm->core[(OFF2) % MEM_SIZE];
		*l = set_reg(instr->proc->regs[instr->reg_index[instr->ri]]);
		instr->core_index += 1;
		++instr->ri;
	}
	else if (acb == 2)
	{
		*l = set_pos(instr);
		instr->core_index += 2;
	}
	else if (acb == 3)
	{
		*l = set_ind(instr);
		instr->core_index += 2;
	}
}

/*
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
		*l = &instr->vm->core[OFF2 % MEM_SIZE];
		instr->core_index += 2;
	}
	else if (acb == 3)
	{
		*l = &instr->vm->core[OPC + indirect(instr->vm, idx, instr)];
		instr->core_index += 2;
	}
}
*/

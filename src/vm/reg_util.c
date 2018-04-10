/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reg_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 16:43:45 by anazar            #+#    #+#             */
/*   Updated: 2018/04/05 15:24:05 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>
#include "asm.h"

void	into_reg(unsigned int val, unsigned char *reg)
{
	reg[3] = val & 0xFF;
	reg[2] = (val >> 8) & 0xFF;
	reg[1] = (val >> 16) & 0xFF;
	reg[0] = (val >> 24) & 0xFF;
}

void	play_spawn(t_vm *vm)
{
	if (vm->f.noise == 0 && (vm->f.s == 1 || vm->f.s == 3))
	{
		system("afplay ./sound/spawn.wav &");
		vm->f.noise++;
	}
}

int		valid_reg_num(int reg_offset, t_vm *vm, t_io *proc)
{
	int reg;

	reg = vm->core[(PARAM1 + reg_offset) % MEM_SIZE];
	if (reg >= 1 && reg <= 16)
		return (1);
	return (0);
}

void	add_to_reg_offset(int *reg_offset, int acb, int op)
{
	*reg_offset += 2;
	if (acb == 2 && !g_optab[op].index)
		*reg_offset += 2;
}

int		valid_register(t_vm *vm, int acb, int op, t_io *proc)
{
	int	reg_offset;

	reg_offset = 2;
	if (ACB1(acb) == 1)
	{
		if (valid_reg_num(reg_offset, vm, proc))
			reg_offset++;
		else
			return (0);
	}
	else
		add_to_reg_offset(&reg_offset, ACB1(acb), op);
	if (ACB2(acb) == 1)
	{
		if (valid_reg_num(reg_offset, vm, proc))
			reg_offset++;
		else
			return (0);
	}
	else
		add_to_reg_offset(&reg_offset, ACB2(acb), op);
	if (g_optab[op].params == 3 && ACB3(acb) == 1)
		return (valid_reg_num(reg_offset, vm, proc) ? 1 : 0);
	return (1);
}

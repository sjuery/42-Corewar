/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 17:46:56 by anazar            #+#    #+#             */
/*   Updated: 2018/04/09 15:46:09 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

char	read_core1(t_vm *vm, unsigned int pos)
{
	return (vm->core[pos % MEM_SIZE]);
}

short	read_core2(t_vm *vm, unsigned int pos)
{
	return (((short)vm->core[pos % MEM_SIZE] << 8) |
		((short)vm->core[(pos + 1) % MEM_SIZE]));
}

int		read_core4(t_vm *vm, unsigned int pos)
{
	return ((int)(((unsigned int)vm->core[pos % MEM_SIZE] << 24) |
		((unsigned int)vm->core[(pos + 1) % MEM_SIZE] << 16) |
		((unsigned int)vm->core[(pos + 2) % MEM_SIZE] << 8) |
		(unsigned int)vm->core[(pos + 3) % MEM_SIZE]));
}

int		read_reg(t_io *proc, int reg_num)
{
	return ((int)(VAL(proc->regs[reg_num])));
}

short	read_reg2(t_io *proc, int reg_num)
{
	return (((unsigned int)proc->regs[reg_num][3]) |
		((unsigned int)proc->regs[reg_num][2] << 8));
}

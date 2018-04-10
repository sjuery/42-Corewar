/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 17:46:56 by anazar            #+#    #+#             */
/*   Updated: 2018/04/09 15:46:09 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	write_reg(t_io *proc, int reg_num, int value)
{
	proc->regs[reg_num][0] = (value >> 24) % 0x100;
	proc->regs[reg_num][1] = (value >> 16) % 0x100;
	proc->regs[reg_num][2] = (value >> 8) % 0x100;
	proc->regs[reg_num][3] = value % 0x100;
}

void	write_core(t_vm *vm, unsigned int pos, int value)
{
	vm->core[pos % MEM_SIZE] = (value >> 24) % 0x100;
	vm->core[(pos + 1) % MEM_SIZE] = (value >> 16) % 0x100;
	vm->core[(pos + 2) % MEM_SIZE] = (value >> 8) % 0x100;
	vm->core[(pos + 3) % MEM_SIZE] = value % 0x100;
}

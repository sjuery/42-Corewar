/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reg_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 16:43:45 by anazar            #+#    #+#             */
/*   Updated: 2018/03/31 15:20:58 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	into_reg(unsigned int val, unsigned char *reg)
{
	reg[3] = val & 0xFF;
	reg[2] = (val >> 8) & 0xFF;
	reg[1] = (val >> 16) & 0xFF;
	reg[0] = (val >> 24) & 0xFF;
}

//t_instr	init_instr(t_vm *vm, t_io *proc)
t_instr	init_instr(t_vm *vm, int i)
{
	t_instr	n;

	n.l1 = NULL;
	n.l2 = NULL;
	n.l3 = NULL;
	n.s = NULL;
	n.vm = vm;
	//n.proc = proc
	n.i = i;//not needed
	n.acb = vm->core[PARAM2];
	n.opcode_pos = VAL(PC);
	n.reg_index[0] = 0;
	n.reg_index[1] = 0;
	n.reg_index[2] = 0;
	n.ri = 0;
	n.core_index = VAL(PC);
	return (n);
}

int		print_reg(unsigned char *l)
{
	return (VAL(l));
}

void	copy_io(t_vm *vm, int dest, int src)//this might be a problem
{
	ft_memcpy(&vm->info[dest], &vm->info[src], sizeof(t_io));
}

void	reg_copy(unsigned char *dest, unsigned char *src)
{
	dest[0] = src[0];
	dest[1] = src[1];
	dest[2] = src[2];
	dest[3] = src[3];
}

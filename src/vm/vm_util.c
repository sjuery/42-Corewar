/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/03/27 15:06:08 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int		indirect(t_vm *vm, int i, unsigned char opcode, t_instr *instr)
{
	if (opcode)
		return ((vm->core[vm->info[i].start + OFF2] * 0x100 +
				vm->core[vm->info[i].start + OFF2 + 1]) % IDX_MOD);
	else
		return (vm->core[vm->info[i].start + OFF2] * 0x100 +
				vm->core[vm->info[i].start + OFF2 + 1]);
}

int		get_index_one(unsigned char *l)
{
	short val;

	val = l[1] + (l[0] << 8);
	return (val);
}

int		get_index_two(t_instr instr)
{
	int	out1;
	int	out2;

	out1 = 0;
	out2 = 0;
	if (ACB1(instr.acb) == 1)
		out1 = VAL3(instr.l1);
	else if (ACB1(instr.acb) == 2)
		out1 = VAL2(instr.l1);
	else if (ACB1(instr.acb) == 3)
		out1 = VAL(instr.l1);
	if (ACB2(instr.acb) == 1)
		out2 = VAL3(instr.l2);
	else if (ACB2(instr.acb) == 2)
		out2 = VAL2(instr.l2);
	//ft_printf("%i\n", out1 + out2 );
	return (out1 + out2);
}

void	vm_lfork(t_vm *vm, int i)
{
	int			j;
	t_instr		instr;

	instr = init_instr(vm, i);
	instr.acb = 0;
	instr.core_index++;
	vm->info[i].index++;
	j = vm->process_count;
	while (vm->info[j].executing)
		++j;
	vm->process_count++;
	if (!get_offset_index(&instr, 2, &instr.l1))
		return ;
	copy_io(vm, j, i);
	vm->info[j].start = vm->info[i].start + instr.opcode_pos +
	(instr.l1[1] << 8 | instr.l1[0]);
	vm->info[j].carry = 0;
	vm->info[j].wait_cycle = 0;
	vm->info[j].waiting = 0;
	vm->info[j].index = 0;
	vm->info[i].index += 3;
}

void	vm_fork(t_vm *vm, int i)
{
	int			j;
	t_instr		instr;

	instr = init_instr(vm, i);
	instr.acb = 0;
	instr.core_index++;
	vm->info[i].index++;
	j = vm->process_count;
	while (vm->info[j].executing)
		++j;
	vm->process_count++;
	if (!get_offset_index(&instr, 2, &instr.l1))
		return ;
	copy_io(vm, j, i);
	vm->info[j].start = (vm->info[i].start + instr.opcode_pos +
		(instr.l1[0] << 8 | instr.l1[1]) % IDX_MOD) % 4096;
	vm->info[j].carry = 0;
	vm->info[j].wait_cycle = 0;
	vm->info[j].waiting = 0;
	vm->info[j].index = 0;
	vm->info[i].index += 1;
}

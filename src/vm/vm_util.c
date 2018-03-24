/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/03/23 23:03:23 by ihodge           ###   ########.fr       */
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
	return (VAL2(l) & 0xFFFF);
}

int		get_index_two(unsigned char *l1, unsigned char *l2)
{
	unsigned char l3[4];

	reg_add(l1, l2, l3);
	return (VAL2(l3));
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
	//ft_printf("fork [%i]\n", ((instr.l1[0] << 8 | instr.l1[1]) % IDX_MOD) % 4096);
	//ft_printf("fork start at [%i]\n", vm->info[j].start);
	vm->info[j].wait_cycle = 0;
	vm->info[j].index = 0;
	vm->info[i].index += 1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/03/21 21:49:32 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	vm_st(t_vm *vm, int i)
{
	t_instr		instr;

	instr = init_instr(vm, i);
	vm->info[i].index += 2;
	if (!valid_acb(instr, 1, 1, 0) && !valid_acb(instr, 1, 3, 0))
		return ;
	if (!get_offset(&instr, ACB1(instr.acb), &instr.l1) ||
	!get_offset(&instr, ACB2(instr.acb) | 0b100, &instr.l2))
		return ;
	if (ACB2(instr.acb) == 1)
		instr.l2 = &vm->core[vm->info[i].start +
			instr.opcode_pos + VAL(instr.l2) % 4096];
	reg_copy(instr.l2, instr.l1);
	vis_copy(&vm->vis[vm->info[i].start + instr.opcode_pos +
		VAL(instr.l2)], instr.l1, vm, i);
	vis_update(vm, vm->info[i].start + instr.opcode_pos + VAL(instr.l2));
}

void	vm_sti(t_vm *vm, int i)
{
	t_instr		instr;

	instr = init_instr(vm, i);
	vm->info[i].index += 2;
	if (ACB1(instr.acb) != 1)
		return ;
	if (!get_offset_index(&instr, ACB1(instr.acb), &instr.l1) ||
		!get_offset_index(&instr, ACB2(instr.acb), &instr.l2) ||
		!get_offset_index(&instr, ACB3(instr.acb), &instr.l3))
		return ;
	instr.index = ((VAL2(instr.l2) + VAL2(instr.l3)) & 0xFFFF) % IDX_MOD;
	reg_copy(&vm->core[vm->info[i].start + instr.opcode_pos + instr.index],
		instr.l1);
	vis_copy(&vm->vis[vm->info[i].start + instr.opcode_pos + instr.index],
		instr.l1, vm, i);
	vis_update(vm, vm->info[i].start + instr.opcode_pos + instr.index);
}

void	vm_zjmp(t_vm *vm, int i)
{
	t_instr instr;

	instr = init_instr(vm, i);
	instr.acb = 0;
	if (!vm->info[i].carry)
	{
		vm->info[i].index += 3;
		return ;
	}
	vm->info[i].index += get_index_one(&vm->core[vm->info[i].start +
		vm->info[i].index + 1]);
	vm->info[i].carry = 0;
}

void	vm_live(t_vm *vm, int i)
{
	vm->live++;
	vm->info[i].index += 1;
	vm->info[i].index += 4;
	vm->info[i].live++;
	vm->info[i].alive = 1;
}

void	vm_aff(t_vm *vm, int i)
{
	t_instr		instr;

	instr = init_instr(vm, i);
	vm->info[i].index += 1;
	if (!valid_acb(instr, 1, 0, 0))
		return ;
	if (!get_offset(&instr, ACB1(instr.acb), &instr.l1))
		return ;
}

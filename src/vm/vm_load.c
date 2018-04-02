/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/04/01 20:47:46 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	vm_lld(t_vm *vm, t_io *proc)
{
	t_instr		instr;

	instr = init_instr(vm, proc);
	instr.core_index += 2;
	get_offset(&instr, ACB1(instr.acb), &instr.l1);
	get_offset(&instr, ACB2(instr.acb), &instr.l2);
	into_reg(instr.core_index, PC);
	reg_copy(instr.l2, instr.l1);
	modify_carry(proc, instr.l2);
}

void	vm_lldi(t_vm *vm, t_io *proc)
{
	t_instr		instr;

	instr = init_instr(vm, proc);
	instr.core_index += 2;
	get_offset_index(&instr, ACB1(instr.acb), &instr.l1);
	get_offset_index(&instr, ACB2(instr.acb), &instr.l2);
	get_offset_index(&instr, ACB3(instr.acb), &instr.l3);
	into_reg(instr.core_index, PC);
	instr.s = &vm->core[(instr.opcode_pos
		+ get_index_two(instr)) % MEM_SIZE];
	reg_copy(instr.l3, instr.s);
	modify_carry(proc, instr.l3);
}

void	vm_ldi(t_vm *vm, t_io *proc)
{
	t_instr		instr;

	instr = init_instr(vm, proc);
	instr.core_index += 2;
	get_offset_index(&instr, ACB1(instr.acb) | 0b100, &instr.l1);
	get_offset_index(&instr, ACB2(instr.acb), &instr.l2);
	get_offset_index(&instr, ACB3(instr.acb), &instr.l3);
	into_reg(instr.core_index, PC);
	instr.s = &vm->core[(instr.opcode_pos
		+ get_index_two(instr)) % IDX_MOD];
	reg_copy(instr.l3, instr.s);
}

void	vm_ld(t_vm *vm, t_io *proc)
{
	t_instr		instr;

	instr = init_instr(vm, proc);
	instr.core_index += 2;
	get_offset(&instr, ACB1(instr.acb) | 0b100, &instr.l1);
	get_offset(&instr, ACB2(instr.acb), &instr.l2);
	into_reg(instr.core_index, PC);
	reg_copy(instr.l2, instr.l1);
	modify_carry(proc, instr.l2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by anazar            #+#    #+#             */
/*   Updated: 2018/04/01 19:16:32 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	vm_or(t_vm *vm, t_io *proc)
{
	t_instr			instr;

	instr = init_instr(vm, proc);
	instr.core_index += 2;
	get_offset(&instr, ACB1(instr.acb), &instr.l1);
	get_offset(&instr, ACB2(instr.acb), &instr.l2);
	get_offset(&instr, ACB3(instr.acb), &instr.l3);
	into_reg(instr.core_index, PC);
	reg_or(instr.l1, instr.l2, instr.l3);
	modify_carry(vm, proc, instr.l3);
}

void	vm_xor(t_vm *vm, t_io *proc)
{
	t_instr			instr;

	instr = init_instr(vm, proc);
	instr.core_index += 2;
	get_offset(&instr, ACB1(instr.acb), &instr.l1);
	get_offset(&instr, ACB2(instr.acb), &instr.l2);
	get_offset(&instr, ACB3(instr.acb), &instr.l3);
	into_reg(instr.core_index, PC);
	reg_xor(instr.l1, instr.l2, instr.l3);
	modify_carry(vm, proc, instr.l3);
}

void	vm_and(t_vm *vm, t_io *proc)
{
	t_instr			instr;

	instr = init_instr(vm, proc);
	instr.core_index += 2;
	get_offset(&instr, ACB1(instr.acb), &instr.l1);
	get_offset(&instr, ACB2(instr.acb), &instr.l2);
	get_offset(&instr, ACB3(instr.acb), &instr.l3);
	into_reg(instr.core_index, PC);
	reg_and(instr.l1, instr.l2, instr.l3);
	modify_carry(vm, proc, instr.l3);
}

void	vm_sub(t_vm *vm, t_io *proc)
{
	t_instr			instr;

	instr = init_instr(vm, proc);
	instr.core_index += 2;
	get_offset(&instr, ACB1(instr.acb), &instr.l1);
	get_offset(&instr, ACB2(instr.acb), &instr.l2);
	get_offset(&instr, ACB3(instr.acb), &instr.l3);
	into_reg(instr.core_index, PC);
	reg_sub(instr.l1, instr.l2, instr.l3);
	modify_carry(vm, proc, instr.l3);
}

void	vm_add(t_vm *vm, t_io *proc)
{
	t_instr			instr;

	instr = init_instr(vm, proc);
	instr.core_index += 2;
	get_offset(&instr, ACB1(instr.acb), &instr.l1);
	get_offset(&instr, ACB2(instr.acb), &instr.l2);
	get_offset(&instr, ACB3(instr.acb), &instr.l3);
	into_reg(instr.core_index, PC);
	reg_add(instr.l1, instr.l2, instr.l3);
	modify_carry(vm, proc, instr.l3);
}

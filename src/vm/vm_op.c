/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by anazar            #+#    #+#             */
/*   Updated: 2018/03/23 12:39:26 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	vm_or(t_vm *vm, int i)
{
	t_instr			instr;

	instr = init_instr(vm, i);
	instr.core_index += 2;
	vm->info[i].index++;
	if (!valid_acb3(instr, 6))
		return ;
	if (!get_offset(&instr, ACB1(instr.acb), &instr.l1) ||
		!get_offset(&instr, ACB2(instr.acb), &instr.l2) ||
		!get_offset(&instr, ACB3(instr.acb), &instr.l3))
		return ;
	vm->info[i].index = instr.core_index;
	reg_or(instr.l1, instr.l2, instr.l3);
}

void	vm_xor(t_vm *vm, int i)
{
	t_instr			instr;

	instr = init_instr(vm, i);
	instr.core_index += 2;
	vm->info[i].index++;
	if (!valid_acb3(instr, 7))
		return ;
	if (!get_offset(&instr, ACB1(instr.acb), &instr.l1) ||
		!get_offset(&instr, ACB2(instr.acb), &instr.l2) ||
		!get_offset(&instr, ACB3(instr.acb), &instr.l3))
		return ;
	vm->info[i].index = instr.core_index;
	reg_xor(instr.l1, instr.l2, instr.l3);
}

void	vm_and(t_vm *vm, int i)
{
	t_instr			instr;

	instr = init_instr(vm, i);
	instr.core_index += 2;
	vm->info[i].index++;
	if (!valid_acb3(instr, 5))
		return ;
	if (!get_offset(&instr, ACB1(instr.acb), &instr.l1) ||
		!get_offset(&instr, ACB2(instr.acb), &instr.l2) ||
		!get_offset(&instr, ACB3(instr.acb), &instr.l3))
		return ;
	vm->info[i].index = instr.core_index;
	reg_and(instr.l1, instr.l2, instr.l3);
}

void	vm_sub(t_vm *vm, int i)
{
	t_instr			instr;

	instr = init_instr(vm, i);
	instr.core_index += 2;
	vm->info[i].index++;
	if (!valid_acb3(instr, 4))
		return ;
	if (!get_offset(&instr, ACB1(instr.acb), &instr.l1) ||
		!get_offset(&instr, ACB2(instr.acb), &instr.l2) ||
		!get_offset(&instr, ACB3(instr.acb), &instr.l3))
		return ;
	vm->info[i].index = instr.core_index;
	reg_sub(instr.l1, instr.l2, instr.l3);
}

void	vm_add(t_vm *vm, int i)
{
	t_instr			instr;

	instr = init_instr(vm, i);
	instr.core_index += 2;
	vm->info[i].index++;
	if (!valid_acb3(instr, 3))
		return ;
	if (!get_offset(&instr, ACB1(instr.acb), &instr.l1) ||
		!get_offset(&instr, ACB2(instr.acb), &instr.l2) ||
		!get_offset(&instr, ACB3(instr.acb), &instr.l3))
		return ;
	vm->info[i].index = instr.core_index;
	reg_add(instr.l1, instr.l2, instr.l3);
}

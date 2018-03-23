/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by anazar            #+#    #+#             */
/*   Updated: 2018/03/21 23:35:35 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	vm_or(t_vm *vm, int i)
{
	t_instr			instr;

	instr = init_instr(vm, i);
	vm->info[i].index += 2;
	if (!valid_acb(instr, 1, 1, 1))
		return ;
	if (!get_offset(&instr, ACB1(instr.acb), &instr.l1) ||
		!get_offset(&instr, ACB2(instr.acb), &instr.l2) ||
		!get_offset(&instr, ACB3(instr.acb), &instr.l3))
		return ;
	reg_or(instr.l1, instr.l2, instr.l3);
}

void	vm_xor(t_vm *vm, int i)
{
	t_instr			instr;

	instr = init_instr(vm, i);
	vm->info[i].index += 2;
	if (!valid_acb(instr, 1, 1, 1))
		return ;
	if (!get_offset(&instr, ACB1(instr.acb), &instr.l1) ||
		!get_offset(&instr, ACB2(instr.acb), &instr.l2) ||
		!get_offset(&instr, ACB3(instr.acb), &instr.l3))
		return ;
	reg_xor(instr.l1, instr.l2, instr.l3);
}

void	vm_and(t_vm *vm, int i)
{
	t_instr			instr;

	instr = init_instr(vm, i);
	vm->info[i].index += 2;
	if (!valid_acb(instr, 1, 1, 1))
		return ;
	if (!get_offset(&instr, ACB1(instr.acb), &instr.l1) ||
		!get_offset(&instr, ACB2(instr.acb), &instr.l2) ||
		!get_offset(&instr, ACB3(instr.acb), &instr.l3))
		return ;
	reg_and(instr.l1, instr.l2, instr.l3);
}

void	vm_sub(t_vm *vm, int i)
{
	t_instr			instr;

	instr = init_instr(vm, i);
	vm->info[i].index += 2;
	if (!valid_acb(instr, 1, 1, 1))
		return ;
	if (!get_offset(&instr, ACB1(instr.acb), &instr.l1) ||
		!get_offset(&instr, ACB2(instr.acb), &instr.l2) ||
		!get_offset(&instr, ACB3(instr.acb), &instr.l3))
		return ;
	reg_sub(instr.l1, instr.l2, instr.l3);
}

void	vm_add(t_vm *vm, int i)
{
	t_instr			instr;

	instr = init_instr(vm, i);
	vm->info[i].index += 2;
	if (!valid_acb(instr, 1, 1, 1))
		return ;
	if (!get_offset(&instr, ACB1(instr.acb), &instr.l1) ||
		!get_offset(&instr, ACB2(instr.acb), &instr.l2) ||
		!get_offset(&instr, ACB3(instr.acb), &instr.l3))
		return ;
	reg_add(instr.l1, instr.l2, instr.l3);
}

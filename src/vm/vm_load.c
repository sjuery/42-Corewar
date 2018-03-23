/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/03/23 16:27:30 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	vm_lld(t_vm *vm, int i)
{
	t_instr		instr;

	instr = init_instr(vm, i);
	instr.core_index += 2;
	vm->info[i].index++;
	if (!valid_acb2(instr, 12))
		return ;
	if (!get_offset(&instr, ACB1(instr.acb), &instr.l1) ||
		!get_offset(&instr, ACB2(instr.acb), &instr.l2))
		return ;
	vm->info[i].index = instr.core_index;
	reg_copy(instr.l2, instr.l1);
	vm->info[i].carry = 1;
}

void	vm_lldi(t_vm *vm, int i)
{
	t_instr		instr;

	instr = init_instr(vm, i);
	instr.core_index += 2;
	vm->info[i].index++;
	if (!valid_acb3(instr, 13))
		return ;
	if (!get_offset_index(&instr, ACB1(instr.acb), &instr.l1) ||
		!get_offset_index(&instr, ACB2(instr.acb), &instr.l2) ||
		!get_offset_index(&instr, ACB3(instr.acb), &instr.l3))
		return ;
	vm->info[i].index = instr.core_index;
	instr.s = &vm->core[(vm->info[i].start + vm->info[i].index
		+ get_index_two(instr.l1, instr.l2)) % 4096];
	reg_copy(instr.l3, instr.s);
	vm->info[i].carry = 1;
}

void	vm_ldi(t_vm *vm, int i)
{
	t_instr		instr;

	instr = init_instr(vm, i);
	instr.core_index += 2;
	vm->info[i].index++;
	if(!valid_acb3(instr, 9))
		return ;
	if (!get_offset_index(&instr, ACB1(instr.acb) | 0b100, &instr.l1) ||
		!get_offset_index(&instr, ACB2(instr.acb), &instr.l2) ||
		!get_offset_index(&instr, ACB3(instr.acb), &instr.l3))
		return ;
	vm->info[i].index = instr.core_index;
	instr.s = &vm->core[(vm->info[i].start + vm->info[i].index
		+ get_index_two(instr.l1, instr.l2)) % 4096];
	reg_copy(instr.l3, instr.s);
	vm->info[i].carry = 1;//this might actually NOT modify the carry
}

void	vm_ld(t_vm *vm, int i)
{
	t_instr		instr;

	instr = init_instr(vm, i);
	instr.core_index += 2;
	vm->info[i].index++;
	if(!valid_acb2(instr, 1))
		return ;
	if (!get_offset(&instr, ACB1(instr.acb) | 0b100, &instr.l1) ||
		!get_offset(&instr, ACB2(instr.acb), &instr.l2))
		return ;
	vm->info[i].index = instr.core_index;
	reg_copy(instr.l2, instr.l1);
	vm->info[i].carry = 1;
}

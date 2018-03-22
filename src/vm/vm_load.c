/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_loads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/03/21 21:49:32 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	vm_lld(t_vm *vm, int i)
{
	t_instr		instr;

	instr = init_instr(vm, i);
	vm->info[i].index += 2;
	if (!valid_acb(instr, 2, 1, 0) && !valid_acb(instr, 3, 1, 0))
		return ;
	if (!get_offset(&instr, ACB1(instr.acb), &instr.l1) ||
		!get_offset(&instr, ACB2(instr.acb), &instr.l2))
		return ;
	reg_copy(instr.l2, instr.l1);
	vm->info[i].carry = 1;
}

void	vm_lldi(t_vm *vm, int i)
{
	t_instr		instr;

	instr = init_instr(vm, i);
	vm->info[i].index += 2;
	if (ACB2(instr.acb) == 3 || ACB3(instr.acb) != 1)
		return ;
	if (!get_offset_index(&instr, ACB1(instr.acb), &instr.l1) ||
		!get_offset_index(&instr, ACB2(instr.acb), &instr.l2) ||
		!get_offset_index(&instr, ACB3(instr.acb), &instr.l3))
		return ;
	instr.s = &vm->core[(vm->info[i].start + vm->info[i].index
		+ get_index_two(instr.l1, instr.l2)) % 4096];
	reg_copy(instr.l3, instr.s);
	vm->info[i].carry = 1;
	ft_printf("\n");
}

void	vm_ldi(t_vm *vm, int i)
{
	t_instr		instr;

	instr = init_instr(vm, i);
	vm->info[i].index += 2;
	if (ACB2(instr.acb) == 3 || ACB3(instr.acb) != 1)
		return ;
	if (!get_offset_index(&instr, ACB1(instr.acb) | 0b100, &instr.l1) ||
		!get_offset_index(&instr, ACB2(instr.acb), &instr.l2) ||
		!get_offset_index(&instr, ACB3(instr.acb), &instr.l3))
		return ;
	instr.s = &vm->core[(vm->info[i].start + vm->info[i].index
		+ get_index_two(instr.l1, instr.l2)) % 4096];
	reg_copy(instr.l3, instr.s);
	vm->info[i].carry = 1;
}

void	vm_ld(t_vm *vm, int i)
{
	t_instr		instr;

	instr = init_instr(vm, i);
	vm->info[i].index += 2;
	if (!valid_acb(instr, 2, 1, 0) && !valid_acb(instr, 3, 1, 0))
		return ;
	if (!get_offset(&instr, ACB1(instr.acb) | 0b100, &instr.l1) ||
		!get_offset(&instr, ACB2(instr.acb), &instr.l2))
		return ;
	reg_copy(instr.l2, instr.l1);
	vm->info[i].carry = 1;
}

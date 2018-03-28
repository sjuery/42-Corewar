/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/03/27 22:08:50 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	vm_lld(t_vm *vm, int i)
{
	t_instr		instr;

	instr = init_instr(vm, i);
	instr.core_index += 2;
	vm->info[i].index++;
	get_offset(&instr, ACB1(instr.acb), &instr.l1);
	get_offset(&instr, ACB2(instr.acb), &instr.l2);
	vm->info[i].index = instr.core_index;
	reg_copy(instr.l2, instr.l1);
	modify_carry(vm, i, instr.l2);
}

void	vm_lldi(t_vm *vm, int i)
{
	t_instr		instr;

	instr = init_instr(vm, i);
	instr.core_index += 2;
	vm->info[i].index++;
	get_offset_index(&instr, ACB1(instr.acb), &instr.l1);
	get_offset_index(&instr, ACB2(instr.acb), &instr.l2);
	get_offset_index(&instr, ACB3(instr.acb), &instr.l3);
	vm->info[i].index = instr.core_index;
	instr.s = &vm->core[(vm->info[i].start + instr.opcode_pos
		+ get_index_two(instr)) % MEM_SIZE];
	reg_copy(instr.l3, instr.s);
	modify_carry(vm, i, instr.l3);
}

void	vm_ldi(t_vm *vm, int i)
{
	t_instr		instr;

	instr = init_instr(vm, i);
	instr.core_index += 2;
	vm->info[i].index++;
	get_offset_index(&instr, ACB1(instr.acb) | 0b100, &instr.l1);
	get_offset_index(&instr, ACB2(instr.acb), &instr.l2);
	get_offset_index(&instr, ACB3(instr.acb), &instr.l3);
	vm->info[i].index = instr.core_index;
	//ft_printf("%i\n", VAL(instr.l1));
	//ft_printf("%i\n", VAL2(instr.l2));
	//instr.s = &vm->core[(vm->info[i].start + vm->info[i].index
	instr.s = &vm->core[(vm->info[i].start + instr.opcode_pos
		+ get_index_two(instr)) % IDX_MOD];
	reg_copy(instr.l3, instr.s);
}

void	vm_ld(t_vm *vm, int i)
{
	t_instr		instr;

	instr = init_instr(vm, i);
	instr.core_index += 2;
	vm->info[i].index++;
	get_offset(&instr, ACB1(instr.acb) | 0b100, &instr.l1);
	get_offset(&instr, ACB2(instr.acb), &instr.l2);
	//ft_printf("ld called; cycle[%i]\n", vm->cycles);
	vm->info[i].index = instr.core_index;
	reg_copy(instr.l2, instr.l1);
	modify_carry(vm, i, instr.l2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/04/08 23:59:45 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	vm_lld(t_vm *vm, t_io *proc)
{
	/*
	t_instr		instr;

	instr = init_instr(vm, proc);
	instr.core_index += 2;
	get_offset(&instr, ACB1(instr.acb), &instr.l1);
	get_offset(&instr, ACB2(instr.acb), &instr.l2);
	into_reg(instr.core_index, PC);
	reg_copy(instr.l2, instr.l1, 0);
	modify_carry(proc, instr.l2);
	*/
	int	value;
	int	acb;

	write_reg(proc, 0, read_reg(proc, 0) + 1);
	acb = read_core1(vm, read_reg(proc, 0));
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	value = read_value(vm, proc, ACB1(acb), 0);
	write_reg(proc, read_core1(vm, read_reg(proc, 0)), value);
	modify_carry2(proc, read_reg(proc, read_core1(vm, read_reg(proc, 0))));
	write_reg(proc, 0, read_reg(proc, 0) + 1);
}

void	vm_lldi(t_vm *vm, t_io *proc)
{
	/*
	t_instr		instr;

	instr = init_instr(vm, proc);
	instr.core_index += 2;
	get_offset_index(&instr, ACB1(instr.acb), &instr.l1);
	get_offset_index(&instr, ACB2(instr.acb), &instr.l2);
	get_offset_index(&instr, ACB3(instr.acb), &instr.l3);
	into_reg(instr.core_index, PC);
	instr.s = &vm->core[(instr.opcode_pos
		+ get_index_two(instr)) % MEM_SIZE];
	reg_copy(instr.l3, instr.s, 0);
	*/
	int	value;
	int	value2;
	int value3;
	int	acb;
	int pos;

	pos = read_reg(proc, 0);
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	acb = read_core1(vm, read_reg(proc, 0));
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	value = read_value(vm, proc, ACB1(acb), 0);
	value2 = read_value(vm, proc, ACB2(acb), 0);
	value3 = read_core4(vm, value + value2 + pos);
	write_reg(proc, read_core1(vm, read_reg(proc, 0)), value);
	modify_carry2(proc, read_reg(proc, read_core1(vm, read_reg(proc, 0))));
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	//modify_carry(proc, instr.l3);
}

void	vm_ldi(t_vm *vm, t_io *proc)
{
	short	value;
	short	value2;
	int value3;
	int	acb;
	int pos;

	pos = read_reg(proc, 0);
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	acb = read_core1(vm, read_reg(proc, 0));
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	value = read_value_index(vm, proc, ACB1(acb), 1);
	value2 = read_value_index(vm, proc, ACB2(acb), 0);
	value3 = read_core4(vm, pos + ((value + value2) % IDX_MOD));
	write_reg(proc, read_core1(vm, read_reg(proc, 0)), value3);
	modify_carry2(proc, read_reg(proc, read_core1(vm, read_reg(proc, 0))));
	write_reg(proc, 0, read_reg(proc, 0) + 1);

	/*
	t_instr		instr;
	int			val;

	instr = init_instr(vm, proc);
	instr.core_index += 2;
	get_offset_index(&instr, ACB1(instr.acb) | 0b100, &instr.l1);
	get_offset_index(&instr, ACB2(instr.acb), &instr.l2);
	get_offset_index(&instr, ACB3(instr.acb), &instr.l3);
	into_reg(instr.core_index, PC);
	val = get_index_two(instr);
	//ft_printf("-> load from %i ", (short)val);
	//ft_printf("(with pc and mod %i)\n", (short)(instr.opcode_pos + val) % MEM_SIZE);
	instr.s = &vm->core[(instr.opcode_pos + val) % MEM_SIZE];
	reg_copy(instr.l3, instr.s, 0);
	*/
}

void	vm_ld(t_vm *vm, t_io *proc)
{
	int	value;
	int	acb;

	write_reg(proc, 0, read_reg(proc, 0) + 1);
	acb = read_core1(vm, read_reg(proc, 0));
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	value = read_value(vm, proc, ACB1(acb), 1);
	write_reg(proc, read_core1(vm, read_reg(proc, 0)), value);
	modify_carry2(proc, read_reg(proc, read_core1(vm, read_reg(proc, 0))));
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	/*
	t_instr		instr;

	instr = init_instr(vm, proc);
	instr.core_index += 2;
	get_offset(&instr, ACB1(instr.acb) | 0b100, &instr.l1);
	get_offset(&instr, ACB2(instr.acb), &instr.l2);
	//ft_printf("ld %i r%i\n", VAL(instr.l1), instr.reg_index[--instr.ri]);
	into_reg(instr.core_index, PC);
	reg_copy(instr.l2, instr.l1, 0);
	modify_carry(proc, instr.l2);
	*/
}

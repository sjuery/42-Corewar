/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/04/09 15:02:07 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	vm_lld(t_vm *vm, t_io *proc)
{
	int				value;
	unsigned char	acb;

	write_reg(proc, 0, read_reg(proc, 0) + 1);
	acb = read_core1(vm, read_reg(proc, 0));
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	value = read_value_load(vm, proc, ACB1(acb));
	write_reg(proc, read_core1(vm, read_reg(proc, 0)), value);
	modify_carry(proc, read_reg(proc, read_core1(vm, read_reg(proc, 0))));
	write_reg(proc, 0, read_reg(proc, 0) + 1);
}

void	vm_lldi(t_vm *vm, t_io *proc)
{
	int				value;
	int				value2;
	int				value3;
	unsigned char	acb;
	int				pos;

	pos = read_reg(proc, 0);
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	acb = read_core1(vm, read_reg(proc, 0));
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	value = read_value_index(vm, proc, ACB1(acb));
	value2 = read_value_index(vm, proc, ACB2(acb));
	value3 = read_core4(vm, value + value2 + pos);
	write_reg(proc, read_core1(vm, read_reg(proc, 0)), value);
	modify_carry(proc, read_reg(proc, read_core1(vm, read_reg(proc, 0))));
	write_reg(proc, 0, read_reg(proc, 0) + 1);
}

void	vm_ldi(t_vm *vm, t_io *proc)
{
	short			value;
	short			value2;
	int				value3;
	unsigned char	acb;
	int				pos;

	pos = read_reg(proc, 0);
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	acb = read_core1(vm, read_reg(proc, 0));
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	value = read_value_index(vm, proc, ACB1(acb));
	value2 = read_value_index(vm, proc, ACB2(acb));
	value3 = read_core4(vm, pos + ((value + value2) % IDX_MOD));
	write_reg(proc, read_core1(vm, read_reg(proc, 0)), value3);
	modify_carry(proc, read_reg(proc, read_core1(vm, read_reg(proc, 0))));
	write_reg(proc, 0, read_reg(proc, 0) + 1);
}

void	vm_ld(t_vm *vm, t_io *proc)
{
	int				value;
	unsigned char	acb;

	write_reg(proc, 0, read_reg(proc, 0) + 1);
	acb = read_core1(vm, read_reg(proc, 0));
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	value = read_value_load(vm, proc, ACB1(acb));
	write_reg(proc, read_core1(vm, read_reg(proc, 0)), value);
	modify_carry(proc, read_reg(proc, read_core1(vm, read_reg(proc, 0))));
	write_reg(proc, 0, read_reg(proc, 0) + 1);
}

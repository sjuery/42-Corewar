/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by anazar            #+#    #+#             */
/*   Updated: 2018/04/01 20:47:23 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	vm_or(t_vm *vm, t_io *proc)
{
	unsigned int	value;
	unsigned int	value2;
	unsigned char	acb;

	write_reg(proc, 0, read_reg(proc, 0) + 1);
	acb = read_core1(vm, read_reg(proc, 0));
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	value = read_value(vm, proc, ACB1(acb));
	value2 = read_value(vm, proc, ACB2(acb));
	write_reg(proc, read_core1(vm, read_reg(proc, 0)), (value | value2));
	modify_carry(proc, read_reg(proc, read_core1(vm, read_reg(proc, 0))));
	write_reg(proc, 0, read_reg(proc, 0) + 1);
}

void	vm_xor(t_vm *vm, t_io *proc)
{
	unsigned int	value;
	unsigned int	value2;
	unsigned char	acb;

	write_reg(proc, 0, read_reg(proc, 0) + 1);
	acb = read_core1(vm, read_reg(proc, 0));
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	value = read_value(vm, proc, ACB1(acb));
	value2 = read_value(vm, proc, ACB2(acb));
	write_reg(proc, read_core1(vm, read_reg(proc, 0)), (value ^ value2));
	modify_carry(proc, read_reg(proc, read_core1(vm, read_reg(proc, 0))));
	write_reg(proc, 0, read_reg(proc, 0) + 1);
}

void	vm_and(t_vm *vm, t_io *proc)
{
	unsigned int	value;
	unsigned int	value2;
	unsigned char	acb;

	write_reg(proc, 0, read_reg(proc, 0) + 1);
	acb = read_core1(vm, read_reg(proc, 0));
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	value = read_value(vm, proc, ACB1(acb));
	value2 = read_value(vm, proc, ACB2(acb));
	write_reg(proc, read_core1(vm, read_reg(proc, 0)), (value & value2));
	modify_carry(proc, read_reg(proc, read_core1(vm, read_reg(proc, 0))));
	write_reg(proc, 0, read_reg(proc, 0) + 1);
}

void	vm_sub(t_vm *vm, t_io *proc)
{
	int					value;
	int					value2;
	unsigned char		acb;

	write_reg(proc, 0, read_reg(proc, 0) + 1);
	acb = read_core1(vm, read_reg(proc, 0));
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	value = read_value(vm, proc, ACB1(acb));
	value2 = read_value(vm, proc, ACB2(acb));
	write_reg(proc, read_core1(vm, read_reg(proc, 0)), (value - value2));
	modify_carry(proc, read_reg(proc, read_core1(vm, read_reg(proc, 0))));
	write_reg(proc, 0, read_reg(proc, 0) + 1);
}

void	vm_add(t_vm *vm, t_io *proc)
{
	int					value;
	int					value2;
	unsigned char		acb;

	write_reg(proc, 0, read_reg(proc, 0) + 1);
	acb = read_core1(vm, read_reg(proc, 0));
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	value = read_value(vm, proc, ACB1(acb));
	value2 = read_value(vm, proc, ACB2(acb));
	write_reg(proc, read_core1(vm, read_reg(proc, 0)), (value + value2));
	modify_carry(proc, read_reg(proc, read_core1(vm, read_reg(proc, 0))));
	write_reg(proc, 0, read_reg(proc, 0) + 1);
}

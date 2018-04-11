/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by anazar            #+#    #+#             */
/*   Updated: 2018/04/10 14:20:18 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	vm_st(t_vm *vm, t_io *proc)
{
	int				value;
	int				pos_code;
	unsigned char	acb;

	read_acb_info(vm, proc, &pos_code, &acb);
	value = read_value(vm, proc, ACB1(acb));
	if (ACB2(acb) == 1)
	{
		write_reg(proc, read_core1(vm, read_reg(proc, 0)), value);
		write_reg(proc, 0, read_reg(proc, 0) + 1);
	}
	else
	{
		write_core(vm, pos_code +
			(read_core2(vm, read_reg(proc, 0)) % IDX_MOD), value);
		vis_copy(vm->vis, value, proc, (unsigned short)(pos_code +
			(read_core2(vm, read_reg(proc, 0)) % IDX_MOD)));
		vis_update(vm, (unsigned short)(pos_code +
			(read_core2(vm, read_reg(proc, 0)) % IDX_MOD)));
		write_reg(proc, 0, read_reg(proc, 0) + 2);
	}
}

void	vm_sti(t_vm *vm, t_io *proc)
{
	int				value;
	int				value2;
	int				value3;
	unsigned char	acb;
	int				pos_code;

	read_acb_info(vm, proc, &pos_code, &acb);
	value = read_value_index(vm, proc, ACB1(acb));
	value2 = read_value_index(vm, proc, ACB2(acb));
	value3 = read_value_index(vm, proc, ACB3(acb));
	write_core(vm, pos_code + ((value2 + value3) % IDX_MOD), value);
	if (ACB3(acb) == 1)
	{
		vis_copy(vm->vis, value, proc, (unsigned short)(pos_code +
			((value2 + value3) % IDX_MOD)));
		vis_update(vm, (unsigned short)(pos_code +
			((value2 + value3) % IDX_MOD)));
	}
	else
	{
		vis_copy(vm->vis, value, proc, (unsigned short)(pos_code +
			((value2 + value3) % IDX_MOD)));
		vis_update(vm, (unsigned short)(pos_code +
			((value2 + value3) % IDX_MOD)));
	}
}

void	vm_zjmp(t_vm *vm, t_io *proc)
{
	unsigned short		val;

	write_reg(proc, 0, read_reg(proc, 0) + 1);
	if (!proc->carry)
	{
		write_reg(proc, 0, read_reg(proc, 0) + 2);
		return ;
	}
	val = read_core2(vm, read_reg(proc, 0) % MEM_SIZE) % IDX_MOD;
	write_reg(proc, 0, (read_reg(proc, 0) + val - 1) % MEM_SIZE);
}

void	vm_live(t_vm *vm, t_io *proc)
{
	int				val;
	unsigned char	*l;

	l = &(vm->core[PARAM2 % MEM_SIZE]);
	val = read_core4(vm, read_reg(proc, 0) + 1);
	if (val <= -1 && val >= (vm->num_players * -1))
		vm->win_player = val * -1;
	vm->live++;
	proc->alive = 1;
	write_reg(proc, 0, read_reg(proc, 0) + 5);
}

void	vm_aff(t_vm *vm, t_io *proc)
{
	char		aff_val;

	write_reg(proc, 0, read_reg(proc, 0) + 2);
	aff_val = (read_reg(proc, read_core1(vm, read_reg(proc, 0)))) % 256;
	if (!vm->f.g)
	{
		ft_putchar(aff_val);
		ft_putchar('\n');
	}
	write_reg(proc, 0, read_reg(proc, 0) + 1);
}

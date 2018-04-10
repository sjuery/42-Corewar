/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/04/05 13:03:51 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	modify_carry(t_io *proc, unsigned char value)
{
	if (!value)
		proc->carry = 1;
	else
		proc->carry = 0;
}

int		get_priority(t_vm *vm, t_io *proc)
{
	return (proc->executing * (proc->cycle_to_execute - vm->cycles));
}

void	read_acb_info(t_vm *vm, t_io *proc, int *pos_code, unsigned char *acb)
{
	*pos_code = read_reg(proc, 0);
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	*acb = read_core1(vm, read_reg(proc, 0));
	write_reg(proc, 0, read_reg(proc, 0) + 1);
}

void	vm_lfork(t_vm *vm, t_io *proc)
{
	t_io		*new_proc;
	int			pos_code;
	short		index;

	pos_code = read_reg(proc, 0);
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	index = read_core2(vm, read_reg(proc, 0));
	new_proc = (t_io *)ft_memalloc(sizeof(t_io));
	ft_memcpy(new_proc, proc, sizeof(t_io));
	++vm->process_count;
	++vm->process_num;
	new_proc->alive = 0;
	new_proc->process = vm->process_num - 1;
	write_reg(new_proc, 0, (pos_code + index) % MEM_SIZE);
	write_reg(proc, 0, read_reg(proc, 0) + 2);
	new_proc->op = vm->core[read_reg(new_proc, 0) % MEM_SIZE];
	set_cycle_to_execute(vm, new_proc);
	enqueue(vm->q, new_proc, new_proc->executing * new_proc->cycle_to_execute);
	play_spawn(vm);
}

void	vm_fork(t_vm *vm, t_io *proc)
{
	t_io			*new_proc;
	unsigned int	pos_code;
	short			index;

	pos_code = read_reg(proc, 0);
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	index = read_core2(vm, read_reg(proc, 0)) % IDX_MOD;
	new_proc = (t_io *)ft_memalloc(sizeof(t_io));
	ft_memcpy(new_proc, proc, sizeof(t_io));
	++vm->process_count;
	++vm->process_num;
	new_proc->alive = 0;
	new_proc->process = vm->process_num - 1;
	write_reg(new_proc, 0, (pos_code + index) % MEM_SIZE);
	write_reg(proc, 0, read_reg(proc, 0) + 2);
	new_proc->op = vm->core[read_reg(new_proc, 0) % MEM_SIZE];
	set_cycle_to_execute(vm, new_proc);
	enqueue(vm->q, new_proc, new_proc->executing * new_proc->cycle_to_execute);
	play_spawn(vm);
}

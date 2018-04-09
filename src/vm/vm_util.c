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

int		indirect(t_vm *vm, unsigned char opcode, t_instr *instr)
{
	if (opcode)
		return ((short)(vm->core[(OFF2) % MEM_SIZE] * 0x100 +
				vm->core[(OFF2 + 1) % MEM_SIZE]) % IDX_MOD);
	else
		return ((vm->core[(OFF2) % MEM_SIZE] * 0x100 +
				vm->core[(OFF2 + 1) % MEM_SIZE]) % MEM_SIZE);
}

int		get_index_one(unsigned char *l)
{
	int val;

	val = l[1] + (l[0] << 8);
	return (val);
}

int		get_index_two(t_instr instr)
{
	int	out1;
	int	out2;

	out1 = 0;
	out2 = 0;
	if (ACB1(instr.acb) == 1)
		out1 = VAL3(instr.l1);
	else if (ACB1(instr.acb) == 2)
		out1 = VAL2(instr.l1);
	else if (ACB1(instr.acb) == 3)
		out1 = VAL(instr.l1);
	if (ACB2(instr.acb) == 1)
		out2 = VAL3(instr.l2);
	else if (ACB2(instr.acb) == 2)
		out2 = VAL2(instr.l2);
	return (out1 + out2);
}

void	modify_carry(t_io *proc, unsigned char *reg)
{
	if (reg[0] == 0 && reg[1] == 0 && reg[2] == 0 && reg[3] == 0)
		proc->carry = 1;
	else
		proc->carry = 0;
}

int		get_priority(t_vm *vm, t_io *proc)
{
	return (proc->executing * (proc->cycle_to_execute - vm->cycles));
}

void	play_spawn(t_vm *vm)
{
	if (vm->f.noise == 0 && (vm->f.s == 1 || vm->f.s == 3))
	{
		system("afplay ./sound/spawn.wav &");
		vm->f.noise++;
	}
}


void vm_lfork(t_vm *vm, t_io *proc)
{
	t_io		*new_proc;
	int			pos_code;
	short			index;
	
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
	t_io		*new_proc;
	unsigned int			pos_code;
	short		index;
	
	pos_code = read_reg(proc, 0);
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	index =  read_core2(vm, read_reg(proc, 0)) % IDX_MOD;
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

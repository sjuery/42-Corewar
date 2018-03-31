/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/03/31 15:57:21 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int		indirect(t_vm *vm, int i, unsigned char opcode, t_instr *instr)
{
	printf("opcode %i\n", (int)opcode);
	if (opcode)
		return ((vm->core[vm->info[i].start + OFF2] * 0x100 +
				vm->core[vm->info[i].start + OFF2 + 1]) % IDX_MOD);
	else
		return ((vm->core[vm->info[i].start + OFF2] * 0x100 +
				vm->core[vm->info[i].start + OFF2 + 1]) % MEM_SIZE);
}

int		get_index_one(unsigned char *l)
{
	short val;

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

void	modify_carry(t_vm *vm, int i, unsigned char *reg)
{
	if (reg[0] == 0 && reg[1] == 0 && reg[2] == 0 && reg[3] == 0)
		vm->info[i].carry = 1;
	else
		vm->info[i].carry = 0;
}

//void vm_lfork(t_vm *vm, t_io *proc)
void	vm_lfork(t_vm *vm, int i)
{
	int			j;
	t_instr		instr;
	//t_io		*new_proc;

	//instr = init_instr(vm, i);
	//instr.acb = 0;
	//instr.core_index++;
	//get_offset_index(&instr, 2, &instr.l1);
	//new_proc = (t_io *)ft_memalloc(sizeof(t_io));
	//ft_memcpy(new_proc, proc, sizeof(t_io));
	//++vm->process_count;
	//new_proc->carry = 0;
	//new_proc->wait_cycle = 0;
	//new_proc->waiting = 0;
	//into_reg(VAL2(instr.l1) % MEM_SIZE, new_proc.regs[0]); // may need to do (instr.l1[0] << 8 | instr.l1[1])
	//into_reg(VAL(PC) + 3, PC);
	//enqueue(vm->queue, new_proc, get_priority(new_proc))
	instr = init_instr(vm, i);
	instr.acb = 0;
	instr.core_index++;
	j = vm->process_count;
	while (vm->info[j].executing)
		++j;
	vm->process_count++;
	get_offset_index(&instr, 2, &instr.l1);
	copy_io(vm, j, i);
	vm->info[j].start = (vm->info[i].start + instr.opcode_pos +
	(instr.l1[0] << 8 | instr.l1[1])) % MEM_SIZE;
	vm->info[j].carry = 0;
	vm->info[j].wait_cycle = 0;
	vm->info[j].waiting = 0;
	into_reg(0, vm->info[j].regs[0]);
	into_reg(VAL(PC) + 3, PC);
}

void	vm_fork(t_vm *vm, int i)
{
	int			j;
	t_instr		instr;
	//t_io		*new_proc;

	//instr = init_instr(vm, i);
	//instr.acb = 0;
	//instr.core_index++;
	//get_offset_index(&instr, 2, &instr.l1);
	//new_proc = (t_io *)ft_memalloc(sizeof(t_io));
	//ft_memcpy(new_proc, proc, sizeof(t_io));
	//++vm->process_count;
	//new_proc->carry = 0;
	//new_proc->wait_cycle = 0;
	//new_proc->waiting = 0;
	//into_reg(VAL2(instr.l1) % IDX_MOD, new_proc.regs[0]); // may need to do (instr.l1[0] << 8 | instr.l1[1])
	//into_reg(VAL(PC) + 3, PC);
	//enqueue(vm->queue, new_proc, get_priority(new_proc))
	instr = init_instr(vm, i);
	instr.acb = 0;
	instr.core_index++;
	j = vm->process_count;
	while (vm->info[j].executing)
		++j;
	vm->process_count++;
	get_offset_index(&instr, 2, &instr.l1);
	copy_io(vm, j, i);
	vm->info[j].start = vm->info[i].start + instr.opcode_pos +
		(instr.l1[0] << 8 | instr.l1[1]) % IDX_MOD;
	vm->info[j].carry = 0;
	vm->info[j].wait_cycle = 0;
	vm->info[j].waiting = 0;
	into_reg(0, vm->info[j].regs[0]);
	into_reg(VAL(PC) + 1, PC);
}

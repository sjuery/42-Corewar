/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by anazar            #+#    #+#             */
/*   Updated: 2018/04/05 21:49:23 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

// void	vm_or(t_vm *vm, t_io *proc)
// {
// 	unsigned int value;
// 	unsigned int value2;
// 	unsigned char acb;

// 	write_reg(proc, 0, read_reg(proc, 0) + 1);
// 	acb = read_core1(vm, read_reg(proc, 0));
// 	write_reg(proc, 0, read_reg(proc, 0) + 1);
// 	value = read_value(vm, proc, ACB1(acb));
// 	value2 = read_value(vm, proc, ACB2(acb));
// 	write_reg(proc, read_core1(vm, read_reg(proc, 0)), (value | value2));
// 	modify_carry2(proc, read_reg(proc, read_core1(vm, read_reg(proc, 0))));
// 	write_reg(proc, 0, read_reg(proc, 0) + 1);
// }

void	vis_copy2(t_vis *dest, int src, t_io *proc, int index)
{
	dest[index % MEM_SIZE].byte = (src >> 24) % 0x100;
	dest[(index + 1) % MEM_SIZE].byte = (src >> 16) % 0x100;
	dest[(index + 2) % MEM_SIZE].byte = (src >> 8) % 0x100;
	dest[(index + 3) % MEM_SIZE].byte = src % 0x100;
	dest[index % MEM_SIZE].player = proc->player_int;
	dest[(index + 1) % MEM_SIZE].player = proc->player_int;
	dest[(index + 2) % MEM_SIZE].player = proc->player_int;
	dest[(index + 3) % MEM_SIZE].player = proc->player_int;
}

void	vis_update2(t_vm *vm, int index)
{
	static short	schizo[] = {
		COLOR_CYAN, COLOR_RED, COLOR_YELLOW, COLOR_GREEN,
		COLOR_BLACK, COLOR_WHITE, COLOR_MAGENTA };

	static long		pain;

	if (vm->f.r == 1 && pain % 200 == 0)
	{
		init_pair(7, schizo[rand() % 6], schizo[rand() % 6]);
		init_pair(8, schizo[rand() % 6], schizo[rand() % 6]);
		init_pair(9, schizo[rand() % 6], schizo[rand() % 6]);
		init_pair(10, schizo[rand() % 6], schizo[rand() % 6]);
		init_pair(11, schizo[rand() % 6], schizo[rand() % 6]);
		init_pair(12, schizo[rand() % 6], schizo[rand() % 6]);
		init_pair(13, schizo[rand() % 6], schizo[rand() % 6]);
	}
	if (vm->f.r == 1)
		attron(COLOR_PAIR(rand() % 7 + 7));
	else
		attron(COLOR_PAIR(vm->vis[index].player));
	pain++;
	mvprintw((index % MEM_SIZE / 64 + 1) % MEM_SIZE, (index * 3) % VWRAP, "%02hhx",
		vm->vis[(index) % MEM_SIZE].byte);
	mvprintw(((index + 1) % MEM_SIZE / 64 + 1) % MEM_SIZE, ((index + 1) * 3) % VWRAP, "%02hhx",
		vm->vis[(index + 1) % MEM_SIZE].byte);
	mvprintw(((index + 2) % MEM_SIZE / 64 + 1) % MEM_SIZE, ((index + 2) * 3) % VWRAP, "%02hhx",
		vm->vis[(index + 2) % MEM_SIZE].byte);
	mvprintw(((index + 3) % MEM_SIZE / 64 + 1) % MEM_SIZE, ((index + 3) * 3) % VWRAP, "%02hhx",
		vm->vis[(index + 3) % MEM_SIZE].byte);
	attroff(COLOR_PAIR(vm->vis[index].player));
	refresh();
}


void	vm_st(t_vm *vm, t_io *proc) //#27437, #642, #ctd-14
{
	int value;
	int pos_code;
	int acb;

	pos_code = read_reg(proc, 0); // getting the start of the instruction
	write_reg(proc, 0, read_reg(proc, 0) + 1); // incrementing to next byte
	acb = read_core1(vm, read_reg(proc, 0)); // recording the value of acb
	write_reg(proc, 0, read_reg(proc, 0) + 1); // incremeneting to first instruction
	value = read_value(vm, proc, ACB1(acb)); // value of the first registry, auto increments byte
	if (ACB2(acb) == 1) // is a register,  will write to reg with information in the reg
	{
		write_reg(proc, read_core1(vm, read_reg(proc, 0)), value); // proc, reg_num, value
		write_reg(proc, 0, read_reg(proc, 0) + 1); // increment to end of instruction
	}
	else
	{
		write_core(vm, pos_code + (read_core2(vm, read_reg(proc, 0)) % IDX_MOD), value); // vm, position on board, value
		// vis_copy2(vm->vis, value, proc, pos_code + (read_core2(vm, read_reg(proc, 0)) % IDX_MOD));
		// vis_update2(vm, pos_code + (read_core2(vm, read_reg(proc, 0)) % IDX_MOD));
		write_reg(proc, 0, read_reg(proc, 0) + 2); // increment to end of instruction
	}
}

void	vm_sti(t_vm *vm, t_io *proc)
{
	int value;
	int	value2;
	int acb;
	int	pos_code;

	pos_code = read_reg(proc, 0);
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	acb = read_core1(vm, read_reg(proc, 0));
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	value = read_value(vm, proc, ACB1(acb));
	// if (ACB2(acb) == 3)
	// {
	// 	value2 = read_core2(vm, read_reg(proc, 0));
	// }
	// else
		value2 = read_value(vm, proc, ACB2(acb));
	if (ACB3(acb) == 1)
	{
		if (ACB2(acb) == 3)
			write_core(vm, (pos_code + value2), value);
		else
			write_core(vm, (pos_code + value2 + read_reg(proc, read_core1(vm, 0))), value);
		ft_printf("register %u, value %u - \n", read_core1(vm, 0), read_reg(proc, read_core1(vm, 0)));
		write_reg(proc, 0, read_reg(proc, 0) + 1);
	}
	else
	{
		if (ACB2(acb) == 3)
			write_core(vm, (pos_code + value2), value);
		else
			write_core(vm, (pos_code + value2 + read_core4(vm, read_reg(proc, 0))), value);
		ft_printf("read core4 %u - \n", read_core4(vm, read_reg(proc, 0)));
		write_reg(proc, 0, read_reg(proc, 0) + 4);
	}

	// t_instr		instr;
	// int			ind;

	// ind = 0;
	// instr = init_instr(vm, proc);
	// instr.core_index += 2;
	// get_offset_index(&instr, ACB1(instr.acb), &instr.l1);
	// get_offset_index(&instr, ACB2(instr.acb), &instr.l2);
	// if(ACB2(instr.acb) == 3)
	// {
	// 	instr.core_index -= 2;
	// 	ind = indirect(instr.vm, 0, &instr);
	// 	instr.core_index += 2;
	// }
	// get_offset_index(&instr, ACB3(instr.acb), &instr.l3);
	// into_reg(instr.core_index, PC);
	// instr.index = (((ACB2(instr.acb) == 1 ? VAL3(instr.l2) : VAL2(instr.l2)) +
	// 			(ACB3(instr.acb) == 1 ? VAL3(instr.l3) : VAL2(instr.l3)))
	// 		& 0xFFFF);
	// if (ind)
	// 	instr.index = ind;
	// reg_copy(vm->core, instr.l1, instr.opcode_pos + instr.index);
	// vis_copy(vm->vis, instr.l1, proc, instr.opcode_pos + instr.index);
	// vis_update(vm, (instr.opcode_pos + instr.index) % MEM_SIZE);
}


void	vm_zjmp(t_vm *vm, t_io *proc)
{
	t_instr instr;
	unsigned short		val;

	instr = init_instr(vm, proc);
	instr.acb = 0;
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	if (!proc->carry)
	{
		write_reg(proc, 0, read_reg(proc, 0) + 2);
		return ;
	}
	val = read_core2(vm, read_reg(proc, 0) % MEM_SIZE) % MEM_SIZE;
	write_reg(proc, 0, read_reg(proc, 0) + val - 1);
}

void	vm_live(t_vm *vm, t_io *proc)
{
	int				val;
	unsigned char	*l;

	l =  &(vm->core[PARAM2 % MEM_SIZE]);
	val = read_core4(vm, read_reg(proc, 0) + 1);
	if (val <= -1 && val >= (vm->num_players * -1))
		vm->win_player = val * -1;
	vm->live++;
	proc->alive = 1;
	write_reg(proc, 0, read_reg(proc, 0) + 5);
}

void	vm_aff(t_vm *vm, t_io *proc)
{
	t_instr		instr;

	instr = init_instr(vm, proc);
	instr.core_index += 2;
	get_offset(&instr, ACB1(instr.acb), &instr.l1);
	ft_printf("%c\n",  VAL(instr.l1) % 256);
	into_reg(instr.core_index, PC);
}

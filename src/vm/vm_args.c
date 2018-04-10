/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by anazar            #+#    #+#             */
/*   Updated: 2018/04/09 20:51:55 by ihodge           ###   ########.fr       */
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
		pain++;
	}
	if (vm->f.r == 1)
		attron(COLOR_PAIR(rand() % 7 + 7));
	else
	{
		// if (index < 0)
		// 	index = 4096 + index;
		attron(COLOR_PAIR(vm->vis[index % MEM_SIZE].player));
	}
	mvprintw((index % MEM_SIZE / 64 + 1) % MEM_SIZE, (index * 3) % VWRAP, "%02hhx",
		vm->vis[(index) % MEM_SIZE].byte);
	mvprintw(((index + 1) % MEM_SIZE / 64 + 1) % MEM_SIZE, ((index + 1) * 3) % VWRAP, "%02hhx",
		vm->vis[(index + 1) % MEM_SIZE].byte);
	mvprintw(((index + 2) % MEM_SIZE / 64 + 1) % MEM_SIZE, ((index + 2) * 3) % VWRAP, "%02hhx",
		vm->vis[(index + 2) % MEM_SIZE].byte);
	mvprintw(((index + 3) % MEM_SIZE / 64 + 1) % MEM_SIZE, ((index + 3) * 3) % VWRAP, "%02hhx",
		vm->vis[(index + 3) % MEM_SIZE].byte);
	attroff(COLOR_PAIR(vm->vis[index % MEM_SIZE].player));
	refresh();
}

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

void	vm_st(t_vm *vm, t_io *proc)
{
	int value;
	int pos_code;
	unsigned char acb;

	pos_code = read_reg(proc, 0);
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	acb = read_core1(vm, read_reg(proc, 0));
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	value = read_value(vm, proc, ACB1(acb));
	if (ACB2(acb) == 1)
	{
		write_reg(proc, read_core1(vm, read_reg(proc, 0)), value);
		write_reg(proc, 0, read_reg(proc, 0) + 1);
	}
	else
	{
		write_core(vm, pos_code + (read_core2(vm, read_reg(proc, 0)) % IDX_MOD), value);
		vis_copy2(vm->vis, value, proc, (unsigned short)(pos_code + (read_core2(vm, read_reg(proc, 0)) % IDX_MOD)));
		// ft_printf("Value %i, %hhx, %i\n", pos_code,  (read_core2(vm, read_reg(proc, 0)) % IDX_MOD), pos_code + (read_core2(vm, read_reg(proc, 0)) % IDX_MOD));
		vis_update2(vm, (unsigned short)(pos_code + (read_core2(vm, read_reg(proc, 0)) % IDX_MOD)));
		write_reg(proc, 0, read_reg(proc, 0) + 2);
	}
}

void	vm_sti(t_vm *vm, t_io *proc)
{
	int value;
	int	value2;
	int value3;
	unsigned char acb;
	int	pos_code;

	pos_code = read_reg(proc, 0);
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	acb = read_core1(vm, read_reg(proc, 0));
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	value = read_value_index(vm, proc, ACB1(acb));
	value2 = read_value_index(vm, proc, ACB2(acb));
	value3 = read_value_index(vm, proc, ACB3(acb));
	write_core(vm, pos_code + ((value2 + value3) % IDX_MOD), value);
	if (ACB3(acb) == 1)
	{
		vis_copy2(vm->vis, value, proc, (unsigned short)(pos_code + ((value2 + value3) % IDX_MOD)));
		vis_update2(vm, (unsigned short)(pos_code + ((value2 + value3) % IDX_MOD)));
	}
	else
	{
		vis_copy2(vm->vis, value, proc, (unsigned short)(pos_code + ((value2 + value3) % IDX_MOD)));
		vis_update2(vm, (unsigned short)(pos_code + ((value2 + value3) % IDX_MOD)));
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
	//int			reg;

	//write_reg(proc, 0, read_reg(proc, 0) + 1);
	//reg = 
	instr = init_instr(vm, proc);
	instr.core_index += 2;
	get_offset(&instr, ACB1(instr.acb), &instr.l1);
	ft_printf("%c\n",  VAL(instr.l1) % 256);
	into_reg(instr.core_index, PC);
}

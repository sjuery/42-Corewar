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

void	vm_st(t_vm *vm, t_io *proc)
{
	t_instr		instr;

	instr = init_instr(vm, proc);
	instr.core_index += 2;
	get_offset(&instr, ACB1(instr.acb), &instr.l1);
	get_offset(&instr, ACB2(instr.acb) | 0b100, &instr.l2);
	if (ACB2(instr.acb) == 1)
	{
		reg_copy(instr.l2, instr.l1, 0);
		//instr.index = (VAL3(instr.l2) & 0xFFFF);
	ft_printf("first reg %i\n", VAL(instr.l1));
	ft_printf("second reg %i\n", VAL(instr.l2));
	}
	else
	{
		instr.core_index -= 2;
		instr.index = (unsigned short)(indirect(instr.vm, 1, &instr));
		instr.core_index += 2;
		reg_copy(vm->core, instr.l1, instr.opcode_pos + instr.index);
		vis_copy(vm->vis, instr.l1, proc, (instr.opcode_pos + instr.index) % MEM_SIZE);
		vis_update(vm, (instr.opcode_pos + instr.index) % MEM_SIZE);
	}
	//ft_printf("st r%i %i cycle [%i]\n", instr.reg_index[--instr.ri], (short)instr.index, vm->cycles);
	//ft_printf("-> with mod and pc %i\n", (instr.opcode_pos + instr.index) % MEM_SIZE);
	into_reg(instr.core_index, PC);
}

void	vm_sti(t_vm *vm, t_io *proc)
{
	t_instr		instr;
	int			ind;

	ind = 0;
	instr = init_instr(vm, proc);
	instr.core_index += 2;
	get_offset_index(&instr, ACB1(instr.acb), &instr.l1);
	get_offset_index(&instr, ACB2(instr.acb), &instr.l2);
	if(ACB2(instr.acb) == 3)
	{
		instr.core_index -= 2;
		ind = indirect(instr.vm, 0, &instr);
		instr.core_index += 2;
	}
	get_offset_index(&instr, ACB3(instr.acb), &instr.l3);
	into_reg(instr.core_index, PC);
	instr.index = (((ACB2(instr.acb) == 1 ? VAL3(instr.l2) : VAL2(instr.l2)) +
				(ACB3(instr.acb) == 1 ? VAL3(instr.l3) : VAL2(instr.l3)))
			& 0xFFFF);
	if (ind)
		instr.index = ind;
	//ft_printf("sti r%i cycle[%i]\n", instr.reg_index[--instr.ri], vm->cycles);
	//ft_printf(" in reg %i\n", VAL(proc->regs[instr.reg_index[instr.ri]]));
	//ft_printf("-> store to %i + %hi = %i", (short)VAL2(instr.l2), (short)VAL3(instr.l3), (short)(instr.index));
	//ft_printf(" (with pc and mod %i)\n", (short)(instr.opcode_pos + instr.index) % MEM_SIZE);
	//ft_printf("storing in %i\n", (instr.opcode_pos + instr.index) % MEM_SIZE);
	reg_copy(vm->core, instr.l1, instr.opcode_pos + instr.index);
	vis_copy(vm->vis, instr.l1, proc, instr.opcode_pos + instr.index);
	vis_update(vm, (instr.opcode_pos + instr.index) % MEM_SIZE);
}

// short     read_core3(t_vm *vm, unsigned int pos)
// {
//     return ((((short)vm->core[(pos + 1) % MEM_SIZE]) | ((short)vm->core[pos % MEM_SIZE] << 8)) % MEM_SIZE);
// }

short read_core3(t_vm *vm, unsigned int pos)
{
    return (((short)vm->core[pos % MEM_SIZE] << 8) | ((short)vm->core[(pos + 1) % MEM_SIZE])) % MEM_SIZE;
}


void	vm_zjmp(t_vm *vm, t_io *proc)
{
	t_instr instr;
	unsigned short		val;

	instr = init_instr(vm, proc);
	instr.acb = 0;
	// into_reg(VAL(PC) + 1, PC);
	write_reg(proc, 0, read_reg(proc, 0) + 1);
	if (!proc->carry)
	{
		//ft_printf("\tzjmp failed\n");
		write_reg(proc, 0, read_reg(proc, 0) + 2);
		// into_reg(VAL(PC) + 2, PC);
		return ;
	}
	//ft_printf("\tzjmp OK ");
	val = read_core2(vm, read_reg(proc, 0) % MEM_SIZE) % MEM_SIZE;
	//if (val != (val % MEM_SIZE))
	//ft_printf("%hd %hd %hd\n", val, read_core2(vm, read_reg(proc, 0) % MEM_SIZE), read_core3(vm, read_reg(proc, 0) % MEM_SIZE));
	// val = get_index_one(&vm->core[read_reg(proc, 0) % MEM_SIZE]);
	// val = get_index_one(&vm->core[PARAM1]);
	//ft_printf(" %i\n", (short)val);
	write_reg(proc, 0, read_reg(proc, 0) + val - 1);
	// into_reg((VAL(PC) + val - 1) % MEM_SIZE, PC);
}

void	vm_live(t_vm *vm, t_io *proc)
{
	int				val;
	unsigned char	*l;

	l =  &(vm->core[PARAM2 % MEM_SIZE]);
	// val = VAL(l);
	val = read_core4(vm, read_reg(proc, 0) + 1);
	// ft_printf("LIVE %i\n", val);
	if (val <= -1 && val >= (vm->num_players * -1))
		vm->win_player = val * -1;
	vm->live++;
	proc->alive = 1;
	write_reg(proc, 0, read_reg(proc, 0) + 5);
	// into_reg(VAL(PC) + 5, PC);
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

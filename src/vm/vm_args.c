/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by anazar            #+#    #+#             */
/*   Updated: 2018/04/03 17:13:51 by ihodge           ###   ########.fr       */
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
	if (ACB2(instr.acb == 1))
	{
		ft_printf("REGISTER\n");
		instr.index = (VAL3(instr.l2) & 0xFFFF) % IDX_MOD;
	}
	else
	{
		instr.core_index -= 2;
		instr.index = (indirect(instr.vm, 1, &instr));
		instr.core_index += 2;
	}
	ft_printf("st r%i %i\n", instr.reg_index[--instr.ri], instr.index);
	into_reg(instr.core_index, PC);
	reg_copy(&vm->core[instr.opcode_pos + instr.index], instr.l1);
	vis_copy(&vm->vis[instr.opcode_pos + instr.index], instr.l1, proc);
	vis_update(vm, instr.opcode_pos + instr.index);
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
	ft_printf("sti r%i cycle[%i]\n", instr.reg_index[--instr.ri], vm->cycles);
	ft_printf("-> store to %i + %hi = %i", (short)VAL2(instr.l2), (short)VAL3(instr.l3), (short)(instr.index));
	ft_printf(" (with pc and mod %i)\n", (short)(instr.opcode_pos + instr.index) % MEM_SIZE);
	ft_printf("stroring in %i\n", (instr.opcode_pos + instr.index) % MEM_SIZE);
	reg_copy(&vm->core[(instr.opcode_pos + instr.index) % MEM_SIZE],
		instr.l1);
	vis_copy(&vm->vis[(instr.opcode_pos + instr.index) & MEM_SIZE],
		instr.l1, proc);
	vis_update(vm, (instr.opcode_pos + instr.index) % MEM_SIZE);
}

void	vm_zjmp(t_vm *vm, t_io *proc)
{
	t_instr instr;
	int		val;

	instr = init_instr(vm, proc);
	instr.acb = 0;
	into_reg(VAL(PC) + 1, PC);
	if (!proc->carry)
	{
		ft_printf("\tzjmp failed\n");
		into_reg(VAL(PC) + 2, PC);
		return ;
	}
	ft_printf("\tzjmp OK ");
	val = get_index_one(&vm->core[PARAM1]);
	ft_printf(" %i\n", (short)val);
	into_reg((VAL(PC) + val - 1) % MEM_SIZE, PC);
}

void	vm_live(t_vm *vm, t_io *proc)
{
	//vm->win_player = vm->info[i].player_int;
	if (vm->core[PARAM1 + 1] == 0xff && vm->core[PARAM1 + 2] == 0xff
			&& vm->core[PARAM1 + 3] == 0xff
			&& (vm->core[PARAM1 + 4] >= 0xff - (vm->num_players - 1)
				&& vm->core[PARAM1 + 4] <= 0xff))
	{
		vm->win_player = vm->core[PARAM1 + 4] - 0xff + 1;
	}
	vm->live++;
	proc->alive = 1;
	into_reg(VAL(PC) + 5, PC);
}

void	vm_aff(t_vm *vm, t_io *proc)
{
	t_instr		instr;

	instr = init_instr(vm, proc);
	instr.core_index += 2;
	get_offset(&instr, ACB1(instr.acb), &instr.l1);
	into_reg(instr.core_index, PC);
}

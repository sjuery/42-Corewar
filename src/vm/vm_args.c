/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by anazar            #+#    #+#             */
/*   Updated: 2018/04/02 15:40:52 by ihodge           ###   ########.fr       */
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
		instr.index = (VAL3(instr.l2) & 0xFFFF) % IDX_MOD;
	else
	{
		instr.core_index -= 2;
		instr.index = indirect(instr.vm, 1, &instr);
		instr.core_index += 2;
	}
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
		ind = indirect(instr.vm, 1, &instr);
		instr.core_index += 2;
	}
	get_offset_index(&instr, ACB3(instr.acb), &instr.l3);
	into_reg(instr.core_index, PC);
	instr.index = (((ACB2(instr.acb) == 1 ? VAL3(instr.l2) : VAL2(instr.l2)) +
				(ACB3(instr.acb) == 1 ? VAL3(instr.l3) : VAL2(instr.l3)))
			& 0xFFFF);
	if (ind)
		instr.index = ind;
	reg_copy(&vm->core[instr.opcode_pos + instr.index],
		instr.l1);
	vis_copy(&vm->vis[instr.opcode_pos + instr.index],
		instr.l1, proc);
	vis_update(vm, instr.opcode_pos + instr.index);
}

void	vm_zjmp(t_vm *vm, t_io *proc)
{
	t_instr instr;

	instr = init_instr(vm, proc);
	instr.acb = 0;
	into_reg(VAL(PC) + 1, PC);
	if (!proc->carry)
	{
		into_reg(VAL(PC) + 2, PC);
		return ;
	}
	into_reg(VAL(PC) + get_index_one(&vm->core[PARAM1]) - 1, PC);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by anazar            #+#    #+#             */
/*   Updated: 2018/03/27 15:09:47 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	vm_st(t_vm *vm, int i)
{
	t_instr		instr;
	int			idx;

	idx = ((ACB2(instr.acb) & 0b100) != 0);
	instr = init_instr(vm, i);
	vm->info[i].index++;
	instr.core_index += 2;
	get_offset(&instr, ACB1(instr.acb), &instr.l1);
	get_offset(&instr, ACB2(instr.acb) | 0b100, &instr.l2);
	if (ACB2(instr.acb == 1))
		instr.index = (VAL3(instr.l2) & 0xFFFF) % IDX_MOD;
	else
	{
		instr.core_index -= 2;
		instr.index = indirect(instr.vm, instr.i, 1, &instr);
		instr.core_index += 2;
	}
	vm->info[i].index = instr.core_index;
	reg_copy(&vm->core[vm->info[i].start + instr.opcode_pos + instr.index], instr.l1);
	vis_copy(&vm->vis[vm->info[i].start + instr.opcode_pos +
		instr.index], instr.l1, vm, i);
	vis_update(vm, vm->info[i].start + instr.opcode_pos + instr.index);
}

void	vm_sti(t_vm *vm, int i)
{
	t_instr		instr;
	int			idx;
	int			ind;

	ind = 0;
	idx = ((ACB2(instr.acb) & 0b100) != 0);
	instr = init_instr(vm, i);
	instr.core_index += 2;
	get_offset_index(&instr, ACB1(instr.acb), &instr.l1);
	get_offset_index(&instr, ACB2(instr.acb), &instr.l2);
	//ft_printf("calling sti\n");
	if(ACB2(instr.acb) == 3)
	{
		instr.core_index -= 2;
		//instr.index = indirect(instr.vm, instr.i, 1, &instr);
		ind = indirect(instr.vm, instr.i, 1, &instr);
	//ft_printf("indirect = %i, OFF2[%i], idx[%i]\n", indirect(instr.vm, instr.i, idx, &instr), instr.core_index, idx);
		instr.core_index += 2;
	}
	get_offset_index(&instr, ACB3(instr.acb), &instr.l3);
	vm->info[i].index = instr.core_index;
	instr.index = (((ACB2(instr.acb) == 1 ? VAL3(instr.l2) : VAL2(instr.l2)) + (ACB3(instr.acb) == 1 ? VAL3(instr.l3) : VAL2(instr.l3))) & 0xFFFF);
	//ft_printf("instr.index = %x\n", instr.index);
	//ft_printf("reg1 content = %x\n", VAL3(instr.l1));
	//ft_printf("reg2 content = %x\n", VAL3(instr.l2));
	//ft_printf("reg3 content = %x\n", VAL3(instr.l3));
	if (ind)
		instr.index = ind;
	reg_copy(&vm->core[vm->info[i].start + instr.opcode_pos + instr.index],
		instr.l1);
	vis_copy(&vm->vis[vm->info[i].start + instr.opcode_pos + instr.index],
		instr.l1, vm, i);
	vis_update(vm, vm->info[i].start + instr.opcode_pos + instr.index);
}

void	vm_zjmp(t_vm *vm, int i)
{
	t_instr instr;

	instr = init_instr(vm, i);
	instr.acb = 0;
	vm->info[i].index++;
	if (!vm->info[i].carry)
	{
		vm->info[i].index += 2;
		return ;
	}
	vm->info[i].index += get_index_one(&vm->core[vm->info[i].start +
		vm->info[i].index]) - 1;
	vm->info[i].index += 2;
	vm->info[i].carry = 0;
}

void	vm_live(t_vm *vm, int i)
{
	if (vm->core[PARAM1 + 1] == 0xff && vm->core[PARAM1 + 2] == 0xff
			&& vm->core[PARAM1 + 3] == 0xff
			&& (vm->core[PARAM1 + 4] >= 0xff - (vm->num_players - 1)
				&& vm->core[PARAM1 + 4] <= 0xff))
	{
		vm->win_player = vm->core[PARAM1 + 4] - 0xff + 1;
	}
	vm->info[i].live++;
	vm->live++;
	vm->info[i].alive = 1;
	vm->info[i].index += 5;
}

void	vm_aff(t_vm *vm, int i)
{
	t_instr		instr;

	instr = init_instr(vm, i);
	vm->info[i].index++;
	instr.core_index += 2;
	if (!get_offset(&instr, ACB1(instr.acb), &instr.l1))
		return ;
	vm->info[i].index = instr.core_index;
}

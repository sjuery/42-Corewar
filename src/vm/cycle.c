/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <ihodge@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/04/06 11:54:16 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "asm.h"

void	check_executing_processes(t_vm *vm, int *game_end)
{
	t_io *tmp;

	if (!isEmpty(vm->q) && vm->cycle_to_die >= 0)
		*game_end = 0;
	else
	{
		while (!isEmpty(vm->q))
		{
			tmp = dequeue(vm->q);
			free(tmp);
		}
	}
}

void	add_acb_bytes(int op, int *acb_val, int acb)
{
	if (acb == 1)
		*acb_val += REG_CODE;
	else if (acb == 2)
		*acb_val += (g_optab[op].index ? DIR_CODE : DIR_SIZE);
	else if (acb == 3)
		*acb_val += IND_SIZE;
}

void	update_pc(t_io *proc, int op, int acb)
{
	int acb_val;

	acb_val = 2;
	add_acb_bytes(op, &acb_val, ACB1(acb));
	if (g_optab[op].params >= 2)
		add_acb_bytes(op, &acb_val, ACB2(acb));
	if (g_optab[op].params == 3)
		add_acb_bytes(op, &acb_val, ACB3(acb));
	if (acb_val == 0)
		acb_val = 1;
	into_reg(VAL(PC) + acb_val, PC);
}

void	cycle_scheduler(t_vm *vm, int *counter)
{
	if (*counter == 0)
	{
		vm->checks++;
		if (vm->live >= NBR_LIVE)
		{
			vm->checks = 0;
			vm->cycle_to_die -= CYCLE_DELTA;
		}
		vm->live = 0;
		reset_alive_all(vm);
	}
	*counter = (*counter + 1) % vm->cycle_to_die;
	if (vm->checks == MAX_CHECKS)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		vm->checks = 0;
	}
}

void	set_cycle_to_execute(t_vm *vm, t_io *proc)
{
	if (proc->op >= 1 && proc->op <= 16)
		proc->cycle_to_execute = g_optab[proc->op - 1].cycles + vm->cycles;
	else
		proc->cycle_to_execute = vm->cycles + 1;
}

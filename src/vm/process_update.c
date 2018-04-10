/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <ihodge@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/04/06 11:54:16 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "asm.h"

void	process_death(t_vm *vm, t_io *proc)
{
	attron(COLOR_PAIR(vm->vis[PARAM1].player));
	mvprintw((PARAM1) / 64 + 1, ((PARAM1) * 3) % VWRAP, "%02hhx",
				vm->vis[PARAM1].byte);
	attroff(COLOR_PAIR(vm->vis[PARAM1].player));
	vm->process_count--;
	free(proc);
	if (vm->f.noise == 0 && (vm->f.s >= 2))
	{
		system("afplay ./sound/death.mp3 &");
		vm->f.noise++;
	}
}

void	process_three(t_vm *vm, t_io *proc)
{
	vm->vis[PARAM2].previous_index = PARAM1;
	into_reg(VAL(PC) + 1, PC);
	proc->op = vm->core[PARAM1];
	set_cycle_to_execute(vm, proc);
	enqueue(vm->q, proc, proc->executing * proc->cycle_to_execute);
	vis_unhighlight_process(vm, proc);
	vis_highlight_process(vm, proc);
}

void	process_two(t_vm *vm, int previous_index, t_io *proc, int op)
{
	previous_index = PARAM1;
	update_pc(proc, op - 1, vm->core[PARAM2]);
	vm->vis[PARAM1].previous_index = previous_index;
	proc->op = vm->core[PARAM1];
	set_cycle_to_execute(vm, proc);
	enqueue(vm->q, proc, proc->executing * proc->cycle_to_execute);
	vis_unhighlight_process(vm, proc);
	vis_highlight_process(vm, proc);
}

void	process_one(t_vm *vm, int previous_index, t_io *proc, int op)
{
	previous_index = PARAM1;
	g_jt[op - 1](vm, proc);
	vm->vis[PARAM1].previous_index = previous_index;
	proc->op = vm->core[PARAM1];
	set_cycle_to_execute(vm, proc);
	enqueue(vm->q, proc, proc->executing * proc->cycle_to_execute);
	vis_unhighlight_process(vm, proc);
	vis_highlight_process(vm, proc);
}

void	process_update(t_vm *vm)
{
	int		op;
	t_io	*proc;
	t_node	**node;

	node = &(vm->q->max_p);
	while (*node && (*node)->data->cycle_to_execute <= vm->cycles)
	{
		proc = dequeue(vm->q);
		if (PARAM1 >= MEM_SIZE)
			into_reg(PARAM1 % MEM_SIZE, PC);
		op = proc->op;
		if ((op > 0 && op < 17) && proc->cycle_to_execute == vm->cycles &&
				((g_optab[op - 1].acb &&
				  valid_acb(op - 1, vm->core[PARAM2], vm, proc)) ||
				 !g_optab[op - 1].acb) && proc->executing)
			process_one(vm, 0, proc, op);
		else if (op > 0 && op < 17 && proc->cycle_to_execute
				== vm->cycles && proc->executing)
			process_two(vm, 0, proc, op);
		else if (proc->cycle_to_execute == vm->cycles && proc->executing)
			process_three(vm, proc);
		else if (!proc->executing)
			process_death(vm, proc);
	}
}

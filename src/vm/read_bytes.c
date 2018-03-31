/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bytes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/03/30 17:30:11 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "asm.h"

void	check_executing_processes(t_vm *vm, int *game_end)
{
	int i;

	i = 0;
	while (i < vm->process_count)
	{
		if (vm->info[i].executing == 1)
			*game_end = 0;
		i++;
	}
}

void	process_update(t_vm *vm, int i)
{
	int op;
	int previous_index;

	if (PARAM1 > MEM_SIZE - 1)
		into_reg(vm->info[i].start * -1, PC);
	op = vm->core[PARAM1];
	vis_unhighlight_process(vm, i);
	vis_highlight_process(vm, i);
	vis_print_debug(vm);
	if ((op > 0 && op < 17) &&
		vm->info[i].wait_cycle == g_optab[op - 1].cycles - 1)
	{
		ft_printf("cycle[%i], op[%i] %s process [%i]\n", vm->cycles, op, g_optab[op -1].opstr, i);
		previous_index = PARAM1;
		g_jt[op - 1](vm, i);
		//jumptable(op, vm, i);
		vm->info[i].wait_cycle = 0;
		vm->info[i].waiting = 0;
		vm->vis[PARAM1].previous_index = previous_index;
	}
	else if (op > 0 && op < 17)
	{
		if (vm->info[i].waiting == 10)
			vm->info[i].wait_cycle++;
		else if ((g_optab[op - 1].acb &&
					valid_acb(op - 1, vm->core[PARAM2], vm, i))
				|| !g_optab[op - 1].acb)
		{
			vm->info[i].waiting = 10;
			vm->info[i].wait_cycle++;
			vm->vis[PARAM1].previous_index = PARAM1;
		}
		else
		{
			ft_printf("INVALID; op[%i] cycle[%i]\n", op, vm->cycles);
			vm->vis[PARAM2].previous_index = PARAM1;
			into_reg(VAL(PC) + 1, PC);//update_pc function according to ACB
		}
	}
	else
	{
		vm->vis[PARAM2].previous_index = PARAM1;
		into_reg(VAL(PC) + 1, PC);
	}
}

void	cycle_scheduler(t_vm *vm, int *counter)
{
	if (*counter == 0)
	{
		vm->checks++;
		if (vm->live >= NBR_LIVE)
			vm->cycle_to_die -= CYCLE_DELTA;
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

void	read_bytes(t_vm *vm, int i, int game_end, int counter)
{
	while (1)
	{
		i = vm->process_count - 1;
		vm->cycles++;
		while (i >= 0)
		{
			if (vm->info[i].executing == 1)
				process_update(vm, i);
			i--;
		}
		if (vm->f.g)
		{
			refresh();
			usleep(10000);
		}
		//ft_printf("processes[%i], cycle[%i]\n", vm->process_count, vm->cycles);
		check_executing_processes(vm, &game_end);
		cycle_scheduler(vm, &counter);
		if (game_end)
			break ;
		game_end = 1;
	}
	endwin();
	ft_printf("\nContestant %i, \"%s\", has won !\n", vm->win_player,
		vm->info[vm->win_player - 1].head->prog_name);
}

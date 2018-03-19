/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bytes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/03/19 00:25:17 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "asm.h"
#define VWRAP 192
void	reset_alive_all(t_vm *vm)
{
	int i;

	i = 0;
	while (i < vm->process_count)
	{
		if (vm->info[i].alive == 0)
			vm->info[i].executing = 0;
		vm->info[i].alive = 0;
		i++;
	}
}

void	reset_alive(t_vm *vm, int i)
{
	if (vm->info[i].alive == 0)
		vm->info[i].executing = 0;
	vm->info[i].alive = 0;
}

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

void	vis_highlight_process(t_vm *vm, int i)
{
	attron(COLOR_PAIR(5));
	mvprintw((vm->info[i].start + vm->info[i].index) / 64 + 1,
			((vm->info[i].start + vm->info[i].index) * 3) % VWRAP,
			"%02hhx", vm->vis[vm->info[i].start + vm->info[i].index].byte);
	attroff(COLOR_PAIR(5));
}

void	vis_unhighlight_process(t_vm *vm, int i)
{
	if (vm->info[i].start + vm->vis[vm->info[i].start + vm->info[i].index].previous_index)
	{
		attron(COLOR_PAIR(vm->vis[vm->vis[vm->info[i].start + vm->info[i].index].previous_index].player));
		mvprintw((vm->vis[vm->info[i].start + vm->info[i].index].previous_index) / 64 + 1,
				((vm->vis[vm->info[i].start + vm->info[i].index].previous_index) * 3) % VWRAP,
				"%02hhx", vm->vis[vm->vis[vm->info[i].start + vm->info[i].index].previous_index].byte);
		attroff(COLOR_PAIR(vm->vis[vm->vis[vm->info[i].start + vm->info[i].index].previous_index].player));
	}
}

void	process_update(t_vm *vm, int i)
{
	int op;
	int previous_index;

	if (vm->info[i].start + vm->info[i].index > MEM_SIZE - 1)//should this be >= MEM_SIZE - 1?
		vm->info[i].index = vm->info[i].start * -1;
	op = vm->core[vm->info[i].start + vm->info[i].index];
	vis_unhighlight_process(vm, i);
	if ((op > 0 && op < 17) && vm->info[i].wait_cycle == g_optab[op - 1].cycles - 1)
	{
		vis_highlight_process(vm, i);
		previous_index = vm->info[i].start + vm->info[i].index;
		jumptable(op, vm, i);
		vm->info[i].wait_cycle = 0;
		vm->vis[vm->info[i].start + vm->info[i].index].previous_index = previous_index;
	}
	else if (op > 0 && op < 17)
	{
		vis_highlight_process(vm, i);
		vm->info[i].wait_cycle++;
	}
	else
	{
		vis_highlight_process(vm, i);
		vm->vis[vm->info[i].start + vm->info[i].index + 1].previous_index = vm->info[i].start +
			vm->info[i].index;
		vm->info[i].index++;
	}
	vm->info[i].cycles++;
	//if (vm->info[i].cycles % vm->cycle_to_die == 0)
	//	reset_alive(vm, i);
}

//implement decrease of CYCLE_TO_DIE with NBR_LIVE
//do processes need to keep track of how many cycles since birth? each have their own cycle count?
//endianness

void	cycle_scheduler(t_vm *vm, int *counter)
{
	if (*counter == 0)
	{
		vm->checks++;
		reset_alive_all(vm);
	}
	*counter = (*counter + 1) % vm->cycle_to_die;
	if (vm->checks == MAX_CHECKS)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		vm->checks = 0;
	}
}

void	read_bytes(t_vm *vm, int i)
{
	int game_end;
	int	counter;

	counter = 1;
	game_end = 1;
	while (1)
	{
		i = vm->process_count - 1;
		++vm->cycles;
		while (i >= 0)
		{
			if (vm->info[i].executing == 1)
				process_update(vm, i);
			i--;
		}
		refresh();
		usleep(50000);
		check_executing_processes(vm, &game_end);
		cycle_scheduler(vm, &counter);
		//ft_printf("cycle[%i]\n", vm->cycles);
		if (game_end)
			break ;
		game_end = 1;
	}
	endwin();
	ft_printf("\nContestant %i, \"%s\", has won !\n", vm->win_player, vm->info[vm->win_player - 1].header + 4);
}

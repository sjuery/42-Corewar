/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bytes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/03/16 17:01:29 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "asm.h"
#define VWRAP 192

void	reset_alive_all(t_vm *vm)
{
	int i;

	i = 0;
	//ft_printf("RESETING ALIVE cycle[%i] todie[%i]\n", vm->cycles, vm->cycle_to_die);
	while (i < vm->process_count)
	{
		if (vm->info[i].alive == 0)
		{
			//ft_printf("IM DED! cycle[%i] process[%i]\n", vm->cycles, i);
			vm->info[i].executing = 0;
		}
		vm->info[i].alive = 0;
		i++;
	}
}

void	reset_alive(t_vm *vm, int i)
{
	//ft_printf("RESETING ALIVE cycle[%i] todie[%i]\n", vm->cycles, vm->cycle_to_die);
	if (vm->info[i].alive == 0)
	{
		//ft_printf("IM DED! cycle[%i] process[%i]\n", vm->cycles, i);
		vm->info[i].executing = 0;
	}
	vm->info[i].alive = 0;
}

void	check_executing_processes(t_vm *vm, int *game_end)
{
	int i;

	i = 0;
	while (i < vm->process_count)
	{
		if (vm->info[i].executing == 1)
		{
			//ft_printf("IM STILL EXECUTING! proceess[%i];\n", i);
			*game_end = 0;
		}
		i++;
	}
}

void	process_update(t_vm *vm, int i)
{
	int op;
	int previous_index;

	//ft_printf("\nProcess number[%i], Byte Read [%#0.2hhx], Index [%i]", i, vm->core[vm->info[i].start + vm->info[i].index], vm->info[i].index);
	if (vm->info[i].start + vm->info[i].index > 4095)//wrapping around the core
		vm->info[i].index = vm->info[i].start * -1;
	op = vm->core[vm->info[i].start + vm->info[i].index];
	if (vm->info[i].start + vm->vis[vm->info[i].start + vm->info[i].index].previous_index)//unhighlight shit
	{
		attron(COLOR_PAIR(vm->vis[vm->vis[vm->info[i].start + vm->info[i].index].previous_index].player));
		mvprintw((vm->vis[vm->info[i].start + vm->info[i].index].previous_index)
				/ 64 + 1, ((vm->vis[vm->info[i].start + vm->info[i].index].previous_index) * 2 +
					(vm->vis[vm->info[i].start + vm->info[i].index].previous_index)) % VWRAP,
				"%02hhx", vm->vis[vm->vis[vm->info[i].start + vm->info[i].index].previous_index].byte);
		attroff(COLOR_PAIR(vm->vis[vm->vis[vm->info[i].start + vm->info[i].index].previous_index].player));
	}
	if (op > 0 && op < 17 && vm->info[i].wait_cycle == g_optab[op - 1].cycles - 1)//highlight start of instruction
	{
		attron(COLOR_PAIR(5));
		mvprintw((vm->info[i].start + vm->info[i].index) / 64 + 1,
				((vm->info[i].start + vm->info[i].index) * 2 + (vm->info[i].start + vm->info[i].index ))
				% VWRAP, "%02hhx", vm->vis[vm->info[i].start + vm->info[i].index + 1].byte);
		//printf("process[%i] cycles[%i] op[%02hhx]\n", i, vm->cycles, (unsigned char)op);
		previous_index = vm->info[i].start + vm->info[i].index;
		jumptable(op, vm, i);
		//ft_putchar('\n');
		vm->info[i].wait_cycle = 0;
		vm->vis[vm->info[i].start + vm->info[i].index].previous_index = previous_index;
		attroff(COLOR_PAIR(5));
	}
	else if (op > 0 && op < 17)
	{
		attron(COLOR_PAIR(5));
		mvprintw((vm->info[i].start + vm->info[i].index) / 64 + 1,
				((vm->info[i].start + vm->info[i].index) * 2 + (vm->info[i].start + vm->info[i].index ))
				% VWRAP, "%02hhx", vm->vis[vm->info[i].start + vm->info[i].index + 1].byte);
		attroff(COLOR_PAIR(5));
		vm->info[i].wait_cycle++;
	}
	else//highlight each process
	{
		attron(COLOR_PAIR(5));
		mvprintw((vm->info[i].start + vm->info[i].index) / 64 + 1,
				((vm->info[i].start + vm->info[i].index) * 2 + vm->info[i].start + vm->info[i].index) % VWRAP,
				"%02hhx", vm->vis[vm->info[i].start + vm->info[i].index].byte);
		vm->vis[vm->info[i].start + vm->info[i].index + 1].previous_index = vm->info[i].start + vm->info[i].index;
		vm->info[i].index++;
		attroff(COLOR_PAIR(5));
	}
	vm->info[i].cycles++;
	//if (vm->info[i].cycles % vm->cycle_to_die == 0)
	//	reset_alive(vm, i);
}

//implement decrease of CYCLE_TO_DIE with NBR_LIVE
//do processes need to keep track of how many cycles since birth? each have their own cycle count?
//endianness

void	read_bytes(t_vm *vm, int i)
{
	int game_end;
	int	counter;

	counter = 1;
	game_end = 1;
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
		refresh();
	usleep(50000);
		//print_curses(vm);
		//ft_printf("cycle [%i] cycle_to_die [%i]\n", vm->cycles, vm->cycle_to_die);
		check_executing_processes(vm, &game_end);
		if (counter == 0)
		{
			vm->checks++;
			reset_alive_all(vm);
		}
		counter = (counter + 1) % vm->cycle_to_die;;
		if (vm->checks == MAX_CHECKS)
		{
			vm->cycle_to_die -= CYCLE_DELTA;
			vm->checks = 0;
		}
		if (game_end)
			break ;
		//else
		//	print_core(vm->core, -1);//refresh();
		game_end = 1;
	}
	endwin();
	print_core(vm->core, -1);
	ft_printf("\nContestant %i, \"%s\", has won !\n", vm->win_player, vm->info[vm->win_player - 1].header + 4);
}

//make another ex.s champion that actually calls live with it's name to see if live works

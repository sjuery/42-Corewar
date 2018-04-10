/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bytes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <ihodge@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/04/09 20:56:51 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "asm.h"

void	gui_interaction(t_vm *vm, int c)
{
	vis_print_debug(vm, 0);
	refresh();
	if (((c = getch()) != ERR) && vm->f.r != 1)
	{
		if (c == 'q' && (vm->f.delay - 10000) >= 0)
			vm->f.delay -= 10000;
		if (c == 'r' && (vm->f.delay + 10000) <= 1000000)
			vm->f.delay += 10000;
		if (c == 'w' && (vm->f.delay - 1000) >= 0)
			vm->f.delay -= 1000;
		if (c == 'e' && (vm->f.delay + 10000) <= 1000000)
			vm->f.delay += 1000;
		if (c == 27)
		{
			endwin();
			exit(0);
		}
	}
	usleep(vm->f.delay);
}

void	read_bytes(t_vm *vm, int game_end, int counter)
{
	if (vm->f.r == 1 && vm->f.g == 1)
		system("afplay ./sound/star.mp3 &");
	while (1)
	{
		process_update(vm);
		if (vm->f.g)
			gui_interaction(vm, 0);
		if (vm->f.d && vm->f.d == vm->cycles)
			print_core(vm->core, -1);
		cycle_scheduler(vm, &counter);
		check_executing_processes(vm, &game_end);
		vm->cycles++;
		if (game_end)
			break ;
		game_end = 1;
		vm->f.noise = 0;
	}
	endwin();
	free(vm->vis);
	free(vm->core);
	free(vm->q);
	ft_printf("\nContestant %i, \"%s\", has won! CTD[%i] Cycle[%i] PC[%i]\n",
		vm->win_player, vm->head[vm->win_player - 1].prog_name,
		vm->cycle_to_die, vm->cycles, vm->process_count);
}

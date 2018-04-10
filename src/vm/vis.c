/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <ihodge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/04/06 11:52:13 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "asm.h"

void	vis_print_debug(t_vm *vm, int i)
{
	attron(0);
	mvprintw(5, VWRAP + 4, "Cycle : %i", vm->cycles);
	mvprintw(7, VWRAP + 4, "Processes : %i", vm->process_count);
	mvprintw(9, VWRAP + 4, "Cycle_To_Die : %4i", vm->cycle_to_die);
	attroff(0);
	while (i < vm->num_players)
	{
		attron(COLOR_PAIR(i + 1));
		mvprintw(11 + (i * 2), VWRAP + 4, "Player %i : %s", i + 1,
				vm->head[i].prog_name);
		attroff(COLOR_PAIR(i + 1));
		i++;
	}
	attron(0);
	mvprintw(19, VWRAP + 4, "Lives in current period : %i", vm->live);
	mvprintw(21, VWRAP + 4, "Winning Player : %i", vm->win_player);
	mvprintw(23, VWRAP + 4, "MAX_CHECKS : %i", MAX_CHECKS);
	mvprintw(25, VWRAP + 4, "NBR_LIVE : %i", NBR_LIVE);
	mvprintw(27, VWRAP + 4, "CYCLE_DELTA : %i", CYCLE_DELTA);
	if (vm->f.r == 1)
		mvprintw(29, VWRAP + 4, "DELAY : NOT APPLICABLE");
	else
		mvprintw(29, VWRAP + 4, "DELAY : %7i", vm->f.delay);
	attroff(0);
}

void	vis_init_color(void)
{
	static short	schizo[] = {
		COLOR_CYAN, COLOR_RED, COLOR_YELLOW, COLOR_GREEN,
		COLOR_BLACK, COLOR_WHITE, COLOR_MAGENTA };

	init_pair(7, schizo[rand() % 6], schizo[rand() % 6]);
	init_pair(8, schizo[rand() % 6], schizo[rand() % 6]);
	init_pair(9, schizo[rand() % 6], schizo[rand() % 6]);
	init_pair(10, schizo[rand() % 6], schizo[rand() % 6]);
	init_pair(11, schizo[rand() % 6], schizo[rand() % 6]);
	init_pair(12, schizo[rand() % 6], schizo[rand() % 6]);
	init_pair(13, schizo[rand() % 6], schizo[rand() % 6]);
}

void	vis_update(t_vm *vm, int index)
{
	static long	pain;

	if (vm->f.r == 1 && pain % 150 == 0)
	{
		vis_init_color();
		pain++;
	}
	if (vm->f.r == 1)
		attron(COLOR_PAIR(rand() % 7 + 7));
	else
		attron(COLOR_PAIR(vm->vis[index % MEM_SIZE].player));
	mvprintw((index % MEM_SIZE / 64 + 1) %
		MEM_SIZE, (index * 3) % VWRAP, "%02hhx",
		vm->vis[(index) % MEM_SIZE].byte);
	mvprintw(((index + 1) % MEM_SIZE / 64 + 1) %
		MEM_SIZE, ((index + 1) * 3) % VWRAP, "%02hhx",
		vm->vis[(index + 1) % MEM_SIZE].byte);
	mvprintw(((index + 2) % MEM_SIZE / 64 + 1) %
		MEM_SIZE, ((index + 2) * 3) % VWRAP, "%02hhx",
		vm->vis[(index + 2) % MEM_SIZE].byte);
	mvprintw(((index + 3) % MEM_SIZE / 64 + 1) %
		MEM_SIZE, ((index + 3) * 3) % VWRAP, "%02hhx",
		vm->vis[(index + 3) % MEM_SIZE].byte);
	attroff(COLOR_PAIR(vm->vis[index % MEM_SIZE].player));
	refresh();
}

void	vis_copy(t_vis *dest, int src, t_io *proc, int index)
{
	dest[index % MEM_SIZE].byte = (src >> 24) % 0x100;
	dest[(index + 1) % MEM_SIZE].byte = (src >> 16) % 0x100;
	dest[(index + 2) % MEM_SIZE].byte = (src >> 8) % 0x100;
	dest[(index + 3) % MEM_SIZE].byte = src % 0x100;
	dest[index % MEM_SIZE].player = proc->player_int;
	dest[(index + 1) % MEM_SIZE].player = proc->player_int;
	dest[(index + 2) % MEM_SIZE].player = proc->player_int;
	dest[(index + 3) % MEM_SIZE].player = proc->player_int;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <ihodge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/03/23 14:42:12 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "asm.h"

void	vis_highlight_process(t_vm *vm, int i)
{
	attron(COLOR_PAIR(5));
	mvprintw((PARAM1) / 64 + 1, ((PARAM1) * 3) % VWRAP, "%02hhx",
			vm->vis[PARAM1].byte);
	attroff(COLOR_PAIR(5));
}

void	vis_unhighlight_process(t_vm *vm, int i)
{
	attron(COLOR_PAIR(vm->vis[vm->vis[PARAM1].previous_index].player));
	mvprintw((vm->vis[PARAM1].previous_index) / 64 + 1,
			((vm->vis[PARAM1].previous_index) * 3) % VWRAP,
			"%02hhx", vm->vis[vm->vis[PARAM1].previous_index].byte);
	attroff(COLOR_PAIR(vm->vis[vm->vis[PARAM1].previous_index].player));
}

void	vis_print_debug(t_vm *vm)
{
	attron(0);
	mvprintw(5, VWRAP + 5, "Cycle : %i", vm->cycles);
	mvprintw(7, VWRAP + 5, "Processes : %i", vm->process_count);
	mvprintw(9, VWRAP + 5, "Cycle_To_Die : %i", vm->cycle_to_die);
	mvprintw(11, VWRAP + 5, "Live called in current period : %i", vm->live);
	mvprintw(13, VWRAP + 5, "Winning Player : %i", vm->win_player);
	mvprintw(15, VWRAP + 5, "MAX_CHECKS : %i", MAX_CHECKS);
	mvprintw(17, VWRAP + 5, "NBR_LIVE : %i", NBR_LIVE);
	mvprintw(19, VWRAP + 5, "CYCLE_DELTA : %i", CYCLE_DELTA);
	attroff(0);
}

void	vis_copy(t_vis *dest, unsigned char *src, t_vm *vm, int i)
{
	dest[0].byte = src[0];
	dest[1].byte = src[1];
	dest[2].byte = src[2];
	dest[3].byte = src[3];
	dest[0].player = vm->info[i].player_int;
	dest[1].player = vm->info[i].player_int;
	dest[2].player = vm->info[i].player_int;
	dest[3].player = vm->info[i].player_int;
}

void	vis_update(t_vm *vm, int index)
{
	attron(COLOR_PAIR(vm->vis[index].player));
	mvprintw(index / 64 + 1, (index * 3) % VWRAP, "%02hhx",
		vm->vis[index].byte);
	mvprintw((index + 1) / 64 + 1, ((index + 1) * 3) % VWRAP, "%02hhx",
		vm->vis[index + 1].byte);
	mvprintw((index + 2) / 64 + 1, ((index + 2) * 3) % VWRAP, "%02hhx",
		vm->vis[index + 2].byte);
	mvprintw((index + 3) / 64 + 1, ((index + 3) * 3) % VWRAP, "%02hhx",
		vm->vis[index + 3].byte);
	attroff(COLOR_PAIR(vm->vis[index].player));
	refresh();
}

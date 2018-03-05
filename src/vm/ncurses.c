/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/02/07 17:43:29 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		setcolor(int i, t_vm *vm)
{
	if (i >= 0 && i <= vm->info[0].head.prog_size)
		return (1);
	else if (i >= (1 * (4096 / vm->num_players)) && i <= vm->info[1].head.prog_size + (1 * (4096 / vm->num_players)))
		return (2);
	else if (i >= (2 * (4096 / vm->num_players)) && i <= vm->info[2].head.prog_size + (2 * (4096 / vm->num_players)))
		return (3);
	else if (i >= (3 * (4096 / vm->num_players)) && i <= vm->info[3].head.prog_size + (3 * (4096 / vm->num_players)))
		return (4);
	else
		return (0);
}

void	init_curses(t_vm *vm)
{
	int i = -1;
	int x = 0;
	int y = 0;
	int color = 0;

	initscr();
	curs_set(false);

	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);

	while (++i < 4096)
	{
		color = setcolor(i, vm);
		attron(COLOR_PAIR(color));
		if (i % 64 == 0)
		{
			x++;
			y = 0;
		}
		if (vm->core[i] < 16 && vm->core[i] >= 0)
		{
			mvprintw(x, y++, "0");
			mvprintw(x, y++, "%hhx", vm->core[i]);
		}
		else
		{
			mvprintw(x, y, "%hhx", vm->core[i]);
			y += 2;
		}
		mvprintw(x, y++, " ");
		attroff(COLOR_PAIR(2));
	}

	refresh();
	sleep(5);
	endwin();
}

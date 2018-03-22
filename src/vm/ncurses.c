/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/03/20 23:14:47 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init_curses(void)
{
	initscr();
	curs_set(false);
	keypad(stdscr, TRUE);
	noecho();
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_WHITE);
	init_pair(6, COLOR_CYAN, COLOR_CYAN);
}

void	print_border(void)
{
	int x;
	int y;

	x = -1;
	y = -1;
	attron(COLOR_PAIR(5));
	while (x <= 230)
		mvprintw(0, ++x, "b");
	while (y < 65)
		mvprintw(++y, 192, "%02c", 'b');
	y = -1;
	while (y < 65)
		mvprintw(++y, x, "%02c", 'b');
	x = -1;
	while (x <= 230)
		mvprintw(y, ++x, "b");
	attroff(COLOR_PAIR(5));
}

void	print_curses(t_vm *vm, int i, int x, int y)
{
	int color;

	color = 0;
	clear();
	print_border();
	while (++i < 4096)
	{
		attron(COLOR_PAIR(vm->vis[i].player));
		if (i % 64 == 0)
		{
			x++;
			y = 0;
		}
		mvprintw(x, y, "%02hhx", vm->vis[i].byte);
		y += 2;
		mvprintw(x, y++, " ");
		attroff(COLOR_PAIR(vm->vis[i].player));
	}
	refresh();
	usleep(50000);
	endwin();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_highlight.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <ihodge@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/03/25 20:44:07 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	vis_highlight_process(t_vm *vm, t_io *proc)
{
	attron(COLOR_PAIR(5));
	mvprintw((PARAM1) / 64 + 1, ((PARAM1) * 3) % VWRAP, "%02hhx",
			vm->vis[PARAM1].byte);
	attroff(COLOR_PAIR(5));
}

void	vis_unhighlight_process(t_vm *vm, t_io *proc)
{
	attron(COLOR_PAIR(vm->vis[vm->vis[PARAM1].previous_index].player));
	mvprintw((vm->vis[PARAM1].previous_index) / 64 + 1,
			((vm->vis[PARAM1].previous_index) * 3) % VWRAP,
			"%02hhx", vm->vis[vm->vis[PARAM1].previous_index].byte);
	attroff(COLOR_PAIR(vm->vis[vm->vis[PARAM1].previous_index].player));
}

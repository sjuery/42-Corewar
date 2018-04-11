/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_binary.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <ihodge@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 19:55:29 by ihodge            #+#    #+#             */
/*   Updated: 2018/04/11 11:49:39 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		print_sp_nl(t_assembler *st, int *y)
{
	if (*y % 2 == 0 && *y % 16)
		ft_dprintf(st->corefile, " ");
	if (*y % 16 == 0)
		ft_dprintf(st->corefile, "\n");
	(*y)++;
}

void		break_shit_up(t_assembler *st, int size, int res)
{
	int		i;
	int		byte;
	char	ch;

	i = size - 1;
	byte = res;
	ch = 0;
	while (i >= 0)
	{
		byte = res >> (i * 8);
		ch = byte;
		ft_dprintf(st->corefile, "%c", ch);
		i--;
	}
}

void		print_header(t_assembler *st, int i, int j)
{
	ft_dprintf(st->corefile, "%c%c%c%c", 0, 234, 131, 243);
	while (++i < PROG_NAME_LENGTH)
		ft_dprintf(st->corefile, "%c", (char)st->prog_name[i]);
	while (++i < PROG_NAME_LENGTH + 8)
	{
		if (1 >= PROG_NAME_LENGTH + 8 - i)
		{
			if (ft_strlen(ft_itoa_base(st->final_offset, 16, 1)) < 2)
				ft_dprintf(st->corefile, "%c", 0);
			ft_dprintf(st->corefile, "%c", (char)(st->final_offset >> 8));
			ft_dprintf(st->corefile, "%c", (char)st->final_offset);
		}
		else if (1 < PROG_NAME_LENGTH + 7 - i)
			ft_dprintf(st->corefile, "%c", 0);
	}
	while (++j < COMMENT_LENGTH)
		ft_dprintf(st->corefile, "%c", (char)st->comment[j]);
	while (++j < COMMENT_LENGTH + 4)
		ft_dprintf(st->corefile, "%c", 0);
}

void		print_parameters(t_assembler *st, int i, int j)
{
	int		res;

	while (st->arr[i]->params[++j])
	{
		if (check_param_type(st->arr[i]->params[j], st->arr[i]->op - 1, j)
				== DIR_CODE && st->arr[i]->params[j][0] == DIRECT_CHAR)
		{
			res = ft_atoi(st->arr[i]->params[j] + 1);
			if (g_optab[st->arr[i]->op - 1].index)
				break_shit_up(st, IND_SIZE, res);
			else
				break_shit_up(st, DIR_SIZE, res);
		}
		else if (check_param_type(st->arr[i]->params[j], st->arr[i]->op - 1, j)
				== REG_CODE)
		{
			res = ft_atoi(st->arr[i]->params[j] + 1);
			ft_dprintf(st->corefile, "%c", (char)res);
		}
		else
		{
			res = ft_atoi(st->arr[i]->params[j]);
			break_shit_up(st, IND_SIZE, res);
		}
	}
}

void		print_shit(t_assembler *st)
{
	int		i;
	int		y;
	char	ch;

	i = 0;
	y = 5;
	print_header(st, -1, -1);
	while (st->arr[i])
	{
		ch = st->arr[i]->op;
		ft_dprintf(st->corefile, "%c", ch);
		if (st->arr[i]->acb)
		{
			ch = st->arr[i]->acb;
			ft_dprintf(st->corefile, "%c", ch);
		}
		print_parameters(st, i, -1);
		i++;
	}
}

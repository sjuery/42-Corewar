/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_binary.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <ihodge@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 19:55:29 by ihodge            #+#    #+#             */
/*   Updated: 2018/04/09 12:28:42 by ihodge           ###   ########.fr       */
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

void		break_shit_up(t_assembler *st, int size, int res, int *y)
{
	(void)*y;
	int i;
	int byte;
	char ch;

	i = size - 1;
	byte = res;
	ch = 0;
	while (i >= 0)
	{
		byte = res >> (i * 8);
		ch = byte;
		ft_dprintf(st->corefile, "%c", ch);
		//ft_dprintf(st->corefile, "%02hhx", byte);
		//print_sp_nl(st, y);
		i--;
	}
}

void		print_header(t_assembler *st, int *y)
{
	int i = 0;
	int j = 0;
	char ch;
	(void)*y;

	//ft_dprintf(st->corefile, "00ea 83f3 ");
	//will need to hard code this as chars 0, 234, 131, 243
	ft_dprintf(st->corefile, "%c%c%c%c", 0, 234, 131, 243);
	while (i < PROG_NAME_LENGTH)
	{
		ch = st->prog_name[i];
		ft_dprintf(st->corefile, "%c", ch);
		//ft_dprintf(st->corefile, "%02x", st->prog_name[i]);
		//print_sp_nl(st, y);
		i++;
	}
	while (i < PROG_NAME_LENGTH + 8)//8 bytes for the size in bytes of commands
	{
		if(1 >= PROG_NAME_LENGTH + 8 - i)
		{
			if(ft_strlen(ft_itoa_base(st->final_offset, 16, 1)) < 2)
				ft_dprintf(st->corefile, "%c", 0);
				//ft_dprintf(st->corefile, "%02x", 0);
			ft_dprintf(st->corefile, "%c", (char)(st->final_offset >> 8));
			ft_dprintf(st->corefile, "%c", (char)st->final_offset);
			//ft_dprintf(st->corefile, "%04x", st->final_offset);
		}
		else if (1 < PROG_NAME_LENGTH + 7 - i)
			ft_dprintf(st->corefile, "%c", 0);
			//ft_dprintf(st->corefile, "%02x", 0);
		//print_sp_nl(st, y);
		i++;
	}
	while (j < COMMENT_LENGTH)
	{
		ch = st->comment[j];
		ft_dprintf(st->corefile, "%c", ch);
		//ft_dprintf(st->corefile, "%02x", st->comment[j]);
		//print_sp_nl(st, y);
		j++;
	}
	while (j < COMMENT_LENGTH + 4)
	{
		ft_dprintf(st->corefile, "%c", 0);
		//ft_dprintf(st->corefile, "%02x", 0);
		//print_sp_nl(st, y);
		j++;
	}
}

void		print_parameters(t_assembler *st, int i, int *y)
{
	int j;
	int res;
	char ch;

	j = 0;
	while (st->arr[i]->params[j])
	{
		if (check_param_type(st->arr[i]->params[j], st->arr[i]->op - 1, j) == DIR_CODE && st->arr[i]->params[j][0] == DIRECT_CHAR)
		{
			res = ft_atoi(st->arr[i]->params[j] + 1);
			if (g_optab[st->arr[i]->op - 1].index)
				break_shit_up(st, IND_SIZE, res, y);
			else
				break_shit_up(st, DIR_SIZE, res, y);
		}
		else if (check_param_type(st->arr[i]->params[j], st->arr[i]->op - 1, j) == REG_CODE)
		{
			res = ft_atoi(st->arr[i]->params[j] + 1);
			ch = (char)res;
			ft_dprintf(st->corefile, "%c", ch);
			//ft_dprintf(st->corefile, "%02x", res);
			//print_sp_nl(st, y);
		}
		else
		{
			res = ft_atoi(st->arr[i]->params[j]);
			break_shit_up(st, IND_SIZE, res, y);
		}
		j++;
	}
}

void		print_shit(t_assembler *st)
{
	int i;
	int y;
	unsigned char ch;

	i = 0;
	y = 5;
	print_header(st, &y);
	while (st->arr[i])
	{
		ch = st->arr[i]->op;
		ft_dprintf(st->corefile, "%c", ch);
		//ft_dprintf(st->corefile, "%02x", st->arr[i]->op);
		//print_sp_nl(st, &y);
		if (st->arr[i]->acb)
		{
			ch = st->arr[i]->acb;
			ft_dprintf(st->corefile, "%c", ch);
			//ft_dprintf(st->corefile, "%02x", st->arr[i]->acb);
			//print_sp_nl(st, &y);
		}
		print_parameters(st, i, &y);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 19:55:29 by sjuery            #+#    #+#             */
/*   Updated: 2018/02/21 19:24:49 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

//endiannesssssss
//somehow im 16 bytes off, actual assembler printing 2192 bytes, I'm printing 2176 bytes (prog_name length + comment_length) for header + corewar_exec_magic (+ 4 bytes); prog_name is actual header is 138 bytes
//comments are 2154 bytes
//labels can be 4 bytes or 2 (index)
static void convert_name(t_assembler *st)
{
    int name_len;
	int i = 0;

    name_len = 1;
	st->prog_name = ft_memalloc(sizeof(int) * PROG_NAME_LENGTH);
    while(st->line[st->i] != '"')
        st->i++;
    st->i++;
    while(st->line[st->i] != '"')
    {
		st->prog_name[i] = (int)st->line[st->i];
		i++;
		st->i++;
        name_len++;
    }
}

static void convert_description(t_assembler *st)
{
    int desc_len;
	int i = 0;

    desc_len = 1;
    st->i = 0;
	st->comment = ft_memalloc(sizeof(int) * COMMENT_LENGTH);
    while(st->line[st->i] != '"')
        st->i++;
    st->i++;
    while(st->line[st->i] != '"')
    {
		st->comment[i] = (int)st->line[st->i];
		i++;
		st->i++;
        desc_len++;
    }
}

void		print_sp_nl(int *y)
{
	if (*y % 2 == 0 && *y % 16)
		ft_putchar(' ');
	if (*y % 16 == 0)
		ft_putchar('\n');
	(*y)++;
}

void		break_shit_up(int size, int res, int *y)
{
	int i;
	int byte;

	i = size - 1;
	byte = res;
	while (i >= 0)
	{
		byte = res >> (i * 8);
		ft_printf("%02hhx", byte);
		print_sp_nl(y);
		i--;
	}
}

void		print_header(t_assembler *st, int *y)
{
	int i = 0;
	int j = 0;

	ft_putstr("00ea 83f3 ");
	while (i < PROG_NAME_LENGTH)
	{
		ft_printf("%02x", st->prog_name[i]);
		print_sp_nl(y);
		i++;
	}
	while (i < PROG_NAME_LENGTH + 8)//random ass bytes outta nowhere
	{
		ft_printf("%02x", 0);
		print_sp_nl(y);
		i++;
	}
	while (j < COMMENT_LENGTH)
	{
		ft_printf("%02x", st->comment[j]);
		print_sp_nl(y);
		j++;
	}
	while (j < COMMENT_LENGTH + 4)//?????????
	{
		ft_printf("%02x", 0);
		print_sp_nl(y);
		j++;
	}
}

void		print_parameters(t_assembler *st, int i, int *y)
{
	int j;
	int res;

	j = 0;
	while (st->arr[i]->params[j])
	{
		if (check_param_type(st->arr[i]->params[j], st->arr[i]->op - 1, j) == DIR_CODE)
		{
			res = ft_atoi(st->arr[i]->params[j] + 1);
			if (g_optab[st->arr[i]->op - 1].index)
				break_shit_up(IND_SIZE, res, y);
			else
				break_shit_up(DIR_SIZE, res, y);
		}
		else if (check_param_type(st->arr[i]->params[j], st->arr[i]->op - 1, j) == REG_CODE)
		{
			res = ft_atoi(st->arr[i]->params[j] + 1);
			ft_printf("%02x", res);
			print_sp_nl(y);
		}
		else
		{
			res = ft_atoi(st->arr[i]->params[j]);
			break_shit_up(IND_SIZE, res, y);
		}
		j++;
	}
}

void		print_shit(t_assembler *st)
{
	int i;
	int y;

	i = 0;
	y = 5;
	print_header(st, &y);
	while (st->arr[i])
	{
		ft_printf("%02x", st->arr[i]->op);
		print_sp_nl(&y);
		if (st->arr[i]->acb)
		{
			ft_printf("%02x", st->arr[i]->acb);
			print_sp_nl(&y);
		}
		print_parameters(st, i, &y);
		i++;
	}
	ft_printf("0a\n");//no idea why this is always at the end
}

//am I accounting for labels with instructions on the same line and next line?

static void	set_label_addresses(t_assembler *st)
{
	t_label_ref *tmp;
	int ref = 0;
	while (st->label)
	{
		tmp = st->label_ref;
		while (tmp)
		{
			if (ft_strequ(tmp->name, st->label->name))
			{
				ref = st->label->offset - tmp->instruct_offset;
				st->arr[tmp->instruct_num]->params[tmp->param_num] = tmp->dir ? ft_strjoin("%", ft_itoa(ref)) : ft_itoa(ref);		}
			tmp = tmp->next;
		}
		st->label = st->label->next;
	}
}

int			convert_to_hex(t_assembler *st)
{
	int		file_size;
	char	*line;

	while(get_next_line(st->sfile, &st->line))
	{
		if (ft_strstr(st->line, NAME_CMD_STRING))
			convert_name(st);
        else if (ft_strstr(st->line, COMMENT_CMD_STRING))
            convert_description(st);
		else
		{
			line = ft_strtrim(st->line);
			if (line[0] != '\0')
				parse_instructions(st);
		}
        st->i++;
	}
	set_label_addresses(st);
	return (1);
}

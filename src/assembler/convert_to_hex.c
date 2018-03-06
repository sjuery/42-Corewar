/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 19:55:29 by sjuery            #+#    #+#             */
/*   Updated: 2018/03/03 23:02:15 by sjuery           ###   ########.fr       */
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
	int i;
	int byte;

	i = size - 1;
	byte = res;
	while (i >= 0)
	{
		byte = res >> (i * 8);
		ft_dprintf(st->corefile, "%02hhx", byte);
		print_sp_nl(st, y);
		i--;
	}
}

void		print_header(t_assembler *st, int *y)
{
	int i = 0;
	int j = 0;

	ft_dprintf(st->corefile, "00ea 83f3 ");
	while (i < PROG_NAME_LENGTH)
	{
		ft_dprintf(st->corefile, "%02x", st->prog_name[i]);
		print_sp_nl(st, y);
		i++;
	}
	while (i < PROG_NAME_LENGTH + 8)//8 bytes for the size in bytes of commands
	{
		if(1 >= PROG_NAME_LENGTH + 8 - i)
		{
			if(ft_strlen(ft_itoa_base(st->final_offset, 16, 1)) < 2)
				ft_dprintf(st->corefile, "%02x", 0);
			ft_dprintf(st->corefile, "%04x", st->final_offset);
		}
		else if (1 < PROG_NAME_LENGTH + 7 - i)
			ft_dprintf(st->corefile, "%02x", 0);
		print_sp_nl(st, y);
		i++;
	}
	while (j < COMMENT_LENGTH)
	{
		ft_dprintf(st->corefile, "%02x", st->comment[j]);
		print_sp_nl(st, y);
		j++;
	}
	while (j < COMMENT_LENGTH + 4)//?????????
	{
		ft_dprintf(st->corefile, "%02x", 0);
		print_sp_nl(st, y);
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
			ft_dprintf(st->corefile, "%02x", res);
			print_sp_nl(st, y);
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

	i = 0;
	y = 5;
	print_header(st, &y);
	while (st->arr[i])
	{
		ft_dprintf(st->corefile, "%02x", st->arr[i]->op);
		print_sp_nl(st, &y);
		if (st->arr[i]->acb)
		{
			ft_dprintf(st->corefile, "%02x", st->arr[i]->acb);
			print_sp_nl(st, &y);
		}
		print_parameters(st, i, &y);
		i++;
	}
}

//am I accounting for labels with instructions on the same line and next line?

static void	set_label_addresses(t_assembler *st)
{
	t_label_ref *tmp;
	t_label *tmp_label;
	int ref = 0;
	tmp_label = st->label;
	while (tmp_label)
	{
		tmp = st->label_ref;
		while (tmp)
		{
			if (ft_strequ(tmp->name, tmp_label->name))
			{
				ref = tmp_label->offset - tmp->instruct_offset;
				st->arr[tmp->instruct_num]->params[tmp->param_num] = tmp->dir ? ft_strjoin("%", ft_itoa(ref)) : ft_itoa(ref);
			}
			tmp = tmp->next;
		}
		tmp_label = tmp_label->next;
	}
}

int			convert_to_hex(t_assembler *st)
{
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
	t_label_ref *tmp_ref;
	tmp_ref = st->label_ref;
	while (tmp_ref)
	{
		ft_printf("label_ref = %s; instruct_offset = %i\n", tmp_ref->name, tmp_ref->instruct_offset);
		tmp_ref = tmp_ref->next;
	}
	t_label *tmp;
	tmp = st->label;
	while (tmp)
	{
		ft_printf("label = %s; offset = %i\n", tmp->name, tmp->offset);
		tmp = tmp->next;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 19:55:29 by sjuery            #+#    #+#             */
/*   Updated: 2018/04/11 15:46:54 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	convert_name(t_assembler *st)
{
	int	name_len;
	int	i;

	i = 0;
	name_len = 1;
	while (st->line[st->i] != '"')
		st->i++;
	st->i++;
	while (st->line[st->i] != '"' && i < PROG_NAME_LENGTH)
	{
		st->prog_name[i] = (int)st->line[st->i];
		i++;
		st->i++;
		name_len++;
	}
}

static void	convert_description(t_assembler *st)
{
	int desc_len;
	int i;

	i = 0;
	desc_len = 1;
	st->i = 0;
	while (st->line[st->i] != '"')
		st->i++;
	st->i++;
	while (st->line[st->i] != '"' && i < COMMENT_LENGTH)
	{
		st->comment[i] = (int)st->line[st->i];
		i++;
		st->i++;
		desc_len++;
	}
}

static void	set_label_addresses(t_assembler *st, int ref, int flag)
{
	t_label_ref *tmp;
	t_label		*tmp_label;

	tmp = st->label_ref;
	while (tmp)
	{
		tmp_label = st->label;
		flag = 0;
		while (tmp_label)
		{
			if (ft_strequ(tmp->name, tmp_label->name))
			{
				ref = tmp_label->offset - tmp->instruct_offset;
				st->arr[tmp->instruct_num]->params[tmp->param_num] = tmp->dir ?
					ft_strjoinfree(ft_strdup("%"), ft_itoa(ref)) : ft_itoa(ref);
				flag = 1;
			}
			tmp_label = tmp_label->next;
		}
		if (!flag)
			handle_error("Error: Referencing non-existing label\n", st);
		tmp = tmp->next;
	}
}

int			convert_to_hex(t_assembler *st)
{
	char	*line;

	line = NULL;
	st->line = NULL;
	while (get_next_line(st->sfile, &st->line))
	{
		if (ft_strstr(st->line, NAME_CMD_STRING))
			convert_name(st);
		else if (ft_strstr(st->line, COMMENT_CMD_STRING))
			convert_description(st);
		else
		{
			line = ft_strtrim(st->line);
			if (line[0] != '\0')
				parse_instructions(st, line, 0, NULL);
			free(line);
		}
		free(st->line);
		st->i++;
	}
	set_label_addresses(st, 0, 0);
	return (1);
}

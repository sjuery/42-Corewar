/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 19:55:29 by sjuery            #+#    #+#             */
/*   Updated: 2018/04/09 14:32:21 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void convert_name(t_assembler *st)
{
    int name_len;
	int i = 0;

    name_len = 1;
	st->prog_name = ft_memalloc(sizeof(int) * PROG_NAME_LENGTH);
    while(st->line[st->i] != '"')
        st->i++;
    st->i++;
    while(st->line[st->i] != '"' && i < PROG_NAME_LENGTH)
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
    while(st->line[st->i] != '"' && i < COMMENT_LENGTH)
    {
		st->comment[i] = (int)st->line[st->i];
		i++;
		st->i++;
        desc_len++;
    }
}

//am I accounting for labels with instructions on the same line and next line?

static void	set_label_addresses(t_assembler *st)
{
	t_label_ref *tmp;
	t_label		*tmp_label;
	int			ref;
	char		*str;
	int			flag;

	ref = 0;
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
				str = ft_itoa(ref);
				st->arr[tmp->instruct_num]->params[tmp->param_num] = tmp->dir ? ft_strjoin("%", str) : ft_itoa(ref);
				free(str);
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
			free(line);
		}
		free(st->line);
        st->i++;
	}
	set_label_addresses(st);
	return (1);
}

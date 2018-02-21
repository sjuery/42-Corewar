/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 19:55:29 by sjuery            #+#    #+#             */
/*   Updated: 2018/02/20 17:55:23 by ihodge           ###   ########.fr       */
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
    //ft_printf_fd(st->corefile, "00ea 83f3 ");
    //ft_printf_fd(st->corefile, "00ea83f3");
    while(st->line[st->i] != '"')
    {
		st->prog_name[i] = (int)st->line[st->i];
        //ft_printf_fd(st->corefile, "%s", ft_itoa_base(st->line[st->i], 16, 1));

        /*if(name_len % 12 == 0)
            ft_printf_fd(st->corefile, "\n");
        else if(name_len % 2 == 0 && st->line[st->i+2])
            ft_printf_fd(st->corefile, " ");*/
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
        //ft_printf_fd(st->corefile, "%s", ft_itoa_base(st->line[st->i], 16, 1));
		st->comment[i] = (int)st->line[st->i];
       /* if(desc_len % 12 == 0)
            ft_printf_fd(st->corefile, "\n");
        else if(desc_len % 2 == 0 && st->line[st->i+2])
            ft_printf_fd(st->corefile, " ");*/
		i++;
		st->i++;
        desc_len++;
    }
}

void		write_shit(t_assembler *st)
{
	int i = 0;
	int j = 0;
	ft_printf("%08x", COREWAR_EXEC_MAGIC);	
	while (i < PROG_NAME_LENGTH + 8)
	{
		ft_printf("%02x", st->prog_name[i]);
		i++;
	}
	while (j < COMMENT_LENGTH)
	{
		ft_printf("%02x", st->comment[j]);
		j++;
	}
	int	res = 0;
	i = 0;
	j = 0;
	while (st->arr[i])
	{
		ft_printf("%02x", st->arr[i]->op);
		if (st->arr[i]->acb)
			ft_printf("%02x", st->arr[i]->acb);
		while (st->arr[i]->params[j])
		{
			if (check_param_type(st->arr[i]->params[j], st->arr[i]->op - 1, j) == DIR_CODE)
			{
				res = ft_atoi(st->arr[i]->params[j] + 1);
				if (g_optab[st->arr[i]->op - 1].index)
					ft_printf("%04hx", res);
				else
					ft_printf("%08x", res);
			}
			else if (check_param_type(st->arr[i]->params[j], st->arr[i]->op - 1, j) == REG_CODE)
			{
				res = ft_atoi(st->arr[i]->params[j] + 1);
				ft_printf("%02x", res);
			}
			else
				ft_printf("%04hx", ft_atoi(st->arr[i]->params[j]));
			j++;
		}
		j = 0;
		i++;
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
	/*while (st->label)
	{
		ft_printf("label name = %s, label offset = %i\n", st->label->name, st->label->offset);
		st->label = st->label->next;
	}
	while (st->label_ref)
	{
		ft_printf("label_ref name = %s, label_ref offset = %i, instruct_offset = %i\n", st->label_ref->name, st->label_ref->offset, st->label_ref->instruct_offset);
		st->label_ref = st->label_ref->next;
	}*/
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
				st->arr[tmp->instruct_num]->params[tmp->param_num] = ft_itoa(ref);
			}
			tmp = tmp->next;
		}
		st->label = st->label->next;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 19:55:29 by sjuery            #+#    #+#             */
/*   Updated: 2018/02/07 23:18:06 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void convert_name(t_assembler *st)
{
    int name_len;

    name_len = 1;
    while(st->line[st->i] != '"')
        st->i++;
    st->i++;
    ft_printf("00ea 83f3 ");
    while(st->line[st->i] != '"')
    {
        ft_printf("%s", ft_itoa_base(st->line[st->i], 16, 1));
        if(name_len % 12 == 0)
            ft_printf("\n");
        else if(name_len % 2 == 0 && st->line[st->i+2])
            ft_printf(" ");
		st->i++;
        name_len++;
    }
}

static void convert_description(t_assembler *st)
{
    int desc_len;

    desc_len = 1;
    st->i = 0;
    while(st->line[st->i] != '"')
        st->i++;
    st->i++;
    ft_printf("03ff ");
    while(st->line[st->i] != '"')
    {
        ft_printf("%s", ft_itoa_base(st->line[st->i], 16, 1));
        if(desc_len % 12 == 0)
            ft_printf("\n");
        else if(desc_len % 2 == 0 && st->line[st->i+2])
            ft_printf(" ");
		st->i++;
        desc_len++;
    }
}

int			convert_to_hex(t_assembler *st)
{
	int		file_size;

	while(get_next_line(st->sfile, &st->line))
	{
		if(ft_strstr(st->line, NAME_CMD_STRING))
			convert_name(st);
        else if(ft_strstr(st->line, COMMENT_CMD_STRING))
            convert_description(st);
		// while(st->line[st->i])
		// {
		// 	// if(ft_strlen(ft_itoa_base(st->line[st->i], 16, 1)) < 2)
		// 	// 	printf("0");
		// 	printf("%x", st->line[st->i]);
		// 	if(st->i % 8 == 0)
		// 		printf("\n");
		// 	else if(st->i % 2 == 0)
		// 		printf(" ");
		// 	st->i++;
		// }
        st->i++;
	}
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 15:39:13 by sjuery            #+#    #+#             */
/*   Updated: 2018/04/11 15:40:48 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void            handle_errors(char *error_message)
{
    ft_printf("%s\n", error_message);
    exit (0);
}

static char		*check_file(char *filename, char *file_type, char *new_type)
{
	char	*output;

	if (ft_strcmp(ft_strrchr(filename, '.'), file_type))
		return (NULL);
	output = ft_memalloc(ft_strlen(filename) 	- ft_strlen(file_type)
	 											+ ft_strlen(new_type) + 1);
	ft_strncpy(output, filename, ft_strlen(filename) - ft_strlen(file_type));
	ft_strncpy(output + ft_strlen(output), new_type, ft_strlen(new_type));
	return (output);
}

int				main(int argc, char **argv)
{
	char	*output;

	output = NULL;

	if (argc == 2)
	{
		if (!(output = check_file(argv[1], ".cor", ".s")))
			handle_errors("Couldn't read given file");
		disassembler(argv[1], output);
	}
	handle_errors("usage: ./dasm \"file.cor\"");
	return (1);
}

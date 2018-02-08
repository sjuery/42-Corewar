/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 15:07:48 by sjuery            #+#    #+#             */
/*   Updated: 2018/02/07 19:56:00 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void			handle_error(char *error_type, t_assembler *st)
{
	ft_printf("%s", error_type);
	close(st->corefile);
	close(st->sfile);
	exit(0);
}

static int			validate_file(t_assembler *st)
{
	return (1);
}

int					main(int argc, char **argv)
{
	t_assembler *st;

	st = ft_memalloc(sizeof(t_assembler));
	if (argc == 2 || argc == 3)
	{
		if (!(st->sfile = open(argv[argc - 1], O_RDONLY)))
			handle_error("Error: Couldn't read given file", st);
		if (!validate_file(st))
			handle_error("Error: File is invalid", st);
		if (!(st->corefile = open(ft_strjoin(argv[argc - 1], ".cor"), O_CREAT)))
			handle_error("Error: Cor file couldn't be created", st);
		if (!convert_to_hex(st))
			handle_error("Error: Couldn't finish writting to Cor file", st);
		close(st->corefile);
		close(st->sfile);
	}
	else
		handle_error("Usage: ./st [-a] <sourcefile.s>\n\t"
		"-a : Instead of creating a .cor file, outputs a stripped"
		" and annotated version of the code to the standard output", st);
	return (1);
}

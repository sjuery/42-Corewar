/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassembler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 15:07:48 by sjuery            #+#    #+#             */
/*   Updated: 2018/03/05 13:18:58 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

void				handle_error(char *error_type, t_disassembler *st)
{
	ft_printf("%s", error_type);
	close(st->corefile);
	close(st->sfile);
	exit(0);
}

int					main(int argc, char **argv)
{
	t_disassembler *st;

	st = ft_memalloc(sizeof(t_disassembler));
	st->arr = ft_memalloc(sizeof(t_instruction*) * CHAMP_MAX_SIZE);
	if (argc == 2 || argc == 3)
	{
		if ((st->sfile = open(argv[argc - 1], O_RDONLY)) < 0 ||
			argv[argc - 1][ft_strlen(argv[argc - 1]) - 4] != '.' ||
			argv[argc - 1][ft_strlen(argv[argc - 1]) - 3] != 'c' ||
			argv[argc - 1][ft_strlen(argv[argc - 1]) - 2] != 'o' ||
			argv[argc - 1][ft_strlen(argv[argc - 1]) - 1] != 'r')
			handle_error("Error: Couldn't read given file", st);
		if (!convert_to_hex(st))
			handle_error("Error: Couldn't finish writting to Cor file", st);
		if ((st->corefile = open(ft_strjoin(ft_strsub(argv[argc - 1], 0,
				ft_strlen(argv[argc - 1]) - 1), "test"),
						O_CREAT | O_WRONLY, S_IRWXU)) < 0)
			handle_error("Error: Cor file couldn't be created", st);
		print_shit(st);
		close(st->corefile);
		close(st->sfile);
	}
	else
		handle_error("Usage: ./st [-a] <sourcefile.s>\n\t"
		"-a : Instead of creating a .cor file, outputs a stripped"
		" and annotated version of the code to the standard output", st);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 15:07:48 by sjuery            #+#    #+#             */
/*   Updated: 2018/04/09 11:24:13 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	handle_error(char *error_type, t_assembler *st)
{
	ft_printf("%s", error_type);
	close(st->corefile);
	close(st->sfile);
	exit(0);
}

void	free_shit(t_assembler *st)
{
	t_label		*tmp;
	t_label_ref *tmp_ref;
	int			i;

	i = 0;
	while (st->label)
	{
		tmp = st->label->next;
		free(st->label->name);
		free(st->label);
		st->label = tmp;
	}
	while (st->label_ref)
	{
		tmp_ref = st->label_ref->next;
		free(st->label_ref->name);
		free(st->label_ref);
		st->label_ref = tmp_ref;
	}
	while (i < st->instruct_num)
	{
		st->arr[i]->params[0] ? free(st->arr[i]->params[0]) : 0;
		st->arr[i]->params[1] ? free(st->arr[i]->params[1]) : 0;
		st->arr[i]->params[2] ? free(st->arr[i]->params[2]) : 0;
		st->arr[i]->params[3] ? free(st->arr[i]->params[3]) : 0;
		free(st->arr[i]->params);
		free(st->arr[i]);
		i++;
	}
	free(st->arr);
	free(st->prog_name);
	free(st->comment);
}

int		main(int argc, char **argv)
{
	t_assembler *st;
	char		*file_name;
	char		*cor_file;

	file_name = NULL;
	cor_file = NULL;
	st = ft_memalloc(sizeof(t_assembler));
	st->arr = ft_memalloc(sizeof(t_instruction*) * CHAMP_MAX_SIZE);
	if (argc == 2 || argc == 3)
	{
		if ((st->sfile = open(argv[argc - 1], O_RDONLY)) < 0 ||
			argv[argc - 1][ft_strlen(argv[argc - 1]) - 2] != '.' ||
			argv[argc - 1][ft_strlen(argv[argc - 1]) - 1] != 's')
			handle_error("Error: Couldn't read given file", st);
		if (!convert_to_hex(st))
			handle_error("Error: Couldn't finish writting to Cor file", st);
		file_name = ft_strsub(argv[argc - 1], 0, ft_strlen(argv[argc - 1]) - 1);
		cor_file = ft_strjoin(file_name, "cor");
		if ((st->corefile = open(cor_file, O_CREAT | O_WRONLY, S_IRWXU)) < 0)
			handle_error("Error: Cor file couldn't be created", st);
		print_shit(st);
		close(st->corefile);
		close(st->sfile);
	}
	else
		handle_error("Usage: ./st [-a] <sourcefile.s>\n\t"
		"-a : Instead of creating a .cor file, outputs a stripped"
		" and annotated version of the code to the standard output", st);
	ft_printf("Writing to .cor file\n");
	free(file_name);
	free(cor_file);
	free_shit(st);
	free(st);
	return (1);
}

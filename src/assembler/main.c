/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 15:07:48 by sjuery            #+#    #+#             */
/*   Updated: 2018/04/11 15:52:33 by ihodge           ###   ########.fr       */
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

void	free_instruct(t_assembler *st)
{
	int	i;

	i = 0;
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
}

void	free_shit(t_assembler *st)
{
	t_label		*tmp;
	t_label_ref *tmp_ref;

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
	free_instruct(st);
	free(st->arr);
	free(st->prog_name);
	free(st->comment);
	free(st);
}

void	create_file(t_assembler *st, int argc, char **argv)
{
	char		*file_name;
	char		*cor_file;

	file_name = ft_strsub(argv[argc - 1], 0, ft_strlen(argv[argc - 1]) - 1);
	cor_file = ft_strjoin(file_name, "cor");
	if ((st->corefile = open(cor_file, O_CREAT | O_WRONLY, S_IRWXU)) < 0)
		handle_error("Error: Cor file couldn't be created", st);
	free(file_name);
	free(cor_file);
}

int		main(int argc, char **argv)
{
	t_assembler *st;

	st = (t_assembler *)ft_memalloc(sizeof(t_assembler));
	st->arr = (t_instruction **)ft_memalloc(sizeof(t_instruction*) * 
			(CHAMP_MAX_SIZE * 2));
	st->prog_name = (int*)ft_memalloc(sizeof(int) * PROG_NAME_LENGTH);
	st->comment = (int*)ft_memalloc(sizeof(int) * COMMENT_LENGTH);
	if (argc == 2 || argc == 3)
	{
		if ((st->sfile = open(argv[argc - 1], O_RDONLY)) < 0 ||
			argv[argc - 1][ft_strlen(argv[argc - 1]) - 2] != '.' ||
			argv[argc - 1][ft_strlen(argv[argc - 1]) - 1] != 's')
			handle_error("Error: Couldn't read given file", st);
		if (!convert_to_hex(st))
			handle_error("Error: Couldn't finish writting to Cor file", st);
		create_file(st, argc, argv);
		print_shit(st);
		close(st->corefile);
		close(st->sfile);
	}
	else
		handle_error("Usage: ./asm <sourcefile.s>\n\t", st);
	ft_printf("Writing to .cor file\n");
	free_shit(st);
	return (1);
}

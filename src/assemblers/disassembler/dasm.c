/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 19:19:56 by sjuery            #+#    #+#             */
/*   Updated: 2018/04/11 15:53:22 by mlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		translater(int x)
{
	int	translation;

	translation = (x >> 24) & 0xFF;
	translation += (x >> 8) & 0xFF00;
	translation += (x << 8) & 0xFF0000;
	translation += x << 24;
	return (translation);
}

static void		disassemble(char *data, int size, int fd)
{
	int				i;
	unsigned long	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < sizeof(g_optab) / sizeof(t_op))
		{
			if (data[i] == g_optab[j].opcode)
			{
				i += print_instructions(&data[i], g_optab[j], fd);
				break ;
			}
			j++;
		}
		if (j >= (sizeof(g_optab) / sizeof(t_op)) - 1)
			handle_errors("Unknown instruction");
	}
}

static int		get_size(char *filename)
{
	int		fd;
	int		file_size;
	int		amount_read;
	char	buff;

	if ((fd = open(filename, O_RDONLY)))
	{
		file_size = 0;
		while ((amount_read = read(fd, &buff, 1)) == 1)
			file_size++;
		close(fd);
		if (amount_read == 0)
			return (file_size);
	}
	handle_errors("Couldn't read the whole file");
	return (0);
}

void			*read_file(char *filename, int *size)
{
	int				amount_read;
	int				fd;
	unsigned char	*buff;

	if (!filename)
		handle_errors("Couldn't find filename");
	else if ((*size = get_size(filename)) == -1)
		handle_errors("Couldn't find filesize");
	else if (!(buff = ft_memalloc(*size + 1)))
		handle_errors("Couldn't allocate memory");
	else if ((fd = open(filename, O_RDONLY)))
	{
		amount_read = read(fd, buff, *size);
		close(fd);
		if (amount_read == *size)
			return (buff);
	}
	handle_errors("Couldn't read the whole file");
	return (0);
}

void			disassembler(char *input_name, char *output_name)
{
	int			size;
	int			fd;
	char		*data;
	t_header	*header;

	data = read_file(input_name, &size);
	header = (t_header *)data;
	if (translater(header->magic) != COREWAR_EXEC_MAGIC)
		handle_errors("Invalid magic number");
	if ((fd = open(output_name, O_WRONLY | O_CREAT, 0644)) == -1)
		handle_errors("Couldn't create .s file");
	ft_dprintf(fd, "%s \"%s\"\n", NAME_CMD_STRING, header->prog_name);
	ft_dprintf(fd, "%s \"%s\"\n\n", COMMENT_CMD_STRING, header->comment);
	disassemble(&data[sizeof(t_header)], translater(header->prog_size), fd);
	ft_printf("Created .s file at %s\n", output_name);
	free(data);
}

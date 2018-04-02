/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 16:52:00 by anazar            #+#    #+#             */
/*   Updated: 2018/04/01 20:51:49 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	convert_header(t_header *head, char *header, int i, int x)
{
	head->magic = (header[3] & 0x000000FF) << 0 |
						(header[2] & 0x000000FF) << 8 |
						(header[1] & 0x000000FF) << 16 |
						(header[0] & 0x000000FF) << 24;
	ft_bzero(head->prog_name, PROG_NAME_LENGTH + 1);
	while (header[++i] != 0)
		head->prog_name[++x] = header[i];
	while (!ft_isprint(header[i]))
		i++;
	x = -1;
	ft_bzero(head->comment, COMMENT_LENGTH + 1);
	i--;
	while (ft_isprint(header[++i]))
		head->comment[++x] = header[i];
}

int		read_input(int fd, t_header *head, char *body)
{
	char		*header;

	header = ft_memalloc(sizeof(char) * HEADER_SIZE);
	if (read(fd, header, 2192) <= 0)
		return (0);
	convert_header(head, header, 3, -1);
	if ((head->prog_size = read(fd, body, CHAMP_MAX_SIZE)) <= 0)
		return (0);
	body[head->prog_size] = 0;
	free(header);
	return (1);
}

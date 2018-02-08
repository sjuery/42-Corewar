/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 16:52:00 by anazar            #+#    #+#             */
/*   Updated: 2018/02/07 19:04:09 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	convert_header(t_io *info)
{
	int i = 3;
	int x = -1;
	info->head.magic =	(info->header[3] & 0x000000FF) << 0 |
						(info->header[2] & 0x000000FF) << 8 |
						(info->header[1] & 0x000000FF) << 16 |
						(info->header[0] & 0x000000FF) << 24;
	ft_bzero(info->head.prog_name, PROG_NAME_LENGTH + 1);
	while (info->header[++i] != 0)
		info->head.prog_name[++x] = info->header[i];
	info->head.prog_name[++x] = 0;
	while (!ft_isascii(info->header[++i]));
	x = -1;
	ft_bzero(info->head.comment, COMMENT_LENGTH + 1);
	while (ft_isascii(info->header[++i]))
		info->head.comment[++x] = info->header[i];
	info->head.comment[++x] = 0;
	ft_printf("MAGIC [%x], NAME [%s], COMMENT [%s]\n", info->head.magic, info->head.prog_name, info->head.comment);
}

int	read_input(int fd, t_io *info)
{
	if (read(fd, info->header, 2192) <= 0)
		return (0);
	convert_header(info);
	if ((info->bytes = read(fd, info->body, CHAMP_MAX_SIZE)) <= 0)
		return (0);
	info->body[info->bytes] = 0;
	return (1);
}

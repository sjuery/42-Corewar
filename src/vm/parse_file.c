/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 16:52:00 by anazar            #+#    #+#             */
/*   Updated: 2018/03/05 18:56:58 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	convert_header(t_io *info, int i, int x)
{
	info->head.magic = (info->header[3] & 0x000000FF) << 0 |
						(info->header[2] & 0x000000FF) << 8 |
						(info->header[1] & 0x000000FF) << 16 |
						(info->header[0] & 0x000000FF) << 24;
	ft_bzero(info->head.prog_name, PROG_NAME_LENGTH + 1);
	while (info->header[++i] != 0)
		info->head.prog_name[++x] = info->header[i];
	while (!ft_isprint(info->header[i]))
		i++;
	x = -1;
	ft_bzero(info->head.comment, COMMENT_LENGTH + 1);
	i--;
	while (ft_isprint(info->header[++i]))
		info->head.comment[++x] = info->header[i];
}

int		read_input(int fd, t_io *info)
{
	if (read(fd, info->header, 2192) <= 0)
		return (0);
	convert_header(info, 3, -1);
	if ((info->head.prog_size = read(fd, info->body, CHAMP_MAX_SIZE)) <= 0)
		return (0);
	info->body[info->head.prog_size] = 0;
	//info->alive = 1;//info->executing = 1 instead of assuming program will call live
	info->executing = 1;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 16:52:00 by anazar            #+#    #+#             */
/*   Updated: 2018/02/07 16:53:19 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	read_input(int fd, t_io *info)
{
	// char	header[2192];
	// char	body[CHAMP_MAX_SIZE + 1];
	// int		bytes_read;

	if (read(fd, info->header, 2192) <= 0)
		exit(0);
	// info->header = header;
	if ((info->bytes = read(fd, info->body, CHAMP_MAX_SIZE)) <= 0)
		exit(0);
	// info->body = body;
	info->body[info->bytes] = 0;
}

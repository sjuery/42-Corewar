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

int	read_input(int fd, t_io *info)
{
	if (read(fd, info->header, 2192) <= 0)
		return (0);
	if ((info->bytes = read(fd, info->body, CHAMP_MAX_SIZE)) <= 0)
		return (0);
	info->body[info->bytes] = 0;
	return (1);
}

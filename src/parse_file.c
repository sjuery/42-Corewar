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

char    *get_header(char *str)
{
	char	header[2192];
	char	body[CHAMP_MAX_SIZE + 1];
	int		bytes_read;
    char    *out;

	fd = open(str, O_RDONLY);
	if (read(fd, header, 2192) <= 0)
		exit(0);
	if ((bytes_read = read(fd, body, CHAMP_MAX_SIZE)) <= 0)
		exit(0);
	body[bytes_read] = 0;
	out = body;
	return (out);
}

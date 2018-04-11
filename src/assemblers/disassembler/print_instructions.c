/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 20:13:32 by sjuery            #+#    #+#             */
/*   Updated: 2018/04/11 15:09:42 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		int_trans(char *array)
{
	int	translation;

	translation = (unsigned char)array[3];
	translation += (unsigned char)array[2] * 256;
	translation += (unsigned char)array[1] * 256 * 256;
	translation += (unsigned char)array[0] * 256 * 256 * 256;
	return (translation);
}

static short	short_trans(char *array)
{
	short	translation;

	translation = (unsigned char)array[1];
	translation += (unsigned char)array[0] * 256;
	return (translation);
}

static int				acb_loop(char *data, t_op op, int fd)
{
	int	i;
	int	j;

	i = 0;
	j = 2;
	while (i < op.params)
	{
		if (((data[1] >> (6 - (i * 2))) & 3) == REG_CODE)
		{
			ft_dprintf(fd, "r%d", data[j]);
			j += 1;
		}
		else if (((data[1] >> (6 - (i * 2))) & 3) == IND_CODE)
		{
			ft_dprintf(fd, "%d", short_trans(&data[j]));
			j += 2;
		}
		else if (((data[1] >> (6 - (i * 2))) & 3) == DIR_CODE)
		{
			if (op.index == 1)
			{
				ft_dprintf(fd, "%c%d", DIRECT_CHAR, short_trans(&data[j]));
				j += 2;
			}
			else
			{
				ft_dprintf(fd, "%c%d", DIRECT_CHAR, int_trans(&data[j]));
				j += 4;
			}
		}
		if (++i < op.params)
			ft_dprintf(fd, ", ");
		else
			ft_dprintf(fd, "\n");
	}
	return (j);
}

int	print_instructions(char *data, t_op op, int fd)
{
	ft_dprintf(fd, "%s\t", op.opstr);
	if (op.acb)
		return (acb_loop(data, op, fd));
	if (op.index)
	{
		ft_dprintf(fd, "%c%d\n", DIRECT_CHAR, short_trans(&data[1]));
		return (3);
	}
	else
	{
		ft_dprintf(fd, "%c%d\n", DIRECT_CHAR, int_trans(&data[1]));
		return (5);
	}
}

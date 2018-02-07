/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 15:07:48 by sjuery            #+#    #+#             */
/*   Updated: 2018/02/07 15:07:50 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

//Be careful of "deadbeef" it might be compiled backwards

int					main(int argc, char **argv)
{
	int			corefile;

	if (argc == 2 || argc == 3)
	{
        if ((corefile = open(ft_strjoin(argv[argc - 1], ".cor"), O_CREAT)) == -1)
            ft_printf("Error opening file");
		close(corefile);
	}
	else
		ft_printf("Usage: ./asm [-a] <sourcefile.s>\n\t-a : Instead of creating a .cor file, outputs a stripped and annotated version of the code to the standard output");
	return (0);
}
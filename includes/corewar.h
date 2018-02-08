/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 09:00:00 by mlu               #+#    #+#             */
/*   Updated: 2018/02/07 16:56:38 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/stat.h>
# include <math.h>
# include <stdarg.h>
# include <stdint.h>
# include <inttypes.h>
# include <ncurses.h>
# include <curses.h>

# include "libft.h"
# include "op.h"
# define  HEADER_SIZE 2192

typedef struct  s_io
{
    char    header[HEADER_SIZE];
    char    body[CHAMP_MAX_SIZE + 1];
    int		bytes;
}               t_io;

typedef struct  s_vm
{
	char    regs[REG_NUMBER][REG_SIZE];
	char    pc[REG_SIZE];
	int		flag;
    t_io    info;
}               t_vm;

/*
** parse_file.c
*/
int		read_input(int fd, t_io *info);

#endif

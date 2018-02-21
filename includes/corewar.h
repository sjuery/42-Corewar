/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 09:00:00 by mlu               #+#    #+#             */
/*   Updated: 2018/02/08 19:31:57 by anazar           ###   ########.fr       */
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

typedef struct		s_io
{
	t_header		head;
	char			header[HEADER_SIZE];
	char			body[CHAMP_MAX_SIZE + 1];
}					t_io;

typedef struct		s_vm
{
	char			regs[REG_NUMBER][REG_SIZE];
	char			pc[REG_SIZE];
	int				flag;
	t_io			info[4];
	char			*players[4];
 	int				num_players;
	unsigned char	core[4096];
	size_t			dump_cycle;
}					t_vm;

/*
** parse_file.c
*/
int					read_input(int fd, t_io *info);

/*
** ncurses.c
*/
void				init_curses(t_vm *vm);

/*
** vm arguments
*/
void	vm_live(void);
void	vm_zjmp(void);
void	vm_sti(void);
void	vm_lfork(void);
void	vm_fork(void);
void	vm_lld(void);
void	vm_lldi(void);
void	vm_ldi(void);
void	vm_ld(void);
void	vm_st(void);
void	vm_and(void);
void	vm_xor(void);
void	vm_aff(void);
void	vm_add(void);
void	vm_sub(void);


#endif

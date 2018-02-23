/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 09:00:00 by mlu               #+#    #+#             */
/*   Updated: 2018/02/21 16:00:12 by anazar           ###   ########.fr       */
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

/*
** typedef struct					s_header
** {
** 		unsigned int				magic; <-- the ex identifier
** 		char						prog_name[PROG_NAME_LENGTH + 1]; <-- process name
** 		unsigned int				prog_size; <-- bytes to be read
** 		char						comment[COMMENT_LENGTH + 1]; <-- process comment
** }	
*/

typedef struct		s_io
{
	t_header		head; // header in comment from op.h to see what it contains
	char			header[HEADER_SIZE]; // store stuff being read
	char			body[CHAMP_MAX_SIZE + 1];
	int				index; // to track where the instruction reading is currently at
	int				alive; // this is to check if the process is alive or not
}					t_io;

typedef struct		s_vm
{
	char			regs[REG_NUMBER][REG_SIZE];
	char			pc[REG_SIZE];
	int				flag;
	t_io			info[1024]; // holds all the process
	int				process_count; // helps us keep track of total # of process
	char			*players[4]; // player names
 	int				num_players; // number of player
	unsigned char	core[4096]; // the vm board
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
void	vm_or(void);
void	vm_xor(void);
void	vm_aff(void);
void	vm_add(void);
void	vm_sub(void);

void jumptable(int a, t_vm *vm);

/*
** read_bytes.c
*/

void	read_bytes(t_vm *vm, int i);
#endif

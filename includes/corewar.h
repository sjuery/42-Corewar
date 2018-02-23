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
	int				live; // # of time it calls live
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
void	vm_live(t_vm *vm, int i);
void	vm_zjmp(t_vm *vm, int i);
void	vm_sti(t_vm *vm, int i);
void	vm_lfork(t_vm *vm, int i);
void	vm_fork(t_vm *vm, int i);
void	vm_lld(t_vm *vm, int i);
void	vm_lldi(t_vm *vm, int i);
void	vm_ldi(t_vm *vm, int i);
void	vm_ld(t_vm *vm, int i);
void	vm_st(t_vm *vm, int i);
void	vm_and(t_vm *vm, int i);
void	vm_or(t_vm *vm, int i);
void	vm_xor(t_vm *vm, int i);
void	vm_aff(t_vm *vm, int i);
void	vm_add(t_vm *vm, int i);
void	vm_sub(t_vm *vm, int i);

void jumptable(int a, t_vm *vm, int i);

/*
** read_bytes.c
*/

void	read_bytes(t_vm *vm, int i);
#endif

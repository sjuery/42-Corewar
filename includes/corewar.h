/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 09:00:00 by mlu               #+#    #+#             */
/*   Updated: 2018/03/06 18:15:33 by anazar           ###   ########.fr       */
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

# define ACB1(a) ((a >> 6) % 4)
# define ACB2(a) ((a >> 4) % 4)
# define ACB3(a) ((a >> 2) % 4)
# define ACB			vm->info[i].start + vm->info[i].index - 1

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
	int				alive; // this is to check if the process has called live every CYCLE_TO_DIE cycles
	int				executing;//will be false if process hasn't called live in CYCLE_TO_DIE cycles/ game ends when all processes no longer executing
	int				live; // # of time it calls live
	unsigned char	regs[REG_NUMBER][REG_SIZE]; // registers, # of reg + its size
	unsigned char	pc[REG_SIZE]; // program counter
	int				carry; // carry flag
	int				location; // load location
	int				start; // start location on the core
	int				cycles;//each process has to keep track of how many cycles it's been executing
	int				wait_cycle;//each instruction has different amount of cycles it has to wait before executing
}					t_io;

typedef struct		s_vm
{
	t_io			info[1024]; // holds all the process
	int				process_count; // helps us keep track of total # of process
	char			*players[4]; // player names
 	int				num_players; // number of player
	unsigned char	core[4096]; // the vm board
	int				cycles;//might change this to every process having keeping track of their own cycles

	size_t			dump_cycle;
}					t_vm;

void				print_core(unsigned char *test, int i);

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

void get_offset(t_vm *vm, int i, unsigned char acb, unsigned char **l); // maybe concatenate acb pair and whether or not it' uses idx mod
int		get_index_one(unsigned char *l);
int		get_index_two(unsigned char *l1, unsigned char *l2);

void jumptable(int a, t_vm *vm, int i);
int		valid_acb(unsigned char acb, int b1, int b2, int b3);

/*
** read_bytes.c
*/

int		*read_acb(unsigned char a);
void	read_bytes(t_vm *vm, int i);

/*
** reg_ops.c
*/

void 	into_reg(unsigned int val, unsigned char *reg);
int		reg_add(unsigned char *reg1, unsigned char *reg2, unsigned char *reg3);
int		reg_sub(unsigned char *reg1, unsigned char *reg2, unsigned char *reg3);
int		reg_xor(unsigned char *reg1, unsigned char *reg2, unsigned char *reg3);
int		reg_or(unsigned char *reg1, unsigned char *reg2, unsigned char *reg3);
int		reg_and(unsigned char *reg1, unsigned char *reg2, unsigned char *reg3);

#endif

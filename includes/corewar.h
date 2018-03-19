/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 09:00:00 by mlu               #+#    #+#             */
/*   Updated: 2018/03/19 10:39:47 by ihodge           ###   ########.fr       */
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
# define VAL(a) (a[3] + (a[2] << 8) + (a[1] << 16) + (a[0] << 24))
# define VAL2(a) ((a[1]) + (a[0] << 8))

typedef	struct		s_vis
{
	unsigned char	byte;//character to be printed
	int				player;//owner of the byte that is being printed
	int				previous_index;//unhighlight this and change the color back to the owners color
}					t_vis;

typedef struct		s_io
{
	t_header		head; // header in comment from op.h to see what it contains
	char			header[HEADER_SIZE]; // store stuff being read
	char			body[CHAMP_MAX_SIZE + 1];
	unsigned char	player_num[4];//FF FF, FF FE, etc
	int				player_int;//player 1, 2, 3 or 4
	int				index; // to track where the instruction reading is currently at
	int				alive; // this is to check if the process has called live
	int				executing;//will be false if process hasn't called live in CYCLE_TO_DIE cycles/ game ends when all processes no longer executing
	int				live; // # of time it calls live
	unsigned char	regs[REG_NUMBER + 1][REG_SIZE]; // registers, # of reg + its size
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
 	int				num_players; // number of players
	unsigned char	core[4096]; // the vm board
	t_vis			vis[4096]; // visualiser board
	int				win_player;//keep track of currently winning player (1, 2, 3, or 4)
	int				cycle_to_die;//initalized to CYCLE_TO_DIE
	int				counter;
	size_t			dump_cycle;
	int				checks;//checks to see if cycle_to_die has been decreased
	int				cycles;
}					t_vm;

typedef struct		s_instr
{
	t_vm			*vm;
	int				i;
	unsigned char	acb;
	unsigned char	*l1;
	unsigned char	*l2;
	unsigned char	*l3;
	unsigned char	*s;
	unsigned int	reg_index[3];
	unsigned int	ri;
	int				opcode_pos;
	short			index;
}					t_instr;

t_instr				init_instr(t_vm *vm, int i);

void				print_core(unsigned char *test, int i);

/*
** parse_file.c
*/
int					read_input(int fd, t_io *info);

/*
** ncurses.c
*/
void				print_curses(t_vm *vm);
void				init_curses(void);

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

int		indirect(t_vm *vm, int i, unsigned char opcode);
//int		indirect(t_vm *vm, int i, unsigned char opcode, int pos);
//void get_offset(t_vm *vm, int i, unsigned char acb, unsigned char **l); // maybe concatenate acb pair and whether or not it' uses idx mod
//void get_offset(t_instr *instr, unsigned char acb, unsigned char **l);
int get_offset(t_instr *instr, unsigned char acb, unsigned char **l);
int get_offset_index(t_instr *instr, unsigned char acb, unsigned char **l);
//void get_offset_index(t_instr instr, unsigned char acb, unsigned char **l);
//void get_offset_index(t_vm *vm, int i, unsigned char acb, unsigned char **l);
int		get_index_one(unsigned char *l);
int		get_index_two(unsigned char *l1, unsigned char *l2);

void jumptable(int a, t_vm *vm, int i);
//int		valid_acb(unsigned char acb, int b1, int b2, int b3);
int		valid_acb(t_instr instr, int b1, int b2, int b3);
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
void reg_copy(unsigned char *dest, unsigned char *src);

#endif

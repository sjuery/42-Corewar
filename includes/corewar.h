/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 09:00:00 by mlu               #+#    #+#             */
/*   Updated: 2018/03/21 21:45:46 by ihodge           ###   ########.fr       */
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

# define PARAM1 	vm->info[i].start + vm->info[i].index
# define PARAM2		vm->info[i].start + vm->info[i].index + 1
# define PARAM3		vm->info[i].start + vm->info[i].index + 2
# define VWRAP 		192

typedef	struct		s_vis
{
	unsigned char	byte;//character to be printed
	int				player;//owner of the byte that is being printed
	int				previous_index;//unhighlight this and change the color back to the owners color
}					t_vis;

typedef struct		s_io
{
	t_header		head; // header in comment from op.h to see what it contains
	// char			header[HEADER_SIZE]; // store stuff being read
	// char			body[CHAMP_MAX_SIZE + 1];
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

typedef struct		s_flags
{
	int				d; // -dump
	int				n; // -n (player count)
	int				g; // -g (visualizer)
	int				b; // -b (debug)
	int				v; // -v (verbose)
	int				flags; // this is default set to 1, when it parses actual champ it sets to 0
}					t_flags;

typedef struct		s_vm
{
	t_io			info[3600]; // holds all the process
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
	int				live;//keeps tracks of number of times live was called for NBR_lIVE
	t_flags			f; // flags
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
int					read_input(int fd, t_io *info, char *body);

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

/*
** flags.c
*/
void	zero_flags(t_vm *vm);
void	get_champ_position(t_vm *vm, char *str, int pos);
void	fill_champ_position(t_vm *vm, char *str);
void	check_flags(t_vm *vm, char **av, int *i);
void	fill_champs(t_vm *vm, char **av, int *i);

/*
** init.c
*/
void 	init_vm(t_vm *vm);
void 	init_players(int ac, char **av, t_vm *vm);
void	write_info(t_vm *vm, int fd, int *x, int i);
void	jumptable(int a, t_vm *vm, int i);

/*
** util.c
*/
int		blank_pos(char **av);
void	assign_player_num(t_vm *vm, int i, unsigned char **reg);
void	print_core(unsigned char *core, int i);
int		valid_acb(t_instr instr, int b1, int b2, int b3);
void	error(void);

#endif

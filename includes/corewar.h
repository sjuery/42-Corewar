/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 09:00:00 by mlu               #+#    #+#             */
/*   Updated: 2018/03/23 11:41:38 by ihodge           ###   ########.fr       */
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

# define HEADER_SIZE	2192

# define ACB1(a)		((a >> 6) % 4)
# define ACB2(a)		((a >> 4) % 4)
# define ACB3(a)		((a >> 2) % 4)
# define ACB			vm->info[i].start + vm->info[i].index - 1
# define VAL(a)			(a[3] + (a[2] << 8) + (a[1] << 16) + (a[0] << 24))
# define VAL2(a)		((a[1]) + (a[0] << 8))

# define PARAM1			vm->info[i].start + vm->info[i].index
# define PARAM2			vm->info[i].start + vm->info[i].index + 1
# define PARAM3			vm->info[i].start + vm->info[i].index + 2

# define OFF1			instr->vm->info[instr->i].start
//# define OFF2			instr->vm->info[instr->i].index
# define OFF2			instr->core_index

# define OPC			instr->opcode_pos
# define REGI			instr->reg_index[instr->ri]

# define VWRAP			192

typedef	struct			s_vis
{
	unsigned char		byte;
	int					player;
	int					previous_index;
}						t_vis;

typedef struct			s_io
{
	t_header			head;
	unsigned char		player_num[4];
	int					player_int;
	int					index;
	int					alive;
	int					executing;
	int					live;
	unsigned char		regs[REG_NUMBER + 1][REG_SIZE];
	unsigned char		pc[REG_SIZE];
	int					carry;
	int					location;
	int					start;
	int					cycles;
	int					wait_cycle;
}						t_io;

typedef struct			s_flags
{
	int					d;
	int					n;
	int					g;
	int					b;
	int					v;
	int					flags;
}						t_flags;

typedef struct			s_vm
{
	t_io				info[3600];
	int					process_count;
	char				*players[4];
	int					num_players;
	unsigned char		core[4096];
	t_vis				vis[4096];
	int					win_player;
	int					cycle_to_die;
	int					counter;
	size_t				dump_cycle;
	int					checks;
	int					cycles;
	int					live;
	t_flags				f;
}						t_vm;

typedef struct			s_instr
{
	t_vm				*vm;
	int					i;
	unsigned char		acb;
	unsigned char		*l1;
	unsigned char		*l2;
	unsigned char		*l3;
	unsigned char		*s;
	unsigned int		reg_index[3];
	unsigned int		ri;
	int					opcode_pos;
	short				index;
	int					core_index;
}						t_instr;

t_instr					init_instr(t_vm *vm, int i);

void					print_core(unsigned char *test, int i);

int						valid_acb1(t_instr instr, int op);
int						valid_acb2(t_instr instr, int op);
int						valid_acb3(t_instr instr, int op);

/*
** parse_file.c
*/
int						read_input(int fd, t_io *info, char *body);

/*
** ncurses.c
*/
void					print_curses(t_vm *vm, int i, int x, int y);
void					init_curses(void);

/*
** read_bytes.c
*/

int						*read_acb(unsigned char a);
void					read_bytes(t_vm *vm, int i, int game_end, int counter);

/*
** reg_ops.c
*/
int						reg_add(unsigned char *reg1,
							unsigned char *reg2, unsigned char *reg3);
int						reg_sub(unsigned char *reg1,
							unsigned char *reg2, unsigned char *reg3);
int						reg_xor(unsigned char *reg1,
							unsigned char *reg2, unsigned char *reg3);
int						reg_or(unsigned char *reg1,
							unsigned char *reg2, unsigned char *reg3);
int						reg_and(unsigned char *reg1,
							unsigned char *reg2, unsigned char *reg3);

/*
** reg_util.c
*/
void					into_reg(unsigned int val, unsigned char *reg);
t_instr					init_instr(t_vm *vm, int i);
int						print_reg(unsigned char *l);
void					copy_io(t_vm *vm, int dest, int src);
void					reg_copy(unsigned char *dest, unsigned char *src);

/*
** flags.c
*/
void					get_champ_position(t_vm *vm, char *str, int pos);
void					fill_champ_position(t_vm *vm, char *str);
void					check_flags(t_vm *vm, char **av, int *i);
void					fill_champs(t_vm *vm, char **av, int *i);

/*
** init.c
*/
void					zero_flags(t_vm *vm);
void					init_vm(t_vm *vm);
void					init_players(int ac, char **av, t_vm *vm);
void					write_info(t_vm *vm, int fd, int *x, int i);
void					jumptable(int a, t_vm *vm, int i);

/*
** util.c
*/
int						blank_pos(char **av);
void					assign_player_num(t_vm *vm, int i, unsigned char **reg);
void					print_core(unsigned char *core, int i);
int						valid_acb(t_instr instr, int b1, int b2, int b3);
void					error(void);

/*
** vis.c
*/
void					vis_highlight_process(t_vm *vm, int i);
void					vis_unhighlight_process(t_vm *vm, int i);
void					vis_print_debug(t_vm *vm);
void					vis_copy(t_vis *dest, unsigned char *src,
							t_vm *vm, int i);
void					vis_update(t_vm *vm, int index);

/*
** reset.c
*/
void					reset_alive_all(t_vm *vm);
void					reset_alive(t_vm *vm, int i);

/*
** acb.c
*/
int						get_offset_index(t_instr *instr, unsigned char acb,
							unsigned char **l);
int						get_offset(t_instr *instr, unsigned char acb,
							unsigned char **l);

/*
** vm_op.c
*/
void					vm_or(t_vm *vm, int i);
void					vm_xor(t_vm *vm, int i);
void					vm_and(t_vm *vm, int i);
void					vm_sub(t_vm *vm, int i);
void					vm_add(t_vm *vm, int i);

/*
** vm_load.c
*/
void					vm_lld(t_vm *vm, int i);
void					vm_lldi(t_vm *vm, int i);
void					vm_ldi(t_vm *vm, int i);
void					vm_ld(t_vm *vm, int i);

/*
** vm_util.c
*/
int						indirect(t_vm *vm, int i, unsigned char opcode,
		t_instr *instr);
int						get_index_one(unsigned char *l);
int						get_index_two(unsigned char *l1, unsigned char *l2);
void					vm_lfork(t_vm *vm, int i);
void					vm_fork(t_vm *vm, int i);

/*
** vm_args.c
*/
void					vm_st(t_vm *vm, int i);
void					vm_sti(t_vm *vm, int i);
void					vm_zjmp(t_vm *vm, int i);
void					vm_live(t_vm *vm, int i);
void					vm_aff(t_vm *vm, int i);

#endif

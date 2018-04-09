/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 09:00:00 by mlu               #+#    #+#             */
/*   Updated: 2018/04/05 15:20:40 by ihodge           ###   ########.fr       */
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
# include <time.h>
# include "libft.h"
# include "op.h"

# define HEADER_SIZE	2192

# define ACB1(a)		((a >> 6) % 4)
# define ACB2(a)		((a >> 4) % 4)
# define ACB3(a)		((a >> 2) % 4)
# define VAL(a)			((int)((unsigned int)a[3] | ((unsigned int)a[2] << 8) | ((unsigned int)a[1] << 16) | ((unsigned int)a[0] << 24)))
# define VAL2(a)		((short)(((unsigned int)a[1]) | ((unsigned int)a[0] << 8)))
# define VAL3(a)		((short)(((unsigned int)a[3]) | ((unsigned int)a[2] << 8)))

# define PC				proc->regs[0]
# define IPC			read_reg(proc, 0)

// # define PARAM1			VAL(PC)
// # define PARAM2			VAL(PC) + 1
// # define PARAM3			VAL(PC) + 2
# define PARAM1			((unsigned short)VAL(PC)) % MEM_SIZE
# define PARAM2			((unsigned short)VAL(PC) + 1) % MEM_SIZE
# define PARAM3			((unsigned short)VAL(PC) + 2) % MEM_SIZE

# define PARAM1M			((unsigned short)VAL(PC)) % MEM_SIZE
# define PARAM2M			((unsigned short)VAL(PC) + 1) % MEM_SIZE
# define PARAM3M			((unsigned short)VAL(PC) + 2) % MEM_SIZE

# define OFF2			instr->core_index

# define OPC			instr->opcode_pos
# define REGI			instr->reg_index[instr->ri]

# define VWRAP			192
# define PRIORITY(a, b) (a > b)

typedef	struct			s_vis
{
	unsigned char		byte;
	int					player;
	int					previous_index;
}						t_vis;

typedef struct			s_io
{
	t_header			*head;
	int					process;
	int					player_int;
	int					op;
	int					alive;
	int					executing;
	unsigned char		regs[REG_NUMBER + 1][REG_SIZE];
	int					carry;
	int					cycle_to_execute;
}						t_io;

typedef struct			s_flags
{
	int					d;
	int					n;
	int					g;
	int					b;
	int					v;
	int					flags;
	long				delay;
	int					noise;
	int					s;
	int					r;
}						t_flags;

typedef struct			s_node {
    t_io				*data;
    int 				priority;
    struct s_node			*next;
}						t_node;

typedef struct			s_queue {
    t_node				*max_p;
    t_node				*min_p;
}						t_queue;

typedef struct			s_vm
{
	t_queue				*q;
	t_header			head[4];
	char				*players[4];
	int					num_players;
	unsigned char		*core;
	t_vis				*vis;
	int					win_player;
	int					cycle_to_die;
	int					counter;
	size_t				dump_cycle;
	int					checks;
	int					cycles;
	int					live;
	int					process_count;
	int					process_num;
	t_flags				f;
}						t_vm;

typedef struct			s_instr
{
	t_vm				*vm;
	t_io				*proc;
	unsigned char		acb;
	unsigned char		*l1;
	unsigned char		*l2;
	unsigned char		*l3;
	unsigned char		*s;
	unsigned int		reg_index[3];
	unsigned int		ri;
	int					opcode_pos;
	int					index;
	int					core_index;
}						t_instr;

void    (*g_jt[16])(t_vm *vm, t_io *proc);
t_instr					init_instr(t_vm *vm, t_io *proc);

void					print_core(unsigned char *test, int i);

int						valid_acb(int op, int acb, t_vm *vm, t_io *proc);
int						valid_acb1(int acb, int op);
int						valid_acb2(int acb, int op);
int						valid_acb3(int acb, int op);
int						valid_register(t_vm *vm, int acb, int op, t_io *proc);
void					modify_carry(t_io *proc, unsigned char *reg);
void					set_cycle_to_execute(t_vm *vm, t_io *proc);

/*
** parse_file.c
*/

int						read_input(int fd, t_header *head, char *body);

/*
** ncurses.c
*/

void					print_curses(t_vm *vm, int i, int x, int y);
void					init_curses(void);

/*
** read_bytes.c
*/

int						*read_acb(unsigned char a);
void					read_bytes(t_vm *vm, int game_end, int counter);

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
t_instr					init_instr(t_vm *vm, t_io *proc);
int						print_reg(unsigned char *l);
void					copy_io(t_vm *vm, int dest, int src);
void					reg_copy(unsigned char *dest, unsigned char *src, int index);

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

/*
** util.c
*/

int						blank_pos(char **av);
void					assign_player_num(t_io *proc, int i, unsigned char **reg);
void					print_core(unsigned char *core, int i);
void					error(void);

/*
** vis.c
*/

void					vis_highlight_process(t_vm *vm, t_io *proc);
void					vis_unhighlight_process(t_vm *vm, t_io *proc);
void					vis_print_debug(t_vm *vm);
void					vis_copy(t_vis *dest, unsigned char *src, t_io *proc, int index);
void					vis_update(t_vm *vm, int index);

/*
** reset.c
*/

void					reset_alive_all(t_vm *vm);

/*
** acb.c
*/

void					get_offset_index(t_instr *instr, unsigned char acb,
							unsigned char **l);
void					get_offset(t_instr *instr, unsigned char acb,
							unsigned char **l);

/*
** vm_op.c
*/

void					vm_or(t_vm *vm, t_io *proc);
void					vm_xor(t_vm *vm, t_io *proc);
void					vm_and(t_vm *vm, t_io *proc);
void					vm_sub(t_vm *vm, t_io *proc);
void					vm_add(t_vm *vm, t_io *proc);

/*
** vm_load.c
*/

void					vm_lld(t_vm *vm, t_io *proc);
void					vm_lldi(t_vm *vm, t_io *proc);
void					vm_ldi(t_vm *vm, t_io *proc);
void					vm_ld(t_vm *vm, t_io *proc);

/*
** vm_util.c
*/
int						indirect(t_vm *vm, unsigned char opcode,
		t_instr *instr);
int						get_index_one(unsigned char *l);
int						get_index_two(t_instr instr);
void					vm_lfork(t_vm *vm, t_io *proc);
void					vm_fork(t_vm *vm, t_io *proc);

/*
** vm_args.c
*/

void					vm_st(t_vm *vm, t_io *proc);
void					vm_sti(t_vm *vm, t_io *proc);
void					vm_zjmp(t_vm *vm, t_io *proc);
void					vm_live(t_vm *vm, t_io *proc);
void					vm_aff(t_vm *vm, t_io *proc);

/*
**	queue_utils.c
*/

t_queue 			    *init_queue(void);
t_node					*init_node(t_io *data, int priority);
void					enqueue(t_queue *queue, t_io *num, int priority);
t_io					*dequeue(t_queue *queue);
t_io					*peek(t_queue *queue);
int						isEmpty(t_queue *queue);
int						get_priority(t_vm *vm, t_io *proc);
void					print_queue(t_queue *queue);


/*
** read_utils.c
*/
unsigned char    read_core1(t_vm *vm, unsigned int pos);
short   read_core2(t_vm *vm, unsigned int pos);
int     read_core4(t_vm *vm, unsigned int pos);
void    write_core(t_vm *vm, unsigned int pos, int value);
int     read_reg(t_io *proc, int reg_num);
void    write_reg(t_io *proc, int reg_num, int value);


int     read_value(t_vm *vm, t_io *proc, int acb);

#endif

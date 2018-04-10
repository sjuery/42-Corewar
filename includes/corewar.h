/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 09:00:00 by mlu               #+#    #+#             */
/*   Updated: 2018/04/09 15:01:05 by anazar           ###   ########.fr       */
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

# define NORM1(a)		(unsigned int)a[3]
# define NORM2(a)		(unsigned int)a[2] << 8
# define NORM3(a)		(unsigned int)a[1] << 16
# define NORM4(a)		(unsigned int)a[0] << 24

# define NORM5(a)		(unsigned int)a[1]
# define NORM6(a)		(unsigned int)a[0] << 8

# define NORM7(a)		(unsigned int)a[3]
# define NORM8(a)		(unsigned int)a[2] << 8

# define VAL(a)			((int)(NORM1(a) | NORM2(a) | NORM3(a) | NORM4(a)))
# define VAL2(a)		((short)(NORM5(a) | NORM6(a)))
# define VAL3(a)		((short)(NORM7(a) | NORM8(a)))

# define PC				proc->regs[0]
# define IPC			read_reg(proc, 0)

# define PARAM1			((unsigned short)VAL(PC)) % MEM_SIZE
# define PARAM2			((unsigned short)VAL(PC) + 1) % MEM_SIZE
# define PARAM3			((unsigned short)VAL(PC) + 2) % MEM_SIZE

# define QMIN			queue->min_p->priority
# define QMAX			queue->max_p->priority
# define QTMP			tmp->next->priority

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
	int					i;
}						t_flags;

typedef struct			s_node {
	t_io				*data;
	int					priority;
	struct s_node		*next;
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

void	(*g_jt[16])(t_vm *vm, t_io *proc);

/*
** util.c
*/
void					error(void);
int						blank_pos(char **av);
void					print_core(unsigned char *core, int i);
void					assign_player_num(t_io *proc, int i,
							unsigned char **reg);

/*
** acb.c
*/
int						valid_acb(int op, int acb, t_vm *vm, t_io *proc);
int						valid_acb1(int acb, int op);
int						valid_acb2(int acb, int op);
int						valid_acb3(int acb, int op);

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
void					gui_interaction(t_vm *vm, int c);
void					read_bytes(t_vm *vm, int game_end, int counter);

/*
** process_update.c
*/
void					process_update(t_vm *vm);

/*
** cycle.c
*/
void					check_executing_processes(t_vm *vm, int *game_end);
void					add_acb_bytes(int op, int *acb_val, int acb);
void					update_pc(t_io *proc, int op, int acb);
void					cycle_scheduler(t_vm *vm, int *counter);
void					set_cycle_to_execute(t_vm *vm, t_io *proc);

/*
** reg_util.c
*/
void					play_spawn(t_vm *vm);
void					into_reg(unsigned int val, unsigned char *reg);
int						valid_reg_num(int reg_offset, t_vm *vm, t_io *proc);
void					add_to_reg_offset(int *reg_offset, int acb, int op);
int						valid_register(t_vm *vm, int acb, int op, t_io *proc);

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
void					init_vm(t_vm *vm, int i, int x);
void					init_players(int ac, char **av, t_vm *vm);
void					write_info(t_vm *vm, int fd, int *x, int i);

/*
** util.c
*/
int						blank_pos(char **av);
void					assign_player_num(t_io *proc, int i,
							unsigned char **reg);
void					print_core(unsigned char *core, int i);
void					error(void);

/*
** vis.c
*/
void					vis_print_debug(t_vm *vm, int i);
void					vis_update(t_vm *vm, int index);
void					vis_copy(t_vis *dest, int src, t_io *proc, int index);

/*
** vis_highlight.c
*/
void					vis_highlight_process(t_vm *vm, t_io *proc);
void					vis_unhighlight_process(t_vm *vm, t_io *proc);

/*
** reset.c
*/
void					reset_alive_all(t_vm *vm);

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
void					modify_carry(t_io *proc, unsigned char value);
int						get_priority(t_vm *vm, t_io *proc);
void					vm_lfork(t_vm *vm, t_io *proc);
void					vm_fork(t_vm *vm, t_io *proc);
void					read_acb_info(t_vm *vm, t_io *proc,
							int *pos_code, unsigned char *acb);

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
t_io					*peek(t_queue *queue);
int						is_empty(t_queue *queue);
void					print_queue(t_queue *queue);

/*
** queue.c
*/
void					enqueue(t_queue *queue, t_io *num, int priority);
t_io					*dequeue(t_queue *queue);
t_queue					*init_queue(void);
t_node					*init_node(t_io *data, int priority);

/*
** read_utils.c
*/
char					read_core1(t_vm *vm, unsigned int pos);
short					read_core2(t_vm *vm, unsigned int pos);
int						read_core4(t_vm *vm, unsigned int pos);
int						read_reg(t_io *proc, int reg_num);
short					read_reg2(t_io *proc, int reg_num);

/*
** write_utils.c
*/
void					write_core(t_vm *vm, unsigned int pos, int value);
void					write_reg(t_io *proc, int reg_num, int value);

/*
** read_value.c
*/
int						read_value(t_vm *vm, t_io *proc, int acb);
int						read_value_index(t_vm *vm, t_io *proc, int acb);
int						read_value_load(t_vm *vm, t_io *proc, int acb);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 15:07:48 by sjuery            #+#    #+#             */
/*   Updated: 2018/04/09 12:32:15 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
#define LINE_SIZE	39

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

# include "libft.h"
# include "op.h"

typedef struct				s_assembler
{
    int                     i;
	int						sfile;
    int                     corefile;
    char                    *line;
    int                     ls;
	int						offset;
	int						instruct_offset;
	int						instruct_num;
	int						final_offset;
	int						*prog_name;
	int						*comment;
	struct s_label			*label;
	struct s_label_ref		*label_ref;
	struct s_instruction	**arr;
}							t_assembler;

typedef struct				s_label
{
	struct s_label			*next;
	char					*name;
	int						offset;
}							t_label;

typedef struct				s_label_ref
{
	struct s_label_ref		*next;
	char					*name;
	int						param_num;
	int						instruct_num;
	int						instruct_offset;
	int						dir;
}							t_label_ref;

typedef struct				s_instruction
{
	int						op;
	int						acb;
	char					**params;
}							t_instruction;

typedef struct				s_op
{
	char					*opstr;
	int						params;
	int						ptype[MAX_ARGS_NUMBER];
	int						opcode;
	int						cycles;
	char					*description;
	int						acb;
	int						index;
}							t_op;

t_op						g_optab[17];
void						parse_instructions(t_assembler *st);
int			                convert_to_hex(t_assembler *st);
int							check_param_type(char *param, int i, int param_num);
void						print_sp_nl(t_assembler *st, int *y);
void						break_shit_up(t_assembler *st, int size, int res,
		int *y);
void						print_header(t_assembler *st, int *y);
void						print_parameters(t_assembler *st, int i, int *y);
void						print_shit(t_assembler *st);
void						handle_error(char *error_type, t_assembler *st);
#endif

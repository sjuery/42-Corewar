/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 15:07:48 by sjuery            #+#    #+#             */
/*   Updated: 2018/02/12 22:00:31 by ihodge           ###   ########.fr       */
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

# include "../libft/includes/libft.h"
# include "op.h"

typedef struct				s_assembler
{
    int                     i;
	int						sfile;
    int                     corefile;
    char                    *line;
    int                     ls;
	int						offset;
	struct s_label			*label;
}							t_assembler;

//calculate number of bytes per line: each op is 1 byte, figure out if it has an acb, if it does: convert to binary, add 1 bytes to the line, figure out type: if acb says param takes a register: add 1 byte. if it acb says it takes an indirect param: add 2 bytes
//if acb says it takes direct, and optab says it takes an index: add 2 bytes, if it doesn't take an index add 4 bytes
//goal: first pass: keep track of byte offset so that when we get to a label, we can record the offset of the label in a linked list.
//second pass: keep track of offset again while going through the file so that when we get to an instruction that takes a label, we know the offset of the instruction and the offset of the label it refers too (from the linked list). reference = label offset minus instruction offset

typedef struct				s_label
{
	struct s_label			*next;
	char					*name;
	int						offset;
}							t_label;

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
void						handle_error(char *error_type, t_assembler *st);
#endif

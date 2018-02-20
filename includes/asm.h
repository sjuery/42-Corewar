/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjuery <sjuery@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 15:07:48 by sjuery            #+#    #+#             */
/*   Updated: 2018/02/19 16:37:22 by ihodge           ###   ########.fr       */
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
	struct s_label			*label;
}							t_assembler;

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

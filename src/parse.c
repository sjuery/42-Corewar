/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 18:03:50 by ihodge            #+#    #+#             */
/*   Updated: 2018/02/12 22:17:00 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdio.h>

//need to error out for same label names

static void	save_labels(t_label **labels, char *name, int offset)
{
	t_label	*head;

	head = (*labels);
	if (head)
	{
		while (head->next)
			head = head->next;
		head->next = (t_label*)ft_memalloc(sizeof(t_label));
		head->next->name = name;
		head->next->offset = offset;
		head->next->next = NULL;
	}
	else
	{
		(*labels) = (t_label*)ft_memalloc(sizeof(t_label));
		(*labels)->name = name;
		(*labels)->offset = offset;
		(*labels)->next = NULL;
	}
}

static int	parameter_type(char *param, int i, int param_num, t_assembler *st)
{
	ft_printf("param[0] = %c, ptype = %i\n", param[0], g_optab[i].ptype[param_num]);
	if (g_optab[i].ptype[param_num] == 3)
	{
		if (param[0] == 'r')
			return (REG_CODE);
		if (param[0] == DIRECT_CHAR)
			return (DIR_CODE);
	}
	if (param[0] == 'r' && g_optab[i].ptype[param_num] & REG_CODE)
			return (REG_CODE);
	else if (param[0] == DIRECT_CHAR && g_optab[i].ptype[param_num] & DIR_CODE)
			return (DIR_CODE);
	else if (g_optab[i].ptype[param_num] & IND_CODE)
		return (IND_CODE);
	handle_error("Error: Wrong parameter type given for instruction", st);
	return (0);
}

static void	create_acb(char **instruction, int i, t_assembler *st)
{
	int j = 1;
	int	acb = 0;
	int param_type = 0;

	st->offset++;//add one byte for acb
	while (j <= g_optab[i].params) 
	{
		param_type = parameter_type(instruction[j], i, j - 1, st);
		st->offset += param_type;
		if (param_type == 2 && !g_optab[i].index)//correct for dir_code with no index, +2 bytes
			st->offset += 2;
		j == 1 ? acb = param_type << 6 : 0;
		j == 2 ? param_type = param_type << 4 : 0; 
		j == 2 ? acb = param_type | acb : 0;
		j == 3 ? param_type = param_type << 2 : 0; 
		j == 3 ? acb = param_type | acb: 0;
		j++;
	}
	ft_printf("acb = %x\n", acb);
	if (instruction[j++])
		handle_error("Error: Instruction has too many parameters", st);
}

static void	convert_instruction(char **instruction, t_assembler *st)
{
	int i = 0;

	while (g_optab[i].opcode)
	{
		if (ft_strequ(g_optab[i].opstr, instruction[0]))
			break ;
		i++;
	}
	st->offset++;//add one byte for opcode
	if (g_optab[i].acb)
		create_acb(instruction, i, st);
	else//if no acb that means we only have one parameter for the instruction
	{
		printf("Instructio[2] = %s\n", instruction[2]);
		if (instruction[2] != 0)
			handle_error("Error: Instruction has too many parameters", st);
		st->offset += g_optab[i].ptype[0];
		if (!g_optab[i].index)
			st->offset += 2;
	}
	ft_printf("line offset: %i\n", st->offset);
}

void	parse_instructions(t_assembler *st)
{
	int i = 0;
	char **instruction;
	char *name;
	
	name = NULL;
	if (!ft_iswhitespace(st->line[0]))//checking for lines with labels
	{
		while (st->line[i] != LABEL_CHAR)
		{
			if (!ft_islower(st->line[i]) && !ft_isdigit(st->line[i])
					&& st->line[i] != '_')
				handle_error("Error: Invalid label name", st);
			else if (st->line[i] == '\n')
				handle_error("Error: Wtf is this?", st);
			i++;
		}
		name = ft_strsub(st->line, 0, i);
		ft_printf("label: %s\n", name);
		i++;
	}
	while (ft_iswhitespace(st->line[i]))
		i++;
	instruction = ft_split_by_delims(st->line + i, "\t ,");
	i = 0;
	while (instruction[i])
	{
		printf("%s ", instruction[i]);
		i++;
	}
	printf("\n");
	if (name)
		save_labels(&st->label, name, st->offset);
	convert_instruction(instruction, st);
}

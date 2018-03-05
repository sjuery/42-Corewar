/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <ihodge@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 18:03:50 by ihodge            #+#    #+#             */
/*   Updated: 2018/03/03 15:49:53 by sjuery           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdio.h>

//need to error out for same label names
//transmission control ascii chars in header? 0x17, 3, 0xff.. etc

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

static t_label_ref	*save_label_refs(t_label_ref **label_ref)
{
	t_label_ref	*head;

	head = (*label_ref);
	if (head)
	{
		while (head->next)
			head = head->next;
		head->next = (t_label_ref*)ft_memalloc(sizeof(t_label_ref));
		head->next->next = NULL;
		return (head->next);
	}
	else
	{
		(*label_ref) = (t_label_ref*)ft_memalloc(sizeof(t_label_ref));
		(*label_ref)->next = NULL;
		return ((*label_ref));
	}
	return (head);
}

int			check_param_type(char *param, int i, int param_num)
{
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
		return (IND_SIZE);
	return (0);
}

//only create/print to file after validating
//non-existing file segfault

static int	parameter_type(char *param, int i, int param_num, t_assembler *st)
{
	int param_type;
	t_label_ref *label_ref;

	param_type = 0;
	label_ref = NULL;
	param_type = check_param_type(param, i, param_num);
	if (param_type > 0)
	{

		if (param[0] == LABEL_CHAR || param[1] == LABEL_CHAR)
		{
			label_ref = save_label_refs(&st->label_ref);
			label_ref->name = param[0] == DIRECT_CHAR ? param + 2: param + 1;
			param[0] == DIRECT_CHAR ? label_ref->dir = 1 : 0;
			label_ref->param_num = param_num;
			label_ref->instruct_num = st->instruct_num;
			label_ref->instruct_offset = st->instruct_offset;
		}
		else
			st->arr[st->instruct_num]->params[param_num] = param;
		return (param_type);
	}
	handle_error("Error: Wrong parameter type given for instruction", st);
	return (0);
}

static void	create_acb(char **instruction, int i, t_assembler *st)
{
	int j = 1;
	int	acb = 0;
	int param_type = 0;

	st->offset++;
	while (j <= g_optab[i].params)
	{
		param_type = parameter_type(instruction[j], i, j - 1, st);
		st->offset += param_type;
		if (instruction[j][0] == DIRECT_CHAR && !g_optab[i].index)
			st->offset += 2;
		if (param_type == 2 && !(instruction[j][0] == DIRECT_CHAR))
			param_type++;
		j == 1 ? acb = param_type << 6 : 0;
		j == 2 ? param_type = param_type << 4 : 0;
		j == 2 ? acb = param_type | acb : 0;
		j == 3 ? param_type = param_type << 2 : 0;
		j == 3 ? acb = param_type | acb: 0;
		j++;
	}
	st->arr[st->instruct_num]->acb = acb;
	if (instruction[j] && instruction[j][0] != COMMENT_CHAR)
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
	st->arr[st->instruct_num] = ft_memalloc(sizeof(t_instruction));
	st->arr[st->instruct_num]->params = ft_memalloc(sizeof(char*) * MAX_ARGS_NUMBER);
	st->arr[st->instruct_num]->op = g_optab[i].opcode;
	st->instruct_offset = st->offset;
	st->offset++;
	if (g_optab[i].acb)
		create_acb(instruction, i, st);
	else
	{
		if (instruction[2] && instruction[2][0] != COMMENT_CHAR)
			handle_error("Error: Instruction has too many parameters", st);
		st->offset += parameter_type(instruction[1], i, 0, st);
		if (!g_optab[i].index)
			st->offset += 2;
	}
	st->instruct_num++;
}

void	parse_instructions(t_assembler *st)
{
	int i = 0;
	char **instruction;
	char *name;

	name = NULL;
	if (!ft_iswhitespace(st->line[0]))
	{
		while (st->line[i] != LABEL_CHAR)
		{
			if (st->line[i] == COMMENT_CHAR)
				return ;
			if (!ft_islower(st->line[i]) && !ft_isdigit(st->line[i])
					&& st->line[i] != '_')
				handle_error("Error: Invalid label name", st);
			else if (st->line[i] == '\n')
				handle_error("Error: Wtf is this?", st);
			i++;
		}
		name = ft_strsub(st->line, 0, i);
		i++;
	}
	while (ft_iswhitespace(st->line[i]))
		i++;
	if (st->line[i] == COMMENT_CHAR)
		return ;
	instruction = ft_split_by_delims(st->line + i, "\t ,");
	if (name)
		save_labels(&st->label, name, st->offset);
	convert_instruction(instruction, st);
	st->final_offset = st->offset;
}

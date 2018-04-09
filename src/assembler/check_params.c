/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <ihodge@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 18:03:50 by ihodge            #+#    #+#             */
/*   Updated: 2018/04/09 13:01:57 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdio.h>

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

void		check_lexical_errors(t_assembler *st, char *param)
{
	int i;

	i = 0;
	while (param[i] && param[i] != COMMENT_CHAR)
	{
		if (!ft_isalnum(param[i]) && param[i] != LABEL_CHAR &&
				param[i] != DIRECT_CHAR && param[i] != 'r' && param[i] != '-'
				&& param[i] != '_')
		{
			handle_error("Error: Lexical error for instruction\n", st);
		}
		i++;
	}
}

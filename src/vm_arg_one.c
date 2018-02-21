/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_arg_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/02/07 17:43:29 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	vm_live(void)
{
	printf("live called");
}

void	vm_zjmp(void)
{
	printf("zjmp called");
}


void	vm_sti(void)
{
	printf("sti called");
}

void	vm_lfork(void)
{
	printf("lfork called");
}

void	vm_fork(void)
{
	printf("fork called");
}
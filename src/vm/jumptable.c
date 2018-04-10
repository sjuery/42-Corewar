/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jumptable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 15:58:53 by anazar            #+#    #+#             */
/*   Updated: 2018/04/01 19:08:26 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	(*g_jt[16])(t_vm *vm, t_io *proc) = {
	vm_live,
	vm_ld,
	vm_st,
	vm_add,
	vm_sub,
	vm_and,
	vm_or,
	vm_xor,
	vm_zjmp,
	vm_ldi,
	vm_sti,
	vm_fork,
	vm_lld,
	vm_lldi,
	vm_lfork,
	vm_aff
};

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jumptable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 15:58:53 by anazar            #+#    #+#             */
/*   Updated: 2018/03/31 13:26:57 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

// if op - 1 == 1, 2, 8, 9, 11 || op == 2, 3, 9, 10, 12

void    (*g_jt[16])(t_vm *vm, int i) = {
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

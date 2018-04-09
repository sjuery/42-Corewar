/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 17:46:56 by anazar            #+#    #+#             */
/*   Updated: 2018/04/09 15:38:26 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

char    read_core1(t_vm *vm, unsigned int pos)
{
    return (vm->core[pos % MEM_SIZE]);
}

short   read_core2(t_vm *vm, unsigned int pos)
{
    return (vm->core[pos % MEM_SIZE] << 8 + vm->core[(pos + 1) % MEM_SIZE]);
}

int     read_core4(t_vm *vm, unsigned int pos)
{
    return (vm->core[pos % MEM_SIZE] << 24 +
        vm->core[(pos + 1) % MEM_SIZE] << 16 +
        vm->core[(pos + 2) % MEM_SIZE] << 8 +
        vm->core[(pos + 3) % MEM_SIZE]);
}

int     read_reg2(t_vm *vm, int reg_num)
{
    return (vm->regs[reg_num][3] | (vm->regs[reg_num][2] << 8));
}

int     read_reg(t_vm *vm, int reg_num)
{
    return (VAL(vm->regs[reg_num]));
}

void    write_reg(t_vm *vm, int reg_num, int value)
{
    vm->regs[reg_num][0] = (value >> 24) % 0x100;
    vm->regs[reg_num][1] = (value >> 16) % 0x100;
    vm->regs[reg_num][2] = (value >> 8) % 0x100;
    vm->regs[reg_num][3] = value % 0x100;
}

void    write_core(t_vm *vm, unsigned int pos, int value)
{
    vm->core[pos % MEM_SIZE] = (value >> 24) % 0x100;
    vm->core[(pos + 1) % MEM_SIZE] = (value >> 16) % 0x100;
    vm->core[(pos + 2) % MEM_SIZE] = (value >> 8) % 0x100;
    vm->core[(pos + 3) % MEM_SIZE] = value % 0x100;
}

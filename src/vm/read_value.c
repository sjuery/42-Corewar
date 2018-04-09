/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 15:01:50 by anazar            #+#    #+#             */
/*   Updated: 2018/04/09 14:29:13 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

unsigned int     read_value(t_vm *vm, t_io *proc, int acb, int bin)
{
    unsigned int reg;
    unsigned int value;
    unsigned int index;

    value = 0;
    if (acb == 1)
    {
        reg = read_core1(vm, read_reg(proc, 0));
        value = read_reg(proc, reg);
        write_reg(proc, 0, read_reg(proc, 0) + 1);
    }
    else if (acb == 2)
    {
        value = read_core4(vm, read_reg(proc, 0));
        write_reg(proc, 0, read_reg(proc, 0) + 4);
    }
    else if (acb == 3)
    {
        index = read_core2(vm, read_reg(proc, 0));
        value = read_core4(vm, index % (bin ? IDX_MOD : MEM_SIZE));
        write_reg(proc, 0, read_reg(proc, 0) + 2);
    }
    return (value);
}


unsigned int     read_value_index(t_vm *vm, t_io *proc, int acb, int bin)
{
    unsigned int reg;
    unsigned int value;
    unsigned int index;

    value = 0;
    if (acb == 1)
    {
        reg = read_core1(vm, read_reg(proc, 0));
        value = read_reg(proc, reg);
        write_reg(proc, 0, read_reg(proc, 0) + 1);
    }
    else if (acb == 2)
    {
        value = read_core2(vm, read_reg(proc, 0));
        write_reg(proc, 0, read_reg(proc, 0) + 2);
    }
    else if (acb == 3)
    {
        index = read_core2(vm, read_reg(proc, 0));
        value = read_core4(vm, index % (bin ? IDX_MOD : MEM_SIZE));
        write_reg(proc, 0, read_reg(proc, 0) + 2);
    }
    return (value);
}

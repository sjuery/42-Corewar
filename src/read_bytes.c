/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bytes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/02/23 19:35:35 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void printbits(unsigned char octet)
{
    char arr[9];


    arr[0] = ((octet & 0b10000000) != 0) + '0';
    arr[1] = ((octet & 0b01000000) != 0) + '0';
    arr[2] = ((octet & 0b00100000) != 0) + '0';
    arr[3] = ((octet & 0b00010000) != 0) + '0';
    arr[4] = ((octet & 0b00001000) != 0) + '0';
    arr[5] = ((octet & 0b00000100) != 0) + '0';
    arr[6] = ((octet & 0b00000010) != 0) + '0';
    arr[7] = ((octet & 0b00000001) != 0) + '0';
	arr[8] = '\n';
    write(1, &arr, 9);
}

int		*read_acb(unsigned char a)
{
	int	arr[3];
	int *ret;

/*
	ret = 0;
	//a += 226;
	while (a >= 2)
	{
		ret = ret * 10 + (a % 2);
		a = a / 2;
	}
	ret = ret * 10 + a;
	printbits(ret);
	ft_printf("\nRET %x\n", ret);
	return (ret);*/
	arr[0] = (a >> 6) % 4;
	arr[1] = (a >> 4) % 4;
	arr[2] = (a >> 2) % 4;
	DBG_INT("A: ", a);
	printbits(a);
	printbits(arr[0]);
	printbits(arr[1]);
	printbits(arr[2]);
	ret = arr;
	return (ret);
}

void	read_bytes(t_vm *vm, int i)
{
	while (++i < vm->process_count)
	{
		if (vm->info[i].alive == 1)
		{
			ft_printf("\nByte Read [%#0.2hhx] ", vm->info[i].body[vm->info[i].index]);
			jumptable(vm->info[i].body[vm->info[i].index], vm, i);
		}
	}
}


// ./corewar resources/champs/examples/zork.cor resources/champs/examples/bigzork.cor resources/champs/examples/helltrain.cor resources/champs/examples/turtle.cor

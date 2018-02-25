/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bytes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/02/24 13:54:15 by anazar           ###   ########.fr       */
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
	char *addrs[4] = {"None", "Register", "Direct", "Indirect"};
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
	arr[0] = ACB1(a);
	arr[1] = ACB2(a);
	arr[2] = ACB3(a);
	DBG_INT("A: ", a);
	ft_putendl(addrs[ACB1(a)]);
	ft_putendl(addrs[ACB2(a)]);
	ft_putendl(addrs[ACB3(a)]);
	//DBG_INT("ACB1: ", ACB1(a));
	//DBG_INT("ACB2: ", ACB2(a));
	//DBG_INT("ACB3: ", ACB3(a));
//	printbits(a);
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
		if (vm->info[i].alive >= 1)
		{
			ft_printf("\nByte Read [%#0.2hhx] ", vm->core[vm->info[i].start + vm->info[i].index]);
			jumptable(vm->core[vm->info[i].start + vm->info[i].index], vm, i);
		}
	}
	// execute game rules, check the current cycle, check to see if we need ot kill stuff
	// if we dont need to kill stuff, call read_bytes again, otherwise, call function
	// that will kill processes, etc. and than call read_bytes again
	// when we execute game rule, if all processes are dead, instead of going back to read_bytes
	// it will go to game over to display winner
}


// ./corewar resources/champs/examples/zork.cor resources/champs/examples/bigzork.cor resources/champs/examples/helltrain.cor resources/champs/examples/turtle.cor

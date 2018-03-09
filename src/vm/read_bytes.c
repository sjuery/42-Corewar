/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bytes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/03/08 18:38:58 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "asm.h"

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

void	reset_alive_all(t_vm *vm)
{
	int i;

	i = 0;
	ft_printf("RESETING ALIVE cycle[%i] todie[%i]\n", vm->cycles, vm->cycle_to_die);
	while (i < vm->process_count)
	{
		if (vm->info[i].alive == 0)
		{
			ft_printf("IM DED! cycle[%i] process[%i]\n", vm->cycles, i);
			vm->info[i].executing = 0;
		}
		vm->info[i].alive = 0;
		i++;
	}
}

void	reset_alive(t_vm *vm, int i)
{
	ft_printf("RESETING ALIVE cycle[%i] todie[%i]\n", vm->cycles, vm->cycle_to_die);
	if (vm->info[i].alive == 0)
	{
		ft_printf("IM DED! cycle[%i] process[%i]\n", vm->cycles, i);
		vm->info[i].executing = 0;
	}
	vm->info[i].alive = 0;
}

void	check_executing_processes(t_vm *vm, int *game_end)
{
	int i;

	i = 0;
	while (i < vm->process_count)
	{
		if (vm->info[i].executing == 1)
		{
			//ft_printf("IM STILL EXECUTING! proceess[%i];\n", i);
			*game_end = 0;
		}
		i++;
	}
}

void	process_update(t_vm *vm, int i)
{
	int op;

	//ft_printf("\nProcess number[%i], Byte Read [%#0.2hhx], Index [%i]", i, vm->core[vm->info[i].start + vm->info[i].index], vm->info[i].index);
	if (vm->info[i].start + vm->info[i].index > 4095)//wrapping around the core
		vm->info[i].index = vm->info[i].start * -1;
	op = vm->core[vm->info[i].start + vm->info[i].index];
	if (op > 0 && op < 17 && vm->info[i].wait_cycle == g_optab[op - 1].cycles)
	{
		ft_printf("cycles[%i] op[%02hhx]\n", vm->cycles, op);
		jumptable(op, vm, i);
		ft_putchar('\n');
		vm->info[i].wait_cycle = 0;
	}
	else if (op > 0 && op < 17)
		vm->info[i].wait_cycle++;
	else
		vm->info[i].index++;
	vm->info[i].cycles++;
	//if (vm->info[i].cycles % vm->cycle_to_die == 0)
	//	reset_alive(vm, i);
}

//implement decrease of CYCLE_TO_DIE with NBR_LIVE
//keep track of which player num is winning
//do processes need to keep track of how many cycles since birth? ecah have their pown cycle count?

void	read_bytes(t_vm *vm, int i)
{
	int game_end;
	int	counter;

	counter = 1;
	game_end = 1;
	while (1)
	{
		i = vm->process_count - 1;
		while (i >= 0)
		{
			if (vm->info[i].executing == 1)
				process_update(vm, i);
			i--;
		}
		vm->cycles++;
		//ft_printf("cycle [%i] cycle_to_die [%i]\n", vm->cycles, vm->cycle_to_die);
		check_executing_processes(vm, &game_end);
		if (counter == 0)
		{
			vm->checks++;
			reset_alive_all(vm);
		}
		counter = (counter + 1) % vm->cycle_to_die;;
		if (vm->checks == MAX_CHECKS)
		{
			vm->cycle_to_die -= CYCLE_DELTA;
			vm->checks = 0;
		}
		if (game_end)
			break ;
		//else
		//	print_core(vm->core, -1);//preferably, here we would update ncurses and display
		game_end = 1;
	}
	print_core(vm->core, -1);
}

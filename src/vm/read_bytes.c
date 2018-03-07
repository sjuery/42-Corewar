/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bytes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/03/06 21:11:57 by anazar           ###   ########.fr       */
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

//define MAX_PROCESSES 1024

/*void	read_bytes(t_vm *vm, int i)
{
	//while (++i < vm->process_count)
	while (++i < 1024)
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
}*/

/*void	reset_alive(t_vm *vm)//should only be called for a specific process when it has reached CYCLES_TO_DIE cycles
{
	int i = 0;

	//ft_printf("\nreset alive\n");
	while (i <= 1023)
	{
		if (vm->info[i].alive == 0)
			vm->info[i].executing = 0;
		vm->info[i].alive = 0;
		i++;
	}
}*/

void	reset_alive(t_vm *vm, int i)
{
	//ft_printf("\nreset alive\n");
	if (vm->info[i].alive == 0)
		vm->info[i].executing = 0;
	vm->info[i].alive = 0;
}

void	check_executing_processes(t_vm *vm, int *game_end)
{//this function checks if all processes have finished executing
	int i;

	i = 0;
	while (i < 1022)
	{
		if (vm->info[i].executing == 1)
			*game_end = 0;
		i++;
	}
}

//question: can a process execute other processes instructions? or can they only execute their own and their parents?
//implement decrease of CYCLE_TO_DIE
void	read_bytes(t_vm *vm, int i)
{
	int game_end;
	int op;

	game_end = 1;
	while (1)//game engine
	{
		i = 1021;// processes 1022, 1023 overflow
		while (i >= 0)//must execute processes from the last born to first
		{
			if (vm->info[i].executing == 1)
			{
				//ft_printf("\nProcess number[%i], Byte Read [%#0.2hhx], Index [%i]", i, vm->core[vm->info[i].start + vm->info[i].index], vm->info[i].index);
				if (vm->info[i].start + vm->info[i].index > 4095)//wrapping around the core
					vm->info[i].index = vm->info[i].start * -1;
				op = vm->core[vm->info[i].start + vm->info[i].index];
				if ((op > 0 && op <= 16) && vm->info[i].wait_cycle == g_optab[op - 1].cycles)
				{
					jumptable(op, vm, i);
					ft_putchar('\n');
					vm->info[i].wait_cycle = 0;
				}
				else if (op > 0)
					vm->info[i].wait_cycle++;
				else//not an intruction, increase program counter/index
					vm->info[i].index++;
				vm->info[i].cycles++;
				if (vm->info[i].cycles % CYCLE_TO_DIE == 0)//if process is alive (has called live) -->reset alive; else, it can no longer execute
					reset_alive(vm, i);
			}
			i--;
		}
		vm->cycles++;
		ft_printf("cycle [%i]\n", vm->cycles);
		check_executing_processes(vm, &game_end);//sets flag for whether the game will end
		if (game_end)//this means all processes have stopped executing
			break ;
		game_end = 1;
		//else
		//	print_core(vm->core, -1);//preferably, here we would update ncurses and display
	}
}

	// execute game rules, check the current cycle, check to see if we need to kill stuff
	// if we dont need to kill stuff, call read_bytes again, otherwise, call function
	// that will kill processes, etc. and than call read_bytes again
	// when we execute game rule, if all processes are dead, instead of going back to read_bytes
	// it will go to game over to display winner
// ./corewar resources/champs/examples/zork.cor resources/champs/examples/bigzork.cor resources/champs/examples/helltrain.cor resources/champs/examples/turtle.cor

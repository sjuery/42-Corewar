/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/03/21 21:49:32 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	error(void)
{
	ft_printf("Corewar Usage\n");
	ft_printf("./corewar { d <value> | g | b | v }");
	ft_printf(" { n <value> | champion.cor }\n");
	ft_printf("-dump, -d			dump mode\n");
	ft_printf("-graphic, -g			graphic mode\n");
	ft_printf("-debug, -b			debug mode\n");
	ft_printf("-verbose, -v			verbose mode\n");
	ft_printf("-number, -n			designate champ slot\n");
	exit(0);
}

int		blank_pos(char **av)
{
	int	i;

	i = 0;
	while (av[i] && i < 4)
		++i;
	return (i);
}

void	print_core(unsigned char *core, int i)
{
	while (++i < MEM_SIZE)
	{
		if (i % 64 == 0)
			ft_printf("\n");
		if (core[i] < 16 && core[i] >= 0)
			ft_printf("0");
		ft_printf("%hhx ", core[i]);
	}
	ft_putchar('\n');
}

void	assign_player_num(t_vm *vm, int i, unsigned char **reg)
{
	*reg = vm->info[i].regs[1];
	(*reg)[0] = 0xff;
	(*reg)[1] = 0xff;
	(*reg)[2] = 0xff;
	(*reg)[3] = 0xff - i;
	vm->info[i].player_num[0] = 0xff;
	vm->info[i].player_num[1] = 0xff;
	vm->info[i].player_num[2] = 0xff;
	vm->info[i].player_num[3] = 0xff - i;
	vm->info[i].player_int = i + 1;
}

int		valid_acb(t_instr instr, int b1, int b2, int b3)
{
	return (ACB1(instr.acb) == b1 && ACB2(instr.acb)
			== b2 && ACB3(instr.acb) == b3);
}

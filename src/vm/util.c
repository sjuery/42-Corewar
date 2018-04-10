/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/04/06 11:53:12 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "asm.h"

void	error(void)
{
	ft_printf("Corewar Usage\n");
	ft_printf("./corewar { d <value> | g | b | r | s <value> | i }");
	ft_printf(" { n <value> | champion.cor }\n");
	ft_printf("-dump, -d			dump mode\n");
	ft_printf("-graphic, -g			graphic mode\n");
	ft_printf("-debug, -b			debug mode\n");
	ft_printf("-rainbow, -r			special rainbow mode (only in graphic)\n");
	ft_printf("-sound, -s			sound on (1 spawn, 2 death, 3 all)\n");
	ft_printf("-number, -n			designate champ slot (valid 1-4)\n");
	ft_printf("-intro, -i			toggle voice intro\n");
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

void	assign_player_num(t_io *proc, int i, unsigned char **reg)
{
	*reg = proc->regs[1];
	(*reg)[0] = 0xff;
	(*reg)[1] = 0xff;
	(*reg)[2] = 0xff;
	(*reg)[3] = 0xff - i;
	proc->player_int = i + 1;
}

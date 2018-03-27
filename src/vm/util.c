/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/03/27 15:08:09 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "asm.h"

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

int		valid_acb(int op, int acb, t_vm *vm, int i)
{
	int params;

	params = g_optab[op].params;
	if (params == 1)
		return (valid_acb1(acb, op));
	if (params == 2)
		return (valid_acb2(acb, op) & valid_register(vm, acb, op, i));
	if (params == 3)
		return (valid_acb3(acb, op) & valid_register(vm, acb, op, i));
	ft_printf("INVALID BITCH valid_acb\n");
	return (0);
}

int		valid_reg_num(int reg_offset, t_vm *vm, int i)
{
	int reg;

	reg = vm->core[PARAM1 + reg_offset];
	if (reg >= 1 && reg <= 16)
		return (1);
	return (0);
}

void	add_to_reg_offset(int *reg_offset, int acb, int op)
{
	*reg_offset += 2;
	if (acb == 2 && !g_optab[op].index)
		*reg_offset += 2;
}

int		valid_register(t_vm *vm, int acb, int op, int i)
{
	int	reg_offset;

	reg_offset = 2;
	if (ACB1(acb) == 1)
	{
		if (valid_reg_num(reg_offset, vm, i))
			reg_offset++;
		else
			return (0);
	}
	else
		add_to_reg_offset(&reg_offset, ACB1(acb), op); 
	if (ACB2(acb) == 1)
	{
		if (valid_reg_num(reg_offset, vm, i))
			reg_offset++;
		else
			return (0);
	}
	else
		add_to_reg_offset(&reg_offset, ACB2(acb), op);
	if (g_optab[op].params == 3 && ACB3(acb) == 1)
		return (valid_reg_num(reg_offset, vm, i) ? 1 : 0);
	return (1);
}

int		valid_acb1(int acb, int op)
{
	if (g_optab[op].ptype[0] & ACB1(acb))
		return (1);
	ft_printf("INVALID BITCH! op[%s]\n", g_optab[op].opstr);
	return (0);
}

int		valid_acb2(int acb, int op)
{
	int	param1;
	int	param2;

	param1 = g_optab[op].ptype[0];
	param2 = g_optab[op].ptype[1];
	if (((ACB1(acb) <= param1) && param1 & ACB1(acb))
			&& (ACB2(acb) <= param2 && param2 & ACB2(acb)))
		return (1);
	ft_printf("INVALID BITCH! op[%s] valid_acb2\n", g_optab[op].opstr);
	return (0);
}

int		valid_acb3(int acb, int op)
{
	int	param1;
	int	param2;
	int	param3;

	param1 = g_optab[op].ptype[0];
	param2 = g_optab[op].ptype[1];
	param3 = g_optab[op].ptype[2];
	if ((ACB1(acb) <= param1 && param1 & ACB1(acb)) &&
			(ACB2(acb) <= param2 && param2 & ACB2(acb)) &&
			(ACB3(acb) <= param3 && param3 & ACB3(acb)))
		return (1);
	else if ((op == 9 || op == 13) && (ACB1(acb) <= param1 && param1 & ACB1(acb))
			&& (ACB2(acb) <= param2 && param2 ^ ACB2(acb))
			&& (ACB3(acb) <= param3 && param3 & ACB3(acb)))
		return (1);
	else if (op == 10 && (ACB1(acb) <= param1 && param1 & ACB1(acb))
			&& (ACB2(acb) <= param2 && param2 & ACB2(acb))
			&& (ACB3(acb) <= param3 && param3 ^ ACB3(acb)))
		return (1);
	ft_printf("INVALID BITCH! op[%s]\n", g_optab[op].opstr);
	return (0);
}

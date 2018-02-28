/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reg_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 16:43:45 by anazar            #+#    #+#             */
/*   Updated: 2018/02/27 16:56:19 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>


void 	into_reg(unsigned int val, char *reg)
{
	reg[3] = val & 0xFF;
	reg[2] = (val >> 8) & 0xFF;
	reg[1] = (val >> 16) & 0xFF;
	reg[0] = (val >> 24) & 0xFF;
}

unsigned int	char_add(unsigned char c1, unsigned char c2)
{
	unsigned int	ret;

	ret = c1 + c2;
	return (ret);
}

int		reg_add(char *reg1, char *reg2, char *reg3)
{
	unsigned int	r1;
	unsigned int	r2;

	r1 = (reg1[3] & 0xFF) + ((reg1[2] & 0xFF) << 8) +
        ((reg1[1] & 0xFF) << 16) + ((reg1[0] & 0xFF) << 24);
	r2 = (reg2[3] & 0xFF) + ((reg2[2] & 0xFF) << 8) +
        ((reg2[1] & 0xFF) << 16) + ((reg2[0] & 0xFF) << 24);
	into_reg(r1 + r2, reg3);
	return (1);
}

unsigned int	char_sub(unsigned char c1, unsigned char c2)
{
	unsigned int	ret;

	ret = c1 - c2;
	return (ret);
}

int		reg_sub(char *reg1, char *reg2, char *reg3)
{
	unsigned int	r1;
	unsigned int	r2;

	r1 = (reg1[3] & 0xFF) + ((reg1[2] & 0xFF) << 8) +
        ((reg1[1] & 0xFF) << 16) + ((reg1[0] & 0xFF) << 24);
	r2 = (reg2[3] & 0xFF) + ((reg2[2] & 0xFF) << 8) +
        ((reg2[1] & 0xFF) << 16) + ((reg2[0] & 0xFF) << 24);
	into_reg(r1 - r2, reg3);
	return (1);
}

int		reg_xor(char *reg1, char *reg2, char *reg3)
{
	reg3[0] = reg1[0] ^ reg2[0];
	reg3[1] = reg1[1] ^ reg2[1];
	reg3[2] = reg1[2] ^ reg2[2];
	reg3[3] = reg1[3] ^ reg2[3];
	return (1);
}

int		reg_or(char *reg1, char *reg2, char *reg3)
{
	reg3[0] = reg1[0] | reg2[0];
	reg3[1] = reg1[1] | reg2[1];
	reg3[2] = reg1[2] | reg2[2];
	reg3[3] = reg1[3] | reg2[3];
	return (1);
}

int		reg_and(char *reg1, char *reg2, char *reg3)
{
	reg3[0] = reg1[0] & reg2[0];
	reg3[1] = reg1[1] & reg2[1];
	reg3[2] = reg1[2] & reg2[2];
	reg3[3] = reg1[3] & reg2[3];
	return (1);
}

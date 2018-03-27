/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reg_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 16:43:45 by anazar            #+#    #+#             */
/*   Updated: 2018/03/27 15:02:13 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int		reg_add(unsigned char *reg1, unsigned char *reg2, unsigned char *reg3)
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

int		reg_sub(unsigned char *reg1, unsigned char *reg2, unsigned char *reg3)
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

int		reg_xor(unsigned char *reg1, unsigned char *reg2, unsigned char *reg3)
{
	reg3[0] = reg1[0] ^ reg2[0];
	reg3[1] = reg1[1] ^ reg2[1];
	reg3[2] = reg1[2] ^ reg2[2];
	reg3[3] = reg1[3] ^ reg2[3];
	return (1);
}

int		reg_or(unsigned char *reg1, unsigned char *reg2, unsigned char *reg3)
{
	reg3[0] = reg1[0] | reg2[0];
	reg3[1] = reg1[1] | reg2[1];
	reg3[2] = reg1[2] | reg2[2];
	reg3[3] = reg1[3] | reg2[3];
	return (1);
}

int		reg_and(unsigned char *reg1, unsigned char *reg2, unsigned char *reg3)
{
	reg3[0] = reg1[0] & reg2[0];
	reg3[1] = reg1[1] & reg2[1];
	reg3[2] = reg1[2] & reg2[2];
	reg3[3] = reg1[3] & reg2[3];
	return (1);
}

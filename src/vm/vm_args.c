/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by anazar            #+#    #+#             */
/*   Updated: 2018/03/19 10:41:40 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include <corewar.h>

t_instr	init_instr(t_vm *vm, int i)
{
	t_instr	n;

	n.l1 = NULL;
	n.l2 = NULL;
	n.l3 = NULL;
	n.s = NULL;
	n.vm = vm;
	n.i = i;
	n.acb = vm->core[vm->info[i].start + vm->info[i].index + 1];
	n.opcode_pos = vm->info[i].index;
    n.reg_index[0] = 0;
    n.reg_index[1] = 0;
    n.reg_index[2] = 0;
    n.ri = 0;
	return (n);
}

int print_reg(unsigned char *l)
{
    return (VAL(l));
}

void copy_io(t_vm *vm, int dest, int src)
{
	ft_memcpy(&vm->info[dest], &vm->info[src], sizeof(t_io));
}

void reg_copy(unsigned char *dest, unsigned char *src)
{
	dest[0] = src[0];
	dest[1] = src[1];
	dest[2] = src[2];
	dest[3] = src[3];
}

int		indirect(t_vm *vm, int i, unsigned char opcode)
{
	//use % idx_mod
	//ld
	//st
	//ldi
	//sti ?
	//zjmp
	//fork
	if (opcode)
	//if (opcode == 0x2 || opcode == 0x3 ||
		//opcode == 0x9 || opcode == 0xA || opcode == 0xC)
		return ((vm->core[vm->info[i].start + vm->info[i].index] * 0x100 +
				vm->core[vm->info[i].start + vm->info[i].index + 1]) % IDX_MOD);
	else
		return (vm->core[vm->info[i].start + vm->info[i].index] * 0x100 +
				vm->core[vm->info[i].start + vm->info[i].index + 1]);
}

int get_offset(t_instr *instr, unsigned char acb, unsigned char **l)
{
	int	idx;

	*l = NULL;
	idx = ((acb & 0b100) != 0);
	acb = acb & 0b11;
	if (acb == 1)
	{
        //ft_printf("r");
		//*l = instr.vm->info[instr.i].regs[instr.vm->core[instr.vm->info[instr.i].start + instr.vm->info[instr.i].index]];
        //instr->reg_index[instr->ri] = instr->vm->core[instr->vm->info[instr->i].start + instr->opcode_pos];
        instr->reg_index[instr->ri] = instr->vm->core[instr->vm->info[instr->i].start + instr->vm->info[instr->i].index];
        if (instr->reg_index[instr->ri] >= REG_NUMBER || instr->reg_index[instr->ri] == 0)
            return (0);
        *l = instr->vm->info[instr->i].regs[instr->reg_index[instr->ri]];
        //ft_printf("%hhx ", instr.vm->core[instr.vm->info[instr.i].start + instr.vm->info[instr.i].index]);
		instr->vm->info[instr->i].index += 1;
        ++instr->ri;
	}
	else if (acb == 2)
	{
        //ft_printf("%%");
		*l = &instr->vm->core[instr->vm->info[instr->i].start + instr->vm->info[instr->i].index];
        //*l = &instr.vm->core[instr.vm->info[instr.i].start + instr.opcode_pos];
        //ft_printf("%d ", print_reg(*l));
		instr->vm->info[instr->i].index += 4;
	}
	else if (acb == 3)
	{
        *l = &instr->vm->core[instr->vm->info[instr->i].start + instr->opcode_pos + indirect(instr->vm, instr->i, idx)];
		//*l = &instr.vm->core[instr.vm->info[instr.i].start + instr.vm->info[instr.i].index +
		//indirect(instr.vm, instr.i, idx)]; //definitely need to change this - index changes, opcode offset won't be consistent
        //ft_printf("%hhd ", *l[0]);
        instr->vm->info[instr->i].index += 2;
	}
    return (1);
}

int get_offset_index(t_instr *instr, unsigned char acb, unsigned char **l)
{
	int	idx;

	*l = NULL;
	idx = ((acb & 0b100) != 0);
	acb = acb & 0b11;
    if (acb == 1)
    {
        //ft_printf("r");
        //*l = instr.vm->info[instr.i].regs[instr.vm->core[instr.vm->info[instr.i].start + instr.vm->info[instr.i].index]];
        //instr->reg_index[instr->ri] = instr->vm->core[instr->vm->info[instr->i].start + instr->opcode_pos];
        instr->reg_index[instr->ri] = instr->vm->core[instr->vm->info[instr->i].start + instr->vm->info[instr->i].index];
        if (instr->reg_index[instr->ri] >= REG_NUMBER || instr->reg_index[instr->ri] == 0)
        {
            return (0);
        }
        *l = instr->vm->info[instr->i].regs[instr->reg_index[instr->ri]];
        //ft_printf("%hhx ", instr.vm->core[instr.vm->info[instr.i].start + instr.vm->info[instr.i].index]);
        instr->vm->info[instr->i].index += 1;
        ++instr->ri;
    }
    else if (acb == 2)
    {
        //ft_printf("%%");
        *l = &instr->vm->core[instr->vm->info[instr->i].start + instr->vm->info[instr->i].index];
        //*l = &instr.vm->core[instr.vm->info[instr.i].start + instr.opcode_pos];
        //ft_printf("%d ", print_reg(*l));
        instr->vm->info[instr->i].index += 2;
    }
    else if (acb == 3)
    {
        *l = &instr->vm->core[instr->vm->info[instr->i].start + instr->opcode_pos + indirect(instr->vm, instr->i, idx)];
        //*l = &instr.vm->core[instr.vm->info[instr.i].start + instr.vm->info[instr.i].index +
        //indirect(instr.vm, instr.i, idx)]; //definitely need to change this - index changes, opcode offset won't be consistent
        //ft_printf("%hhd ", *l[0]);
        instr->vm->info[instr->i].index += 2;
    }
    return (1);
	/*if (acb == 1)
	{
        ft_printf("r");
		*l = instr.vm->info[instr.i].regs[instr.vm->core[instr.vm->info[instr.i].start + instr.vm->info[instr.i].index]];
        ft_printf("%hhx ", instr.vm->core[instr.vm->info[instr.i].start + instr.vm->info[instr.i].index]);
		instr.vm->info[instr.i].index += 1;
	}
	else if (acb == 2)
	{
        ft_printf("%%");
		*l = &instr.vm->core[instr.vm->info[instr.i].start + instr.vm->info[instr.i].index];
        ft_printf("%d ", print_reg(&instr.vm->core[instr.vm->info[instr.i].start + instr.vm->info[instr.i].index]));
		instr.vm->info[instr.i].index += 2;
	}
	else if (acb == 3)
	{
		*l = &instr.vm->core[instr.vm->info[instr.i].start + instr.opcode_pos + indirect(instr.vm, instr.i, idx)];
        ft_printf("%x%x ", instr.vm->core[instr.vm->info[instr.i].start + instr.vm->info[instr.i].index], instr.vm->core[instr.vm->info[instr.i].start + instr.vm->info[instr.i].index + 1]);
		instr.vm->info[instr.i].index += 2;
	}*/
}

int		get_index_one(unsigned char *l)
{
	return (VAL2(l) & 0xFFFF);
}

int		get_index_two(unsigned char *l1, unsigned char *l2)
{
	unsigned char l3[4];

	reg_add(l1, l2, l3);
	return (VAL2(l3));
}

void output(char *opname, t_instr instr)
{
    int i;

    i = 0;
    /*ft_printf("P    %d | %s ", instr.i + 1, opname);
    if (!ACB1(instr.acb))
        ;
    else if (ACB1(instr.acb) == 1)
        ft_printf("r%d ", instr.reg_index[i++]);
    else if (ACB1(instr.acb) == 2)
        ft_printf("%d ", print_reg(instr.l1));
    else
        ft_printf("%hhd ", instr.l1[0]);
    if (!ACB2(instr.acb))
        ;
    else if (ACB2(instr.acb) == 1)
        ft_printf("r%d ", instr.reg_index[i++]);
    else if (ACB2(instr.acb) == 2)
        ft_printf("%d ", print_reg(instr.l2));
    else
        ft_printf("%hhd ", instr.l2[0]);
    if (!ACB3(instr.acb))
        ;
    else if (ACB3(instr.acb) == 1)
        ft_printf("r%d ", instr.reg_index[i++]);
    else if (ACB3(instr.acb) == 2)
        ft_printf("%d ", print_reg(instr.l3));
    else
        ft_printf("%hhd ", instr.l3[0]);
    ft_printf("\n");*/
}

void output_index(char *opname, t_instr instr)
{
    int i;

    i = 0;
    /*ft_printf("P    %d | %s ", instr.i + 1, opname);
    if (!ACB1(instr.acb))
        ;
    else if (ACB1(instr.acb) == 1)
        ft_printf("r%d ", instr.reg_index[i++]);
    else if (ACB1(instr.acb) == 2)
        ft_printf("%d ", get_index_one(instr.l1));
    else
        ft_printf("%hhd ", instr.l1[0]);
    if (!ACB2(instr.acb))
        ;
    else if (ACB2(instr.acb) == 1)
        ft_printf("r%d ", instr.reg_index[i++]);
    else if (ACB2(instr.acb) == 2)
        ft_printf("%d ", get_index_one(instr.l2));
    else
        ft_printf("%hhd ", instr.l2[0]);
    if (!ACB3(instr.acb))
        ;
    else if (ACB3(instr.acb) == 1)
        ft_printf("r%d ", instr.reg_index[i++]);
    else if (ACB3(instr.acb) == 2)
        ft_printf("%d ", get_index_one(instr.l3));
    else
        ft_printf("%hhd ", instr.l3[0]);
    ft_printf("\n");*/
}

void	vm_live(t_vm *vm, int i)
{
    //ft_printf("P    %d | ", i + 1);
    vm->info[i].index += 1;
    //ft_printf("live %d", print_reg(&vm->core[vm->info[i].start + vm->info[i].index]));
    vm->info[i].index += 4;
	vm->info[i].live++;
	vm->info[i].alive = 1;
    //ft_printf("\n");
}
void	vm_zjmp(t_vm *vm, int i)
{
    t_instr instr;

    instr = init_instr(vm, i);
	instr.acb = 0;
    if (!vm->info[i].carry)
    {
        vm->info[i].index += 3;
        return ;
    }
    output("zjmp", instr);
    vm->info[i].index += get_index_one(&vm->core[vm->info[i].start + vm->info[i].index + 1]);
    vm->info[i].carry = 0;
}

void	vm_sti(t_vm *vm, int i)
{
    t_instr         instr;

    instr = init_instr(vm, i);
	vm->info[i].index += 2;
    if (ACB1(instr.acb) != 1)
        return ;
	if (!get_offset_index(&instr, ACB1(instr.acb), &instr.l1) ||
        !get_offset_index(&instr, ACB2(instr.acb), &instr.l2) ||
        !get_offset_index(&instr, ACB3(instr.acb), &instr.l3))
        return ;
	instr.index = ((VAL2(instr.l2) + VAL2(instr.l3)) & 0xFFFF) % IDX_MOD;
    output_index("sti", instr);
	reg_copy(&vm->core[vm->info[i].start + instr.opcode_pos + instr.index], instr.l1);
}
void	vm_lfork(t_vm *vm, int i)
{
    int             j;
    t_instr         instr;

    instr = init_instr(vm, i);
    instr.acb = 0;
    j = vm->process_count;
    while (vm->info[j].alive && vm->info[j].executing)
        ++j;
    vm->process_count++;
    if (!get_offset_index(&instr, 2, &instr.l1))
        return ;
    output("lfork", instr);
    copy_io(vm, j, i);
    vm->info[j].start = vm->info[i].start + vm->info[i].index + (instr.l1[1] << 8 | instr.l1[0]);
    vm->info[j].index = 0;
    vm->info[i].index += 3;
}
void	vm_fork(t_vm *vm, int i)
{
    int             j;
    t_instr         instr;

    instr = init_instr(vm, i);
    instr.acb = 0;
    j = vm->process_count;
    while (vm->info[j].alive && vm->info[j].executing)
        ++j;
    vm->process_count++;
    if (!get_offset_index(&instr, 2, &instr.l1))
        return ;
    output("fork", instr);
    copy_io(vm, j, i);
    vm->info[j].start = (vm->info[i].start + vm->info[i].index + (instr.l1[0] << 8 | instr.l1[1]) % IDX_MOD) % 4096;
    vm->info[j].index = 0;
    vm->info[i].index += 1;
    ft_printf("currently at: %d + %d %hhx\n", vm->info[i].start, vm->info[i].index, vm->core[vm->info[i].start + vm->info[i].index]);
}
void	vm_lld(t_vm *vm, int i)
{
    t_instr         instr;

    instr = init_instr(vm, i);
    vm->info[i].index += 2;
    //if (!valid_acb(instr.acb, 2, 1, 0) && !valid_acb(instr.acb, 3, 1, 0))
    if (!valid_acb(instr, 2, 1, 0) && !valid_acb(instr, 3, 1, 0))
        return ;
    if (!get_offset(&instr, ACB1(instr.acb), &instr.l1) ||
        !get_offset(&instr, ACB2(instr.acb), &instr.l2))
        return ;
    output("lld", instr);
    reg_copy(instr.l2, instr.l1);
	vm->info[i].carry = 1;
}
void	vm_lldi(t_vm *vm, int i)
{
    t_instr         instr;

    instr = init_instr(vm, i);
    vm->info[i].index += 2;
    if (ACB2(instr.acb) == 3 || ACB3(instr.acb) != 1)
        return ;
    if (!get_offset_index(&instr, ACB1(instr.acb), &instr.l1) ||
        !get_offset_index(&instr, ACB2(instr.acb), &instr.l2) ||
        !get_offset_index(&instr, ACB3(instr.acb), &instr.l3))
        return ;
    instr.s = &vm->core[(vm->info[i].start + vm->info[i].index + get_index_two(instr.l1, instr.l2)) % 4096];
    output_index("lldi", instr);
    reg_copy(instr.l3, instr.s);
    vm->info[i].carry = 1;
    ft_printf("\n");
}
void	vm_ldi(t_vm *vm, int i)
{
    t_instr         instr;

    instr = init_instr(vm, i);
    vm->info[i].index += 2;
    if (ACB2(instr.acb) == 3 || ACB3(instr.acb) != 1)
        return ;
    if (!get_offset_index(&instr, ACB1(instr.acb) | 0b100, &instr.l1) ||
        !get_offset_index(&instr, ACB2(instr.acb), &instr.l2) ||
        !get_offset_index(&instr, ACB3(instr.acb), &instr.l3))
        return ;
    instr.s = &vm->core[(vm->info[i].start + vm->info[i].index + get_index_two(instr.l1, instr.l2)) % 4096];
    output_index("ldi", instr);
    reg_copy(instr.l3, instr.s);
    vm->info[i].carry = 1;
}

void	vm_ld(t_vm *vm, int i)
{
    t_instr         instr;

    instr = init_instr(vm, i);
    vm->info[i].index += 2;
    if (!valid_acb(instr, 2, 1, 0) && !valid_acb(instr, 3, 1, 0))
        return ;
    if (!get_offset(&instr, ACB1(instr.acb) | 0b100, &instr.l1) ||
        !get_offset(&instr, ACB2(instr.acb), &instr.l2))
        return ;
    output("ld", instr);
    reg_copy(instr.l2, instr.l1);
	vm->info[i].carry = 1;
}
void	vm_st(t_vm *vm, int i)
{
    t_instr			instr;

    instr = init_instr(vm, i);
    vm->info[i].index += 2;
    if (!valid_acb(instr, 1, 1, 0) && !valid_acb(instr, 1, 3, 0))
        return ;
    if (!get_offset(&instr, ACB1(instr.acb), &instr.l1) ||
    !get_offset(&instr, ACB2(instr.acb) | 0b100, &instr.l2))
        return ;
    if (ACB2(instr.acb) == 1)
        instr.l2 = &vm->core[vm->info[i].start + instr.opcode_pos + VAL(instr.l2) % 4096];
    output("st", instr);
    reg_copy(instr.l2, instr.l1);
}
void	vm_sub(t_vm *vm, int i)
{
    t_instr			instr;

    instr = init_instr(vm, i);
    vm->info[i].index += 2;
    if (!valid_acb(instr, 1, 1, 1))
		return ;
	if (!get_offset(&instr, ACB1(instr.acb), &instr.l1) ||
        !get_offset(&instr, ACB2(instr.acb), &instr.l2) ||
        !get_offset(&instr, ACB3(instr.acb), &instr.l3))
        return ;
    output("sub", instr);
    reg_sub(instr.l1, instr.l2, instr.l3);
}
void	vm_add(t_vm *vm, int i)
{
    t_instr			instr;

    instr = init_instr(vm, i);
    vm->info[i].index += 2;
    if (!valid_acb(instr, 1, 1, 1))
		return ;
	if (!get_offset(&instr, ACB1(instr.acb), &instr.l1) ||
        !get_offset(&instr, ACB2(instr.acb), &instr.l2) ||
        !get_offset(&instr, ACB3(instr.acb), &instr.l3))
        return ;
    output("add", instr);
    reg_add(instr.l1, instr.l2, instr.l3);
}
void	vm_aff(t_vm *vm, int i)
{
    t_instr         instr;

    instr = init_instr(vm, i);
    vm->info[i].index += 1;
    if (!valid_acb(instr, 1, 0, 0))
		return ;
	if (!get_offset(&instr, ACB1(instr.acb), &instr.l1))
        return ;
    output("aff", instr);
    ft_printf("%c\n", instr.l1[3]);
}
void	vm_or(t_vm *vm, int i)
{
    t_instr			instr;

    instr = init_instr(vm, i);
    vm->info[i].index += 2;
    if (!valid_acb(instr, 1, 1, 1))
		return ;
	if (!get_offset(&instr, ACB1(instr.acb), &instr.l1) ||
        !get_offset(&instr, ACB2(instr.acb), &instr.l2) ||
        !get_offset(&instr, ACB3(instr.acb), &instr.l3))
        return ;
    output("or", instr);
    reg_or(instr.l1, instr.l2, instr.l3);
}
void	vm_xor(t_vm *vm, int i)
{
    t_instr			instr;

    instr = init_instr(vm, i);
    vm->info[i].index += 2;
    if (!valid_acb(instr, 1, 1, 1))
		return ;
	if (!get_offset(&instr, ACB1(instr.acb), &instr.l1) ||
        !get_offset(&instr, ACB2(instr.acb), &instr.l2) ||
        !get_offset(&instr, ACB3(instr.acb), &instr.l3))
        return ;
    output("xor", instr);
    reg_xor(instr.l1, instr.l2, instr.l3);
}
void	vm_and(t_vm *vm, int i)
{
    t_instr			instr;

    instr = init_instr(vm, i);
    vm->info[i].index += 2;
    if (!valid_acb(instr, 1, 1, 1))
		return ;
	if (!get_offset(&instr, ACB1(instr.acb), &instr.l1) ||
        !get_offset(&instr, ACB2(instr.acb), &instr.l2) ||
        !get_offset(&instr, ACB3(instr.acb), &instr.l3))
        return ;
    output("and", instr);
    reg_and(instr.l1, instr.l2, instr.l3);
}

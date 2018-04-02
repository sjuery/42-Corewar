/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/04/01 20:57:03 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	zero_flags(t_vm *vm)
{
	vm->f.d = 0;
	vm->f.n = 0;
	vm->f.g = 0;
	vm->f.b = 0;
	vm->f.v = 0;
	vm->f.flags = 1;
}

void	init_vm(t_vm *vm)
{
	int				i;
	int				x;
	int				fd;
	unsigned char	*reg;
	t_io			*proc;

	i = -1;
	x = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->q = init_queue();;
	ft_bzero(vm->core, MEM_SIZE);
	ft_bzero(vm->vis, MEM_SIZE);
	while (++i < vm->num_players)
	{
		proc = (t_io*)ft_memalloc(sizeof(t_io));
		proc->executing = 1;
		vm->process_count++;
		proc->head = &vm->head[i];
		//vm->info[i].head = &vm->head[i];
		fd = open(vm->players[i], O_RDONLY);
		write_info(vm, fd, &x, i);
		//write_info(vm, fd, &x, i);
		into_reg(i * (MEM_SIZE / vm->num_players), PC);
		//vm->info[i].start = i * (MEM_SIZE / vm->num_players);
		assign_player_num(proc, i, &reg);
		//assign_player_num(vm, i, &reg);
		enqueue(vm->q, proc, i);
		x += ((MEM_SIZE / vm->num_players) - proc->head->prog_size);
		//x += ((MEM_SIZE / vm->num_players) - vm->info[i].head->prog_size);
	}
	vm->win_player = vm->num_players;
}

void	write_info(t_vm *vm, int fd, int *x, int i)
{
	int		j;
	char	*body;

	body = ft_memalloc(sizeof(char) * CHAMP_MAX_SIZE + 1);
	//if (!read_input(fd, &vm->info[i], body))
	if (!read_input(fd, &vm->head[i], body))
		error();
	j = -1;
	//while (++j < (int)vm->info[i].head->prog_size)
	while (++j < (int)vm->head[i].prog_size)
	{
		vm->vis[*x].player = i + 1;
		vm->core[*x] = body[j];
		vm->vis[*x].byte = body[j];
		*x = *x + 1;
	}
	free(body);
}

void	init_players(int ac, char **av, t_vm *vm)
{
	int i;

	i = 0;
	zero_flags(vm);
	while (++i < ac)
		check_flags(vm, av, &i);
	i = 0;
	while (++i < ac)
		fill_champs(vm, av, &i);
}

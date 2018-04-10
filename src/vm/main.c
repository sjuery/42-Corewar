/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/04/05 19:10:36 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	countdown(void)
{
	ft_printf("\nCorewar will begin in...\n");
	system("say -v Mei-Jia Corewar will begin in 3");
	system("cat ./src/extra/3.txt");
	sleep(1);
	system("cat ./src/extra/2.txt");
	system("say -v Mei-Jia 2");
	sleep(1);
	system("cat ./src/extra/1.txt");
	system("say -v Mei-Jia 1");
	sleep(1);
	system("cat ./src/extra/go.txt");
	system("say -v Mei-Jia Go!");
	sleep(2);
}

void	introduce_players_v(t_vm *vm)
{
	int		i;
	char	*voice;

	i = 0;
	voice = ft_memalloc(sizeof(char));
	system("clear");
	system("cat ./src/extra/entrance.txt");
	system("say -v Mei-Jia Introducing the corewar contestants!");
	ft_printf("Introducing contestants...\n");
	voice = ft_strjoinfree(voice, ft_strdup("say -v Mei-Jia Player "));
	while (i < vm->num_players)
	{
		voice = ft_strjoinfree(voice, ft_strdup(vm->head[i].prog_name));
		voice = ft_strjoinfree(voice, ft_strdup(" weighing in at "));
		voice = ft_strjoinfree(voice, ft_itoa(vm->head[i].prog_size));
		voice = ft_strjoinfree(voice, ft_strdup(" bytes, their motto is "));
		voice = ft_strjoinfree(voice, ft_strdup(vm->head[i].comment));
		voice = ft_strjoinfree(voice, ft_strdup("."));
		ft_printf("* Player %i, weighing %i bytes, \"%s\" (\"%s\") !\n", i + 1,
			vm->head[i].prog_size, vm->head[i].prog_name, vm->head[i].comment);
		i++;
	}
	system(voice);
	free(voice);
	countdown();
}

void	introduce_players(t_vm *vm)
{
	int i;

	i = 0;
	system("clear");
	system("cat ./src/extra/entrance.txt");
	ft_printf("Introducing contestants...\n");
	while (i < vm->num_players)
	{
		ft_printf("* Player %i, weighing %i bytes, \"%s\" (\"%s\") !\n", i + 1,
			vm->head[i].prog_size, vm->head[i].prog_name, vm->head[i].comment);
		i++;
	}
}

int		main(int ac, char **av)
{
	t_vm			*vm;
	time_t			t;

	if (ac < 2)
		error();
	srand((unsigned)time(&t));
	vm = (t_vm *)ft_memalloc(sizeof(t_vm));
	init_players(ac, av, vm);
	init_vm(vm, -1, 0);
	if (vm->f.i == 1)
		introduce_players_v(vm);
	else
		introduce_players(vm);
	if (vm->f.g)
	{
		init_curses();
		keypad(stdscr, TRUE);
		nodelay(stdscr, TRUE);
		print_curses(vm, -1, 0, 0);
	}
	read_bytes(vm, 1, 1);
	free(vm);
	return (0);
}

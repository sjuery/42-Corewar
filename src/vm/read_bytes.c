/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bytes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:59:44 by mlu               #+#    #+#             */
/*   Updated: 2018/04/06 11:54:16 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "asm.h"

void	check_executing_processes(t_vm *vm, int *game_end)
{
	t_io *tmp;

	if (!isEmpty(vm->q) && vm->cycle_to_die >= 0)
		*game_end = 0;
	else
	{
		while (!isEmpty(vm->q))
		{
			tmp = dequeue(vm->q);
			free(tmp);
		}
	}
}

void	add_acb_bytes(int op, int *acb_val, int acb)
{
	if (acb == 1)
		*acb_val += REG_CODE;
	else if (acb == 2)
		*acb_val += (g_optab[op].index ? DIR_CODE : DIR_SIZE);
	else if (acb == 3)
		*acb_val += IND_SIZE;
}

void	update_pc(t_io *proc, int op, int acb)
{
	int acb_val;

	acb_val = 2;
	add_acb_bytes(op, &acb_val, ACB1(acb));
	if (g_optab[op].params >= 2)
		add_acb_bytes(op, &acb_val, ACB2(acb));
	if (g_optab[op].params == 3)
		add_acb_bytes(op, &acb_val, ACB3(acb));
	if (acb_val == 0)
		acb_val = 1;
	into_reg(VAL(PC) + acb_val, PC);
}

void	cycle_scheduler(t_vm *vm, int *counter)
{
	if (*counter == 0)
	{
		vm->checks++;
		if (vm->live >= NBR_LIVE)
		{
			vm->checks = 0;
			vm->cycle_to_die -= CYCLE_DELTA;
		}
		vm->live = 0;
		reset_alive_all(vm);
	}
	*counter = (*counter + 1) % vm->cycle_to_die;
	if (vm->checks == MAX_CHECKS)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		vm->checks = 0;
	}
}

void	set_cycle_to_execute(t_vm *vm, t_io *proc)
{
	if (proc->op >= 1 && proc->op <= 16)
		proc->cycle_to_execute = g_optab[proc->op - 1].cycles + vm->cycles;
	else
		proc->cycle_to_execute = vm->cycles + 1;
}

void	process_update(t_vm *vm)
{
	int		op;
	int		previous_index;
	t_io	*proc;
	t_node	**node;

	node = &(vm->q->max_p);
	while (*node && (*node)->data->cycle_to_execute <= vm->cycles)
	{
		proc = dequeue(vm->q);
		if (PARAM1 >= MEM_SIZE)
			into_reg(PARAM1 % MEM_SIZE, PC);
		op = proc->op;
		if ((op > 0 && op < 17) && proc->cycle_to_execute == vm->cycles &&
				((g_optab[op - 1].acb &&
				  valid_acb(op - 1, vm->core[PARAM2M], vm, proc)) ||
				 !g_optab[op - 1].acb) && proc->executing)
		{
			//ft_printf("AFTER DEQUEUE\n");
			//print_queue(vm->q);
			//ft_printf("cycle[%i], op[%i] %s process[%i] pc[%i]\n", vm->cycles, op, g_optab[op - 1].opstr, proc->process + 1, PARAM1);
			previous_index = PARAM1M;
			g_jt[op - 1](vm, proc);
			vm->vis[PARAM1M].previous_index = previous_index;
			proc->op = vm->core[PARAM1M];
			set_cycle_to_execute(vm, proc);
			enqueue(vm->q, proc, proc->executing * proc->cycle_to_execute);
			//ft_printf("AFTER ENQUE\n");
			//print_queue(vm->q);
			vis_unhighlight_process(vm, proc);
			vis_highlight_process(vm, proc);
		}
		else if (op > 0 && op < 17 && proc->cycle_to_execute == vm->cycles && proc->executing)
		{
			//ft_printf("INVALID; op[%i] cycle[%i] pc[%i]\n", op, vm->cycles, PARAM1);
			previous_index = PARAM1M;
			update_pc(proc, op - 1, vm->core[PARAM2M]);
			vm->vis[PARAM1M].previous_index = previous_index;
			proc->op = vm->core[PARAM1M];
			set_cycle_to_execute(vm, proc);
			enqueue(vm->q, proc, proc->executing * proc->cycle_to_execute);
			vis_unhighlight_process(vm, proc);
			vis_highlight_process(vm, proc);
		}
		else if (proc->cycle_to_execute == vm->cycles && proc->executing)
		{
			//ft_printf("INVALID OPCODE [%i] process[%i] pc[%i]\n", op, proc->process + 1, PARAM1);
			vm->vis[PARAM2M].previous_index = PARAM1M;
			into_reg(VAL(PC) + 1, PC);
			proc->op = vm->core[PARAM1M];
			set_cycle_to_execute(vm, proc);
			enqueue(vm->q, proc, proc->executing * proc->cycle_to_execute);
			vis_unhighlight_process(vm, proc);
			vis_highlight_process(vm, proc);
		}
		else if (!proc->executing)
		{
			attron(COLOR_PAIR(vm->vis[PARAM1M].player));
			mvprintw((PARAM1M) / 64 + 1, ((PARAM1M) * 3) % VWRAP, "%02hhx",
						vm->vis[PARAM1M].byte);
			attroff(COLOR_PAIR(vm->vis[PARAM1M].player));
			vm->process_count--;
			free(proc);
			if (vm->f.noise == 0 && (vm->f.s >= 2))
			{
				system("afplay ./sound/death.mp3 &");
				vm->f.noise++;
			}
			//ft_printf("DEAD PROCESS\n");
			//ft_printf("process count %i proc->num %i\n", vm->process_count, proc->process);
		}
	}
}

void	read_bytes(t_vm *vm, int game_end, int counter)
{
	int c;

	if (vm->f.r == 1 && vm->f.g == 1)
		system("afplay ./sound/star.mp3 &");
	while (1)
	{
		process_update(vm);
		if (vm->f.g)
		{
			vis_print_debug(vm);
			refresh();
			if (((c = getch()) != ERR) && vm->f.r != 1)
			{
				if (c == 'q' && (vm->f.delay - 10000) >= 0)
					vm->f.delay -= 10000;
				if (c == 'r' && (vm->f.delay + 10000) <= 1000000)
					vm->f.delay += 10000;
				if (c == 'w' && (vm->f.delay - 1000) >= 0)
					vm->f.delay -= 1000;
				if (c == 'e' && (vm->f.delay + 10000) <= 1000000)
					vm->f.delay += 1000;
				if (c == 27)
				{
					endwin();
					exit(0);
				}
			}
			usleep(vm->f.delay);
		}
		if (vm->f.d && vm->f.d == vm->cycles)
			print_core(vm->core, -1);
		cycle_scheduler(vm, &counter);
		check_executing_processes(vm, &game_end);
		vm->cycles++;
		if (game_end)
			break ;
		//ft_putnbr(vm->cycles);
		//ft_putchar('\n');
		game_end = 1;
		vm->f.noise = 0;
	}
	endwin();
	free(vm->vis);
	free(vm->core);
	free(vm->q);
	ft_printf("\nContestant %i, \"%s\", has won ! CTD[%i] cycle[%i] process_count[%i]\n", vm->win_player,
		vm->head[vm->win_player - 1].prog_name, vm->cycle_to_die, vm->cycles, vm->process_count);
}

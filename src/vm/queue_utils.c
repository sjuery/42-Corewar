/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 13:29:06 by anazar            #+#    #+#             */
/*   Updated: 2018/04/04 21:52:32 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void print_proc(t_io *proc)
{
    ft_printf("[proc: %d op: %d CTE: %d]| -> ", 
    	proc->process + 1, proc->op, proc->cycle_to_execute);
}

void print_queue(t_queue *queue)
{
    t_node  *tmp;

    tmp = queue->max_p;
    while (tmp) {
		ft_printf("priority[%i] ", tmp->priority);
        print_proc(tmp->data);
        tmp = tmp->next;
    }
	ft_printf("\n");
}

t_io			*peek(t_queue *queue)
{
	if (!queue->max_p)
		return (NULL);
	return (queue->max_p->data);
}

int				isEmpty(t_queue *queue)
{
	return (!queue->max_p && !queue->min_p);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 13:29:06 by anazar            #+#    #+#             */
/*   Updated: 2018/04/04 21:52:32 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		queue_process(t_queue *queue, t_node *new, t_io *num, int priority)
{
	t_node *tmp;

	if (PRIORITY(priority, QMIN) || (priority == QMIN &&
			num->process < queue->min_p->data->process))
	{
		queue->min_p->next = new;
		queue->min_p = queue->min_p->next;
	}
	else if (PRIORITY(QMAX, priority) || (priority == QMAX &&
			num->process > queue->max_p->data->process))
	{
		new->next = queue->max_p;
		queue->max_p = new;
	}
	else
	{
		tmp = queue->max_p;
		while (tmp->next && (PRIORITY(priority, QTMP) ||
			(priority == QTMP && num->process < tmp->next->data->process)))
			tmp = tmp->next;
		new->next = tmp->next;
		tmp->next = new;
	}
}

void		enqueue(t_queue *queue, t_io *num, int priority)
{
	t_node	*new;

	new = init_node(num, priority);
	if (!queue->max_p)
		queue->max_p = new;
	if (!queue->min_p)
		queue->min_p = new;
	else
		queue_process(queue, new, num, priority);
}

t_io		*dequeue(t_queue *queue)
{
	t_node		*tmp;
	t_io		*tmp_num;

	if (!queue->max_p)
		return (NULL);
	tmp = queue->max_p;
	tmp_num = queue->max_p->data;
	queue->max_p = queue->max_p->next;
	if (!queue->max_p)
		queue->min_p = NULL;
	free(tmp);
	tmp = NULL;
	return (tmp_num);
}

t_queue		*init_queue(void)
{
	t_queue	*new;

	new = (t_queue *)malloc(sizeof(t_queue));
	new->max_p = NULL;
	new->min_p = NULL;
	return (new);
}

t_node		*init_node(t_io *data, int priority)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	new->data = data;
	new->priority = priority;
	new->next = NULL;
	return (new);
}

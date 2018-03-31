/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <anazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 13:29:06 by anazar            #+#    #+#             */
/*   Updated: 2018/03/31 13:32:42 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

t_queue     *init_queue(void)
{
	t_queue	*new;

	new = (t_queue *)malloc(sizeof(t_queue));
	new->max_p = NULL;
	new->min_p = NULL;
	return (new);
}

t_node      *init_node(t_data *data, int priority)
{
    t_node  *new;

    new = (t_node *)malloc(sizeof(t_node));
    new->data = data;
    new->priority = priority;
    new->next = NULL;
    return (new);
}

void			enqueue(t_queue *queue, t_data *num, int priority)
{
	t_node	*new;
    t_node  *tmp;

    new = init_node(num, priority);
	if (!queue->max_p)
		queue->max_p = new;
	if (!queue->min_p)
		queue->min_p = new;
	else
	{
        if (!PRIORITY(queue->min_p->priority, priority))
        {
            queue->min_p->next = new;
    		queue->min_p = queue->min_p->next;
        }
        else if (PRIORITY(queue->max_p->priority, priority))
        {
            new->next = queue->max_p;
    		queue->max_p = new;
        }
        else
        {
            tmp = queue->max_p;
            while (tmp && !PRIORITY(tmp->priority, priority))
                tmp = tmp->next;
            new->next = tmp;
            tmp->next = new;
        }
	}
}

t_data			*dequeue(t_queue *queue)
{
	t_node	*tmp;
	t_data			*tmp_num;

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

t_data			*peek(t_queue *queue)
{
	if (!queue->max_p)
		return (NULL);
	return (queue->max_p->data);
}

int				isEmpty(t_queue *queue)
{
	return (!queue->max_p && !queue->min_p);
}

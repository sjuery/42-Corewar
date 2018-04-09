/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_label.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <ihodge@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 18:03:50 by ihodge            #+#    #+#             */
/*   Updated: 2018/04/09 12:50:05 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdio.h>

void		save_labels(t_label **labels, char *name, int offset)
{
	t_label	*head;

	head = (*labels);
	if (head)
	{
		while (head->next)
			head = head->next;
		head->next = (t_label*)ft_memalloc(sizeof(t_label));
		head->next->name = name;
		head->next->offset = offset;
		head->next->next = NULL;
	}
	else
	{
		(*labels) = (t_label*)ft_memalloc(sizeof(t_label));
		(*labels)->name = name;
		(*labels)->offset = offset;
		(*labels)->next = NULL;
	}
}

t_label_ref	*save_label_refs(t_label_ref **label_ref)
{
	t_label_ref	*head;

	head = (*label_ref);
	if (head)
	{
		while (head->next)
			head = head->next;
		head->next = (t_label_ref*)ft_memalloc(sizeof(t_label_ref));
		head->next->next = NULL;
		return (head->next);
	}
	else
	{
		(*label_ref) = (t_label_ref*)ft_memalloc(sizeof(t_label_ref));
		(*label_ref)->next = NULL;
		return ((*label_ref));
	}
	return (head);
}

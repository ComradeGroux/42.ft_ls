/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:27:17 by vgroux            #+#    #+#             */
/*   Updated: 2024/02/15 14:17:50 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sortList(t_list **head, int flag)
{
	*head = sortAlpha(*head);
	if (flag & FLAG_t)
		sortTime(head);
	if (flag & FLAG_r)
		sortReverse(head);
}

void	sortTime(t_list **head)
{
	(void)head;
}

t_list*	swap(t_list* n1, t_list* n2)
{
	n1->next = n2->next;
	n2->next = n1;
	return n2;
}

t_list*	sortAlpha(t_list *head)
{
	if (!head)
		return NULL;
	if (head->next && ft_strcmp(((struct dirent*)head->content)->d_name, ((struct dirent*)head->next->content)->d_name) > 0)
		head = swap(head, head->next);
	head->next = sortAlpha(head->next);
	if (head->next && ft_strcmp(((struct dirent*)head->content)->d_name, ((struct dirent*)head->next->content)->d_name) > 0)
	{
		head = swap(head, head->next);
		head->next = sortAlpha(head->next);
	}
	return (head);
}

void	sortReverse(t_list **head)
{
	t_list	*newList = *head;
	*head = (*head)->next;
	newList->next = NULL;

	t_list*	tmp = NULL;
	while (*head != NULL)
	{
		tmp = (*head)->next;
		ft_lstadd_front(&newList, *head);
		*head = tmp;
	}
	*head = newList;
}

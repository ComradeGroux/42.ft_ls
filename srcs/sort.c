/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:27:17 by vgroux            #+#    #+#             */
/*   Updated: 2024/02/14 13:31:58 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sortTime(t_list **head)
{
	(void)head;
}

void	sortAlpha(t_list **head)
{
	(void)head;
	// t_list	**newList = NULL;
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

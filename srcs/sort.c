/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:27:17 by vgroux            #+#    #+#             */
/*   Updated: 2025/03/17 13:09:56 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sortList(t_list **head, int flag)
{
	*head = sortAlpha(*head);
	if (flag & FLAG_t)
		*head = sortTime(*head);
	if (flag & FLAG_r)
		sortReverse(head);
}

t_list*	sortTime(t_list *head)
{
	struct stat statCurr;
	struct stat statNext;
	if (!head)
		return NULL;
	if (stat(((struct dirent*)head->content)->d_name, &statCurr) != 0)
		return NULL;
	if (head->next == NULL)
		return head;
	if (stat(((struct dirent*)head->next->content)->d_name, &statNext) != 0)
		return NULL;

	time_t	timeCurr = statCurr.st_mtime;
	time_t	timeNext = statNext.st_mtime;

	if (head->next && timeNext > timeCurr)
		head = swap(head, head->next);
	head->next = sortTime(head->next);

	if (stat(((struct dirent*)head->content)->d_name, &statCurr) != 0)
		return NULL;
	if (head->next && stat(((struct dirent*)head->next->content)->d_name, &statNext) != 0)
		return NULL;
	timeCurr = statCurr.st_mtime;
	timeNext = statNext.st_mtime;
	if (head->next && timeNext > timeCurr)
	{
		head = swap(head, head->next);
		head->next = sortTime(head->next);
	}
	return (head);
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
	else if (!((struct dirent*)head->content)->d_name)
		return NULL;

	if (!head->next)
		return head;
	else if (!((struct dirent*)head->content)->d_name)
		return head;

	if (ft_strcmp_uncase(((struct dirent*)head->content)->d_name, ((struct dirent*)head->next->content)->d_name) > 0)
		head = swap(head, head->next);
	head->next = sortAlpha(head->next);

	if (ft_strcmp_uncase(((struct dirent*)head->content)->d_name, ((struct dirent*)head->next->content)->d_name) > 0)
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

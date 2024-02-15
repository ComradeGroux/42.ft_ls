/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_rm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:30:46 by vgroux            #+#    #+#             */
/*   Updated: 2024/02/15 10:58:36 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_rm(t_list **head, t_list *toRm)
{
	t_list	*next;

	if (head && *head && toRm)
	{
		if (*head == toRm)
		{
			next = (*head)->next;
			ft_lstdelone(head, NULL);
			*head = next;
		}
		else
			ft_lst_rm(&((*head)->next), toRm);
	}
}

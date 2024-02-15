/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_rm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:30:46 by vgroux            #+#    #+#             */
/*   Updated: 2024/02/15 10:54:41 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_rm(t_list **head, t_list *toRm)
{
	t_list	*old = NULL;
	t_list	*curr = *head;
	while (curr != NULL)
	{
		if (curr == toRm)
		{
			if (old != NULL)
			{
				old->next = curr->next;
				free(curr);
				curr = old->next;
			}
			else
			{
				
			}
		}
		else
		{
			old = curr;
			curr = curr->next;
		}
	}
}

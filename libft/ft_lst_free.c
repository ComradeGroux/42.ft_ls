/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:41:13 by vgroux            #+#    #+#             */
/*   Updated: 2024/02/15 15:55:46 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_free(t_list **head)
{
	t_list	*tmp;

	if (*head)
	{
		while (*head)
		{
			tmp = (*head)->next;
			free((*head)->path);
			free(*head);
			*head = tmp;
		}
	}

}
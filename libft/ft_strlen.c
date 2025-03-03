/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:20:27 by vgroux            #+#    #+#             */
/*   Updated: 2022/10/10 14:31:57 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	if (!s)
		return 0;

	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

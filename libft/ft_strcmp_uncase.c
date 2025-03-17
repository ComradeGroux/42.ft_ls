/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_uncase.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:57:03 by vgroux            #+#    #+#             */
/*   Updated: 2025/03/17 13:12:06 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strcmp_uncase(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (s1 == s2 ? 0 : (s1 ? 1 : -1));
		
	size_t	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && ft_tolower(s1[i]) == ft_tolower(s2[i]))
		i++;
	return (ft_tolower((unsigned char)s1[i]) - ft_tolower((unsigned char)s2[i]));
}

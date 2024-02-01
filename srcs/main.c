/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 09:05:28 by vgroux            #+#    #+#             */
/*   Updated: 2024/02/01 09:16:08 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int argc, char** argv)
{
	(void)argv;
	if (argc >= 2)
	{

	}
	else
		ft_error("./ft_ls [OPTION]... [FILE]...\n[OPTION] are: \n-a\tdo not ignore entries starting with .\n-l\tuse a long listing format\n-r\treverse order while sorting\n-R\tlist subdirectories recursively\n-t\tsort by time, newest first");
	return (0);
}

void	ft_error(char* str)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(str, 2);
}
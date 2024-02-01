/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 09:05:28 by vgroux            #+#    #+#             */
/*   Updated: 2024/02/01 10:21:28 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int argc, char** argv)
{
	int	flag = init(argc, argv);
	printf("flag is %d\n", flag);
	if (flag != -1)
	{
		if ((flag & FLAG_R) != 0) // if '-R' is active, ls must be subdirectories recursive
			ls_recur(flag);
		else
			ls(flag);
	}
	else
		ft_error("An error occured during the init");
	return (0);
}

void	ls(int flag)
{
	(void)flag;
	ft_printf("ls classique\n");
}

void	ls_recur(int flag)
{
	(void)flag;
	ft_printf("ls recursif\n");
}

/**
 * 	ls "-a" "-l"			OK
 * 	ls -al					OK
 * 	ls -aaaaaaaaaaa -l		OK
 * 	ls " -a"				failed
 * 	ls "-a -l"				failed
 * 	ls "-a" -l "headers/"	OK
 * 	ls "-a" -l "headers/ "	failed
 * 	ls headers/ -a			OK
 * 	ls headers/ -a srcs/ -l	OK
 */ 
int	init(int argc, char** argv)
{
	int	flag = 0;

	if (argc == 1)
		return (0);
	else
	{
		int	j;
		int	i = 1;

		while (argv[i])
		{
			if (argv[i][0] != '-')
			{
				i++;
				continue;
			}
			else
			{
				j = 1;
				while (argv[i][j])
				{
					char	c = argv[i][j];
					
					switch (c)
					{
						case 'a':
							flag = flag | FLAG_a;
							break;
						case 'l':
							flag = flag | FLAG_l;
							break;
						case 'R':
							flag = flag | FLAG_R;
							break;
						case 'r':
							flag = flag | FLAG_r;
							break;
						case 't':
							flag = flag | FLAG_t;
							break;
						default:
							return (-1);
							break;
					}
					j++;
				}
			}
			i++;
		}
	}
	return (flag);
}

void	ft_error(char* str)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(str, 2);
	ft_putstr_fd("Usage: ", 2);
	ft_putendl_fd(MAN_LS, 2);
}
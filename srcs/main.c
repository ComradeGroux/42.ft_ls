/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 09:05:28 by vgroux            #+#    #+#             */
/*   Updated: 2024/02/01 14:59:57 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int argc, char** argv)
{
	int	flag = init(argc, argv);

	if (flag >= 0)
	{
		if(argc == 1)
		{
			char*	tmp[] = { ".", ".", NULL};
			ls(tmp, flag);
		}
		else if ((flag & FLAG_R) != 0) // if '-R' is active, ls must be subdirectories recursive
			ls_recur("", flag);
		else
			ls(argv, flag);
	}
	else
		switch (flag)
		{
			case -1:
				ft_error("Flag doesn't exist");
				break;
			case -2:
				ft_error("Directory doesn't exist");
				break;
			default:
				ft_error("Default error");
				break;
		}
	return (0);
}

void	printVal(struct dirent* currDir, int flag)
{
	if (flag & FLAG_a)
	{
		ft_printf("%s  ", currDir->d_name);
	}
	else if (currDir->d_name[0] != '.')
	{
		ft_printf("%s  ", currDir->d_name);
	}
}

void	ls(char** argv, int flag)
{
	int	i = 1;


	while (argv[i])
	{
		if (argv[i][0] != '-')
		{
			DIR*	fd_dir = opendir(argv[i]);

			if (fd_dir == NULL)
				return (perror(strerror(errno)));

			struct dirent*	currDir = readdir(fd_dir);
			while (currDir != NULL)
			{
				if (currDir->d_name[0] != '-')
					printVal(currDir, flag);
				currDir = readdir(fd_dir);
			}
		}
		i++;
	}
}

void	ls_recur(char* path, int flag)
{
	(void)flag;
	(void)path;
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
				// int		x = 0;
				// char*	str = argv[i];

				// while (str[x] && !ft_isspace(str[x]))
				// 	x++;
				// if (str[x] != '\0')
				// 	return (-2);
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
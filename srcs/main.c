/* ************************************************************************** */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 09:05:28 by vgroux            #+#    #+#             */
/*   Updated: 2024/02/21 16:25:17 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void printFlag(int flag)
{
	if (flag & FLAG_R)
		ft_printf("R");
	if (flag & FLAG_a)
		ft_printf("a");
	if (flag & FLAG_l)
		ft_printf("l");
	if (flag & FLAG_r)
		ft_printf("r");
	if (flag & FLAG_t)
		ft_printf("t");
	if (flag & FLAG_MULTI)
		ft_printf("\nls on multiple files/directories");
}

int	main(int argc, char** argv, char** envp)
{
	int	flag = init(argc, argv);
	if (flag < 0)
	{
		switch (flag)
		{
			case -1:
				ft_error("Flag doesn't exist");
				break;
			default:
				ft_error("Default error");
				break;
		}
	}

	int i = 1;
	bool hasTarget = false;
	while (argv[i])
	{
		if (argv[i][0] != '-')
		{
			hasTarget = true;
			break;
		}
		i++;
	}

	if (hasTarget == false)
	{
		char*	tmp[] = { ".", ".", NULL};
		ls(tmp, flag, envp);
	}
	else
		ls(argv, flag, envp);

	return (0);
}

void getEntries(char *argv, char** envp, t_list **head)
{
	(void)envp;
	DIR* fd_dir = opendir(argv);

	if (fd_dir == NULL)
	{
		ft_printf("ft_ls: cannot access '%s': %s", argv, strerror(errno));
		return;
	}
	
	struct dirent*	currDir;
	while ((currDir = readdir(fd_dir)))
	{
		char*	path = argv;
		path = ft_strjoin(path, "/");
		ft_lstadd_back(head, ft_lstnew(currDir, path));
	}

	closedir(fd_dir);
}

void	ls(char** argv, int flag, char** envp)
{
	int			i = 1;
	t_list*	head = NULL;

	while (argv[i])
	{
		if (argv[i][0] != '-')
		{
			getEntries(argv[i], envp, &head);
			sortList(&head, flag);
			printList(&head, flag, false);
			ft_lst_free(&head);
		}
		i++;
	}

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
	int		flag = 0;
	bool	multi = false;

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
				if (multi)
					flag = flag | FLAG_MULTI;
				i++;
				multi = true;
				continue;
			}
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
	exit(1);
}

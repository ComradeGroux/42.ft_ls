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

	if (flag >= 0)
	{
		if (argc == 1)
		{
			char*	tmp[] = { ".", ".", NULL};
			ls(tmp, flag, envp);
		}
		else if (flag & FLAG_R) // if '-R' is active, ls must be subdirectories recursive
			ls_recur(argv, flag, envp);
		else
			ls(argv, flag, envp);
	}
	else
	{
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
	}
	return (0);
}

void	ls(char** argv, int flag, char** envp)
{
	int		i = 1;
	bool	already_printed = false;
	t_list*	head = NULL;

	while (argv[i])
	{
		already_printed = false;
		if (argv[i][0] != '-')
		{
			DIR*	fd_dir = opendir(argv[i]);
			if (fd_dir == NULL)
			{
				ft_printf("ft_ls: cannot access '%s': %s", argv[i], strerror(errno));
				i++;
				continue;
			}
			struct dirent*	currDir;
			while ((currDir = readdir(fd_dir)))
			{
				char*	path = argv[i];
				path = ft_strjoin(path, "/");
				ft_lstadd_back(&head, ft_lstnew(currDir, path));
			}
			
			if (flag & FLAG_MULTI && i != 1)
				ft_printf("\n%s:\n", argv[i]);
			else if (flag & FLAG_MULTI)
				ft_printf("%s:\n", argv[i]);
			sortList(&head, flag);
			printList(&head, flag, &already_printed);
			
			closedir(fd_dir);
			ft_lst_free(&head);
		}
		i++;
	}
	if (!already_printed)
	{
		char*	tmp[] = { ".", ".", NULL};
		ls(tmp, flag, envp);
	}
}

void	ls_recur(char** argv, int flag, char** envp)
{
	int		i = 1;
	bool	already_printed = false;
	t_list*	head = NULL;

	while (argv[i])
	{
		already_printed = false;
		if (argv[i][0] != '-')
		{
			DIR*	fd_dir = opendir(argv[i]);
			if (fd_dir == NULL)
			{
				ft_printf("ft_ls: cannot access '%s': %s\n", argv[i], strerror(errno));
				i++;
				continue;
			}
			struct dirent*	currDir;
			while ((currDir = readdir(fd_dir)))
			{
				struct stat currStat;
				char*	path = argv[i];
				path = ft_strjoin(path, "/");
				path = ft_strjoin(path, currDir->d_name);
				if (stat(path, &currStat) != 0)
				{
					ft_printf("ft_ls: stat() error on '%s'\n", path);
					i++;
					continue;
				}
				if (S_ISDIR(currStat.st_mode))
				{
					if (flag & FLAG_a && ft_strcmp(currDir->d_name, ".") && ft_strcmp(currDir->d_name, ".."))
					{
						char*	tmp[] = {".", path, NULL};
						if (already_printed)
							ft_printf("\n%s:\n", path);
						else
							ft_printf("%s:\n", path);
						already_printed = true;
						ls_recur(tmp, flag, envp);
					}
					else if (ft_strncmp(currDir->d_name, ".", 1) != 0 && ft_strncmp(currDir->d_name, "..", 2) != 0)
					{
						char*	tmp[] = {".", path, NULL};
						if (already_printed)
							ft_printf("\n%s:\n", path);
						else
							ft_printf("%s:\n", path);
						already_printed = true;
						ls_recur(tmp, flag, envp);
					}
				}
				ft_lstadd_back(&head, ft_lstnew(currDir, path));
			}

			sortList(&head, flag);
			printList(&head, flag, &already_printed);
			closedir(fd_dir);
			ft_lst_free(&head);
		}
		i++;
	}
	if (!already_printed)
	{
		char*	tmp[] = { ".", ".", NULL};
		ls_recur(tmp, flag, envp);
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
}

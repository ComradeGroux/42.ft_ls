/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 09:05:28 by vgroux            #+#    #+#             */
/*   Updated: 2024/02/12 17:40:35 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

int	main(int argc, char** argv, char** envp)
{
	int	flag = init(argc, argv);

	if (flag >= 0)
	{
		if(argc == 1)
		{
			char*	tmp[] = { ".", ".", NULL};
			ls(tmp, flag, envp);
		}
		else if ((flag & FLAG_R) != 0) // if '-R' is active, ls must be subdirectories recursive
			ls_recur("", flag, envp);
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

bool	printVal(struct dirent* currDir, int flag)
{
	if (flag & FLAG_a)
	{
		ft_printf("%s", currDir->d_name);
		return true;
	}
	else if (currDir->d_name[0] != '.')
	{
		ft_printf("%s", currDir->d_name);
		return true;
	}
	return false;
}

void	ls(char** argv, int flag, char** envp)
{
	(void)envp;

	int		i = 1;
	bool	already_printed = false;

	while (argv[i])
	{
		t_list*	head = NULL;
		
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
			if (flag & FLAG_MULTI && i != 1)
				ft_printf("\n%s:\n", argv[i]);
			else if (flag & FLAG_MULTI)
				ft_printf("%s:\n", argv[i]);

			struct dirent*	currDir;
			while ((currDir = readdir(fd_dir)))
				ft_lstadd_back(&head, ft_lstnew(currDir));
		}
		if (flag & FLAG_t)
			sortTime(&head);
		else
			sortAlpha(&head);
		if (flag & FLAG_r)
			sortReverse(&head);
		printList(&head, flag, &already_printed);
		ft_printf("\n");
		i++;
	}
	if (!already_printed)
	{
		char*	tmp[] = { ".", ".", NULL};
		ls(tmp, flag, envp);
	}
}

void	ls_recur(char* path, int flag, char** envp)
{
	(void)flag;
	(void)path;
	(void)envp;
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

void	printList(t_list **head, int flag, bool* already_printed)
{
	t_list*	curr = *head;
	while (curr->next != NULL)
	{
		if ((already_printed) && (curr->content->d_name[0] != '.' || flag & FLAG_a))
			ft_printf("  ");
		if (printVal(curr->content, flag))
			*already_printed = true;
	}
}

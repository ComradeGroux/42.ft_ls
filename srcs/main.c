/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:25:17 by vgroux            #+#    #+#             */
/*   Updated: 2025/05/09 20:30:28 by vgroux           ###   ########.fr       */
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

	int i = 0;
	bool hasTarget = false;
	while (argv[++i])
	{
		if (argv[i][0] != '-')
		{
			hasTarget = true;
			break;
		}
	}

	bool already_printed = false;
	if (hasTarget)
		ls(argv, flag, envp, &already_printed);
	else
	{
		char*	tmp[] = { ".", ".", NULL};
		ls(tmp, flag, envp, &already_printed);
	}

	return (0);
}

void getEntries(char *argv, char** envp, t_list **head)
{
	(void)envp;
	DIR* fd_dir = opendir(argv);

	if (fd_dir == NULL)
	{
		ft_printf("ft_ls: cannot access '%s': %s\n", argv, strerror(errno));
		return;
	}
	
	struct dirent*	currDir;
	while ((currDir = readdir(fd_dir)))
	{
		char*	path = argv;
		if (path[ft_strlen(path) - 1] != '/')
			path = ft_strjoin(path, "/");
		ft_lstadd_back(head, ft_lstnew(currDir, path));
	}

	closedir(fd_dir);
}

void	ls(char** argv, int flag, char** envp, bool* already_printed)
{
	int			i = 1;
	t_list*	head = NULL;

	while (argv[i])
	{
		if (argv[i][0] != '-')
		{
			getEntries(argv[i], envp, &head);
			sortList(&head, flag);
			printList(&head, flag, already_printed);

			if (flag & FLAG_R)
				recurs_traitement(&head, flag, envp, already_printed);

			ft_lst_free(&head);
		}
		i++;
	}
}

void recurs_traitement(t_list** head, int flag, char** envp, bool* already_printed)
{
	t_list** head_recur = head;
	while (*head_recur)
	{
		if (ft_strcmp(((struct dirent*)(*head_recur)->content)->d_name, ".") == 0 ||
			ft_strcmp(((struct dirent*)(*head_recur)->content)->d_name, "..") == 0 ||
			(!(flag & FLAG_a) && ((struct dirent*)(*head_recur)->content)->d_name[0] == '.'))
		{
			*head_recur = (*head_recur)->next;
			continue;
		}

		struct stat currStat;
		char*	path = ft_strjoin((*head_recur)->path, ((struct dirent*)(*head_recur)->content)->d_name);
		if (lstat(path, &currStat) != -1)
		{
			if ((currStat.st_mode & S_IFMT) == S_IFDIR)
			{
				char *tmp[] = {".", ft_strdup(path + 2), NULL};
				ls(tmp, flag, envp, already_printed);
				free(tmp[1]);
			}
		}
		free(path);

		*head_recur = (*head_recur)->next;
	}
}

int	init(int argc, char** argv)
{
	int		flag = 0;
	bool	multi = false;

	if (argc == 1)
		return (0);
	else
	{
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

			int j = 1;
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

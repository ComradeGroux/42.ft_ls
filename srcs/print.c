/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:54:14 by vgroux            #+#    #+#             */
/*   Updated: 2025/03/28 18:18:52 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/**
 * type of file (l=symbolic link | d=directory | c=character file)
 * -rw-rw-r--
 * 
 * number of hard-links
 * 
 * owner of the file
 * 
 * group this file belongs to
 * 
 * size
 * 
 * modification/creation date and time
 * 
 * dir name
*/
void	printLong(char* dname, char* path, int flag)
{
	struct stat	currStat;
	if (lstat(path, &currStat) != -1)
	{
		struct passwd	*user = getpwuid(currStat.st_uid);
		struct group	*groupe = getgrgid(currStat.st_gid);
		char*			ctimer = ctime(&(currStat.st_mtime));
		char*			timer = ft_gnl_strndup(ctimer, ft_strlen(ctimer) - 2);

		if (flag & FLAG_a)
		{
			printFileType(&currStat);
			printFilePerm(currStat);
			ft_printf(" %d %s %s %d %s %s\n", currStat.st_nlink, user->pw_name, groupe->gr_name, currStat.st_size, timer, dname);
		}
		else if (dname[0] != '.')
		{
			printFileType(&currStat);
			printFilePerm(currStat);
			ft_printf(" %d %s %s %d %s %s\n", currStat.st_nlink, user->pw_name, groupe->gr_name, currStat.st_size, timer, dname);
		}
		free(timer);
	}
	else
		ft_printf("Stat error on %s\n", path);
	free(path);
}

void	printFileType(struct stat *currStat)
{
	switch (currStat->st_mode & S_IFMT)
	{
		case S_IFLNK:
			ft_putchar_fd('l', 1);
			break;
		case S_IFCHR:
			ft_putchar_fd('c', 1);
			break;
		case S_IFBLK:
			ft_putchar_fd('b', 1);
			break;
		case S_IFIFO:
			ft_putchar_fd('p', 1);
			break;
		case S_IFDIR:
			ft_putchar_fd('d', 1);	
			break;
		case S_IFSOCK:
			ft_putchar_fd('s', 1);
			break;
		default:
			ft_putchar_fd('-', 1);
			break;
	}
}

void	printFilePerm(struct stat currStat)
{
	if (currStat.st_mode & S_IRUSR)
		ft_putchar_fd('r', 1);
	else
		ft_putchar_fd('-', 1);
	if (currStat.st_mode & S_IWUSR)
		ft_putchar_fd('w', 1);
	else
		ft_putchar_fd('-', 1);
	if (currStat.st_mode & S_IXUSR)
		ft_putchar_fd('x', 1);
	else
		ft_putchar_fd('-', 1);

	if (currStat.st_mode & S_IRGRP)
		ft_putchar_fd('r', 1);
	else
		ft_putchar_fd('-', 1);
	if (currStat.st_mode & S_IWGRP)
		ft_putchar_fd('w', 1);
	else
		ft_putchar_fd('-', 1);
	if (currStat.st_mode & S_IXGRP)
		ft_putchar_fd('x', 1);
	else
		ft_putchar_fd('-', 1);

	if (currStat.st_mode & S_IROTH)
		ft_putchar_fd('r', 1);
	else
		ft_putchar_fd('-', 1);
	if (currStat.st_mode & S_IWOTH)
		ft_putchar_fd('w', 1);
	else
		ft_putchar_fd('-', 1);
	if (currStat.st_mode & S_IXOTH)
		ft_putchar_fd('x', 1);
	else
		ft_putchar_fd('-', 1);
}

bool	printVal(struct dirent* currDir, char* path, int flag)
{
	if (flag & FLAG_l)
	{
		printLong(currDir->d_name, ft_strjoin(path, currDir->d_name), flag);
		return true;
	}
	else
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
	}
	return false;
}

void	printList(t_list **head, int flag)
{
	t_list*	curr = *head;
	if (flag & FLAG_l)
	{
		int	totalBlockSize = 0;
		struct stat	currStat;
		while (curr != NULL)
		{
			char*	path = ft_strjoin(curr->path, ((struct dirent*)curr->content)->d_name);

			if (flag & FLAG_a || ((struct dirent*)curr->content)->d_name[0] != '.')
			{
				if (lstat(path, &currStat) != -1)
					totalBlockSize += currStat.st_blocks;
			}
			free(path);
			curr = curr->next;
		}
		curr = *head;
		ft_printf("total %d\n", totalBlockSize / 2);
	}

	while (curr != NULL)
	{
		if (printVal(curr->content, curr->path, flag))
		{
			if (!(flag & FLAG_l))
				ft_putendl_fd("  ", 1);
		}
		curr = curr->next;
	}

	
}

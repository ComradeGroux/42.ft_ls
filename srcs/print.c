/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:54:14 by vgroux            #+#    #+#             */
/*   Updated: 2024/02/15 10:47:29 by vgroux           ###   ########.fr       */
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
void	printLong(struct dirent* currDir, int flag)
{
	struct stat	currStat;
	char*	dname = currDir->d_name;
	// ft_printf("%s\t", dname);
	if (stat(dname, &currStat) != -1)
	{
		// printf("%s\t", currDir->d_name);
		struct passwd	*user = getpwuid(currStat.st_uid);
		struct group	*groupe = getgrgid(currStat.st_gid);
		char*			ctimer = ctime(&(currStat.st_mtime));
		char*			timer = ft_gnl_strndup(ctimer, ft_strlen(ctimer) - 2);

		if (flag & FLAG_a)
		{
			printFileType(currStat);
			printFilePerm(currStat);
			ft_printf(" %d %s %s %d %s %s", currStat.st_nlink, user->pw_name, groupe->gr_name, currStat.st_size, timer, currDir->d_name);
		}
		else if (currDir->d_name[0] != '.')
		{
			printFileType(currStat);
			printFilePerm(currStat);
			ft_printf(" %d %s %s %d %s %s", currStat.st_nlink, user->pw_name, groupe->gr_name, currStat.st_size, timer, currDir->d_name);
		}
		free(timer);
	}
	else
		ft_printf("ERROR\t%s", currDir->d_name);
	ft_printf("\n");
}

void	printFileType(struct stat currStat)
{
	if (S_ISDIR(currStat.st_mode))
		ft_putchar_fd('d', 1);	
	else if (S_ISREG(currStat.st_mode))
		ft_putchar_fd('-', 1);
	else if (S_ISLNK(currStat.st_mode))
		ft_putchar_fd('l', 1);
	else if (S_ISCHR(currStat.st_mode))
		ft_putchar_fd('c', 1);
	else if (S_ISBLK(currStat.st_mode))
		ft_putchar_fd('b', 1);
	else if (S_ISFIFO(currStat.st_mode))
		ft_putchar_fd('p', 1);
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

bool	printVal(struct dirent* currDir, int flag)
{
	if (flag & FLAG_l)
	{
		// Print in long format
		// Will probably use stat() and so
		printLong(currDir, flag);
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

void	printList(t_list **head, int flag, bool* already_printed)
{
	t_list*	curr = *head;
	if (flag & FLAG_l)
	{
		int	totalBlockSize = 0;
		struct stat	currStat;
		while (curr != NULL)
		{
			if (flag & FLAG_a || ((struct dirent*)curr->content)->d_name[0] != '.')
			{
				if (stat(((struct dirent*)curr->content)->d_name, &currStat) != -1)
					totalBlockSize += currStat.st_blocks;
			}
			curr = curr->next;
		}
		curr = *head;
		ft_printf("total %d\n", totalBlockSize / 2);
	}
	while (curr != NULL)
	{
		if ((*already_printed) && !(flag & FLAG_l) && (((struct dirent*)curr->content)->d_name[0] != '.' || flag & FLAG_a))
			ft_printf("  ");
		if (printVal(curr->content, flag))
			*already_printed = true;
		curr = curr->next;
	}
}

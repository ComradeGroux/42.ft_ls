/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 08:26:20 by vgroux            #+#    #+#             */
/*   Updated: 2024/02/01 09:57:17 by vgroux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libft.h"
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <sys/xattr.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAN_LS "./ft_ls [OPTION]... [FILE]...\n\
[OPTION] are: \n\
\t-a\tdo not ignore entries starting with .\n\
\t-l\tuse a long listing format\n\
\t-r\treverse order while sorting\n\
\t-R\tlist subdirectories recursively\n\
\t-t\tsort by time, newest first"

#define FLAG_a 				0b000001
#define FLAG_l				0b000010
#define FLAG_R				0b000100
#define FLAG_r				0b001000
#define FLAG_t				0b010000
#define FLAG_MULTI			0b100000

int		init(int argc, char** argv);
void	ls(int flag);
void	ls_recur(int flag);
void	ft_error(char* str);

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgroux <vgroux@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 08:26:20 by vgroux            #+#    #+#             */
/*   Updated: 2024/02/01 09:08:30 by vgroux           ###   ########.fr       */
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

#define flag_a = 0b00001
#define flag_l = 0b00010
#define flag_R = 0b00100
#define flag_r = 0b01000
#define flag_t = 0b10000


void	ft_error(char* str);

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shleet_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:39:23 by aelkhali          #+#    #+#             */
/*   Updated: 2023/01/26 21:01:34 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "./environment.h"

#include <unistd.h>
#include <limits.h>

int	shleet_pwd(int fd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putstr_fd(cwd, fd);
		return (ft_putchar_fd('\n', fd), 0);
	}
	return (-1);
}

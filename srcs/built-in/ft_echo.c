/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 09:22:11 by asaffroy          #+#    #+#             */
/*   Updated: 2022/01/27 09:22:11 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_w_is_arg(char **args, int x, int y)
{
	if (args[x] && args[x][y] == '-' && args[x][++y] == 'n')
	{
		while (args[x][y])
		{
			if (args[x][y] != 'n')
				return (0);
			y++;
		}
		return (1);
	}
	return (0);
}

int	ft_echo(char **args, int fd)
{
	int	x;
	int	y;
	int	check;
	int	tamp;

	x = 1;
	y = 0;
	check = 1;
	while (args[x] && check)
	{
		if (!ft_w_is_arg(args, x, y))
			check = 0;
		else
			x++;
	}
	tamp = x;
	while (args[x])
	{
		write(fd, args[x], ft_strlen(args[x]));
		if (args[++x])
			write(fd, " ", 1);
	}
	if (tamp == 1)
		write(fd, "\n", 1);
	return (1);
}

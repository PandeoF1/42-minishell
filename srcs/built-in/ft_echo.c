/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:15:05 by tnard             #+#    #+#             */
/*   Updated: 2022/01/25 14:15:05 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_w_is_arg(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] && str[i + 1] && str[i + 2])
			if (str[i] == '-' && str[i + 1] == 'n' && str[i + 2] == ' ')
				i += 3;
	}
	return (0);
}

void	ft_echo(char *args, int fd)
{
	int	x;

	x = ft_w_is_arg(args);
	if (x == 0)
		write(fd, args, ft_strlen(args));
	else
	{
		if (args[x])
			write(fd, args + x, ft_strlen(args + x));
		write(fd, "\n", 1);
	}
	exit(0);
}

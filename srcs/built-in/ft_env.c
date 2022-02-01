/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:21:50 by tnard             #+#    #+#             */
/*   Updated: 2022/01/25 14:21:50 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_data *data, int fd)
{
	char	**tmp;
	int		x;
	char	**splitd;
	int		i;

	x = 0;
	tmp = data->tab_env;
	splitd = ft_split(*tmp, '\n');
	while (splitd[x])
	{
		i = 0;
		while (splitd[x] && splitd[x][i] != '=')
			i++;
		if (splitd[x][i + 1] && splitd[x][i + 1] != '\n')
			ft_putendl_fd(splitd[x], fd);
		x++;
	}
	ft_free_split(splitd);
	return (1);
}

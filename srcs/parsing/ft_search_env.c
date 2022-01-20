/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:36:57 by tnard             #+#    #+#             */
/*   Updated: 2022/01/20 14:11:40 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
* ft_search_env(char *env, char *var)
* desc : search the value of a variable in the env
*/

char	*ft_search_env(char *env, char *var)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (env[x])
	{
		if (env[x] != var[0])
			while (env[x] && env[x] != '\n')
				x++;
		else
		{
			y = 0;
			while (env[x] && y < (int)ft_strlen(var) && env[x] == var[y])
				ft_printf("", x++, y++);
			if (y == (int)ft_strlen(var) && env[x] == '=')
				return (ft_strndup(env + x + 1, ft_w_is_eon(env + x + 1)));
		}
		x++;
	}
	return (NULL);
}

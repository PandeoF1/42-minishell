/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:12:22 by tnard             #+#    #+#             */
/*   Updated: 2022/01/14 15:32:34 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_w_is_not_charset(char *str, char *charset)
{
	
}

char	*ft_env(char *env, char *str)
{
	char	*tmp;
	char	*var;
	int		x;
	int		y;

	x = 0;
	tmp = malloc(sizeof(char));
	while (str[x])
	{
		if (str[x] == '$')
		{
			
			if (str[x] && ft_isdigit[x])
			{
				while ()
			}
			y = 0;
			while (str[x] && str[x])
				x++;
		}
		x++;
	}
	ft_printf("env : %s\n", env);
	free(str);
	return (tmp);
}

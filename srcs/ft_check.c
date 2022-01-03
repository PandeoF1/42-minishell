/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 12:12:14 by tnard             #+#    #+#             */
/*   Updated: 2022/01/03 12:12:14 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (i);
		i++;
	}
	return (i);
}

/*
*	ft_check_quote(str)
*	desc : check if the string have correct quote
*/

int	ft_check_quote(char *str)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (str[x] == '"')
		{
			x++;
			while (str[x] && str[x] != '"')
				x++;
			if (!str[x] || str[x] != '"')
				return (0);
		}
		else if (str[x] == '\'')
		{
			x++;
			while (str[x] && str[x] != '\'')
				x++;
			if (!str[x] || str[x] != '\'')
				return (0);
		}
		if (str[x])
			x++;
	}
	return (1);
}

/*
*	ft_check_inout(str)
*	desc : check if the string have correct < > << >>
*/

int	ft_check_inout(char *str)
{

}

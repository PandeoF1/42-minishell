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

#include "../../includes/minishell.h"

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
*	ft_contains(str, c)
*	desc : check if str could contain c
*/

int	ft_contains(char *str, char c)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (str[x] == c)
			return (1);
		x++;
	}
	return (0);
}

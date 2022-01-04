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
	int	x;

	x = 0;
	while (str[x])
	{
		if ((str[x] == '<' && str[x + 1] == '>') || (str[x + 1] == '<' && str[x] == '>'))
			return (0);
		else if (str[x] == '|' && str[x + 1] == '|')
			return (0);
		x++;
	}
	return (1);
}

/*
*	ft_count_c(str)
*	desc :  count the number of char == c in str
*/
/*
int	ft_count_c(char *str, char c)
{
	int	x;
	int	i;

	x = 0;
	i = 0;
	while (str[x])
	{
		if (str[x] == c)
			i++;
		x++;
	}
	return (i);
}*/

/*
*	ft_check_inout_n(str)
*	desc : check if the string have correct output / input file after << >> < >
*/

int	ft_check_inout_n(char *str)
{
	char	**split;
	int		x;
	int		y;

	x = -1;
	split = ft_split(str, '|');
	while (split[++x])
	{
		y = 0;
		while (split[x][y])
		{

		}
	}
	return (1);
}

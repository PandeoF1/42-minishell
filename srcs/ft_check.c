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

int	ft_w_is_space(char *str)
{
	int	x;

	x = 0;
	while (str[x] && str[x] == ' ')
		x++;
	return (x);
}

int	ft_check_command(char **split, int x, int y)
{
	int	i;

	i = 0;

	return (i);
}

/*
*	ft_check_inout_n(str)
*	desc : check if the string have correct output / input file after << >> < >
*   error : clear leaks at exit
*/


int	ft_check_inout_n(char *str)
{
	char	**split;
	int		x;
	int		y;
	t_check	check;

	x = -1;
	split = ft_split(str, '|');
	while (split[++x])
	{
		y = -1;
		while (split[x][++y])
		{
			check.input = 0;
			check.output = 0;
			y += ft_w_is_space(split[x] + y);
			if (split[x][y] == '<')
				check.input = 1;
			else if (split[x][y] == '>')
				check.output = 1;
			y++;
			if (split[x][y] == '<' && check.input)
				return (0);
			else if (split[x][y] == '>')
			{
				check.output = 2;
				y++;
			}
			ft_printf("log : '%s' %d '%c'\n", split[x] + y, y, split[x][y]);
			y += ft_w_is_space(split[x] + y);
			ft_printf("log : '%s' %d '%c'\n", split[x] + y, y, split[x][y]);
			if ((!ft_isalpha(split[x][y]) && (check.output != 0 || check.input != 0)) || split[x][y] == '<' || split[x][y] == '>')
				return (0);
			if (!split[x][y])
				return (1);
			while (split[x][y] && split[x][y] != '<' && split[x][y] != '>')
				y++;
			ft_printf("log : %s\n", split[x] + y);
		}

	}
	return (1);
}

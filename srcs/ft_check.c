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

static int	ft_w_is_space(char *str)
{
	int	x;

	x = 0;
	while (str[x] && str[x] == ' ')
		x++;
	return (x);
}

int	ft_is_command(char *split)
{
	int	i;

	i = 0;

	return (i);
}

int	ft_is_out_file(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '>')
		i++;
	if (!str[i])
		return (0);
	i += ft_w_is_space(str + i + 1) + 1;
	if (!str[i] && !ft_isalpha(str[i]))
		return (0);
	return (1);
	/*i = ft_w_is_space(split[x]);
	if (split[x][i] && (!ft_isalpha(split[x][i]) && split[x][i] != ' '))
		return (0);
	while (split[x][i] && (ft_isalpha(split[x][i] || split[x][i] == ' ')))
		i++;
	if (split[x][i] && split[x][i] == '>')
		i++;
	else
		while (split[x][i] && split[x][i] != '<' || split[x][i] != '>')
			i++;
	if (!split[x][i])
		return (0);
	if (split[x][i] == '>')
	{
		return (-1);
	}
	else if (split[x][i] == '<')
	{
		if (ft_strlen(split[x][i]) == i)
			return (0);
		if (ft_strlen(split[x][i])  && split[x][i] == ' ')
	}*/
	return (1);
}

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

/*
*	ft_check_inout_n(str)
*	desc : check if the string have correct output / input file after << >> < >
*   error : clear leaks at exit
*/


int	ft_check_inout_n(char *str)
{
	char	**split;
	char	**split1;
	int		command;
	int		out_file;
	int		in_file;
	int		x;
	int		y;
	t_check	check;

	x = -1;
	split = ft_split(str, '|');
	while (split[++x])
	{
		y = -1;
		if (ft_contains(split[x], '>'))
		{
			if (split[x][0] == '>')
				y = 0;
			else
				y = 1;
			if (ft_strlen(split[x]) <= 1)
				return (0);
			split1 = ft_split(split[x], '>');
			while (split1[y])
			{
				out_file = ft_strlen(split1[y]) - ft_w_is_space(split1[y]);
				if (out_file)
					ft_printf("-- out file : %s --\n", split1[y]);
				else
					return (0);
				y++;
			}
		}
		if (ft_contains(split[x], '<'))
		{
			if (split[x][0] == '<')
				y = 0;
			else
				y = 1;
			if (ft_strlen(split[x]) <= 1)
				return (0);
			split1 = ft_split(split[x], '<');
			while (split1[y])
			{
				in_file = ft_strlen(split1[y]) - ft_w_is_space(split1[y]);
				if (out_file)
					ft_printf("-- in file : %s --\n", split1[y]);
				else
					return (0);
				y++;
			}
		}
	}
	ft_free_split(split);
	return (1);
}

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

static int	ft_w_is_space(char *str)
{
	int	x;

	x = 0;
	while (str[x] && str[x] == ' ')
		x++;
	return (x);
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

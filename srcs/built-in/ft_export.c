/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 13:46:05 by tnard             #+#    #+#             */
/*   Updated: 2022/01/26 13:46:06 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
	return (1);
}

int	ft_split_len(char **splitd)
{
	int		x;

	x = 0;
	while (splitd[x])
		x++;
	return (x);
}

char	**ft_sort(char *env)
{
	char	**splitd;
	int		x;
	int		y;
	int		a;

	a = 1;
	splitd = ft_splitd(env, '\n');
	while (a)
	{
		x = 0;
		a = 0;
		while (splitd[x])
		{
			y = 0;
			if (splitd[x + 1] && splitd[x][y] > splitd[x + 1][y])
				a = ft_swap(&splitd[x + 1], &splitd[x]);
			else if (splitd[x + 1] && splitd[x][y] && splitd[x + 1][y] && splitd[x][y] == splitd[x + 1][y])
			{
				while (splitd[x][y] && splitd[x + 1][y] && splitd[x][y] == splitd[x + 1][y])
					y++;
				if (splitd[x][y] && splitd[x + 1][y] && splitd[x][y] > splitd[x + 1][y])
					a = ft_swap(&splitd[x + 1], &splitd[x]);
			}
			x++;
		}
	}
	return (splitd);
}

void	ft_display_export(char **splitd)
{
	int		x;
	int		y;

	x = 0;
	while (splitd[x])
	{
		y = 0;
		ft_putstr("declare -x ");
		while (splitd[x][y])
		{
			if (splitd[x][y] == '=')
			{
				ft_putstr("=\"");
				y++;
			}
			ft_putchar(splitd[x][y]);
			y++;
		}
		ft_putstr("\"\n");
		x++;
	}
	ft_free_split(splitd);
}

void	ft_add_env(char **tmp, char *arg)
{
	char	*str;
	int		x;

	x = 0;
	str = NULL;
	while (arg[x])
	{
		if (arg[x] == '=' && !str)
		{
			str = ft_strndup(arg, x++);
			str = ft_strnjoin(str, "=", 1);
			str = ft_strnjoin(str, arg + x, ft_strlen(arg + x));
			x = ft_strlen(arg);
		}
		x++;
	}
	if (str == NULL)
	{
		str = ft_strdup(arg);
		str = ft_strnjoin(str, "=", 1);
	}
	(*tmp) = ft_strnjoin((*tmp), "\n", 1);
	(*tmp) = ft_strnjoin((*tmp), str, ft_strlen(str));
}

int	ft_is_valid(char *str)
{
	int	x;
	int	a;

	x = 0;
	a = 0;
	if (str[x] && !ft_isalpha(str[x]) && str[x] != '_')
		return (0);
	while (str[x])
	{
		if (str[x] == '=')
			a = 1;
		if (a == 0 && !ft_isalpha(str[x]) && str[x] != '_')
			return (0);
		x++;
	}
	return (1);
}

int	ft_export(t_data *data, char **arg, int fd)
{
	int		x;
	char	**tmp;

	x = 1;
	ft_printf("export:\n");
	tmp = data->tab_env;
	if (ft_split_len(arg) == 1)
		ft_display_export(ft_sort(*tmp));
	else
	{
		while (arg[x])
		{
			if (ft_is_valid(ft_ddquote(arg[x], 0)))
				ft_add_env(tmp, arg[x]);
			else
				ft_printf("export: %s: not a valid identifier\n", arg[x]);
			x++;
		}
	}
	ft_printf("fin export\n");
	return (1);
}

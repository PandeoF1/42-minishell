/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 22:59:28 by tnard             #+#    #+#             */
/*   Updated: 2022/01/31 22:59:28 by tnard            ###   ########lyon.fr   */
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

char	**ft_sort(char *env, int x, int y, int a)
{
	char	**splitd;

	splitd = ft_splitd(env, '\n');
	while (a)
	{
		x = -1;
		a = 0;
		while (splitd[++x])
		{
			y = 0;
			if (splitd[x + 1] && splitd[x][y] > splitd[x + 1][y])
				a = ft_swap(&splitd[x + 1], &splitd[x]);
			else if (splitd[x + 1] && splitd[x][y]
				&& splitd[x + 1][y] && splitd[x][y] == splitd[x + 1][y])
			{
				while (splitd[x][y] && splitd[x + 1][y]
					&& splitd[x][y] == splitd[x + 1][y])
					y++;
				if (splitd[x][y] && splitd[x + 1][y]
					&& splitd[x][y] > splitd[x + 1][y])
					a = ft_swap(&splitd[x + 1], &splitd[x]);
			}
		}
	}
	return (splitd);
}

void	ft_display_export(char **splitd, int x, int y, int a)
{
	while (splitd[x])
	{
		y = 0;
		a = 0;
		ft_putstr("declare -x ");
		while (splitd[x][y])
		{
			if (splitd[x][y] == '=' && splitd[x][y + 1])
			{
				a = 1;
				ft_putstr("=\"");
				y++;
			}
			else if (splitd[x][y] == '=')
				y++;
			if (splitd[x][y])
				ft_putchar(splitd[x][y]);
			y++;
		}
		if (a)
			ft_putstr("\"");
		ft_putstr("\n");
		x++;
	}
	ft_free_split(splitd);
}

char	*ft_add_env(char **tmp, char *arg)
{
	char	*str;
	int		x;

	(void)tmp;
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
		if (arg[x])
			x++;
	}
	if (str == NULL)
	{
		str = ft_strdup(arg);
		str = ft_strnjoin(str, "=", 1);
	}
	return (str);
}

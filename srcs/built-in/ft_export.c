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
			if (splitd[x][y])
				ft_putchar(splitd[x][y]);
			y++;
		}
		ft_putstr("\"\n");
		x++;
	}
	ft_free_split(splitd);
}

char	*ft_add_env(char **tmp, char *arg)
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
	return (str);
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

int	ft_env_len(char *env)
{
	int		x;

	x = 0;
	while (env[x])
	{
		if (env[x] == '=')
			return (x);
		x++;
	}
	return (x);
}

int	ft_exist(char *env, char *varr)
{
	int		x;
	int		y;
	char	*var;

	var = ft_strdup(varr);
	x = 0;
	y = 0;
	while (var[y++])
		if (var[y] == '=')
			var[y] = '\0';
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
			ft_printf("x : %d y : %d strlen : %d char : %c\n", x, y, ft_strlen(var), env[x]);
			if (y == (int)ft_strlen(var) && (!env[x] || env[x] == '=' || env[x] == '\n'))
			{
				free(var);
				return (x);
			}
		}
		x++;
	}
	free(var);
	return (0);
}

char	*ft_remove_in(char *str, int a, int b)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = (char *)malloc(sizeof(char) * ft_strlen(str) - (b - a));
	while (str[i])
	{
		if (i < a || i > b)
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}

void	ft_remove_env(char **tmp, char *arg)
{
	int		x;
	int		y;

	x = -1;
	while ((*tmp)[++x])
	{
		if ((*tmp)[x] != arg[0])
			while ((*tmp)[x] && (*tmp)[x] != '\n')
				x++;
		else
		{
			y = 0;
			while ((*tmp)[x] && y < (int)ft_strlen(arg) && (*tmp)[x] == arg[y] && arg[y] != '=')
				ft_printf("", x++, y++);
			if (y == (int)ft_env_len(arg) && (*tmp)[x] == '=')
			{
				y = x - y;
				while ((*tmp)[x] && (*tmp)[x] != '\n')
					x++;
				(*tmp) = ft_remove_in((*tmp), y, x);
				return ;
			}
		}
	}
}

void	ft_finish_export(char **tmp, char *env)
{
	if ((*tmp)[ft_strlen(*tmp) - 1] != '\n')
		(*tmp) = ft_strnjoin(*tmp, "\n", 1);
	(*tmp) = ft_strnjoin(*tmp, env, ft_strlen(env));
	if (env)
		free(env);
}

int	ft_export(t_data *data, char **arg, int fd)
{
	int		x;
	char	**tmp;
	char	*env;

	x = 0;
	env = NULL;
	tmp = data->tab_env;
	if (ft_split_len(arg) == 1)
		ft_display_export(ft_sort(*tmp));
	else
	{
		while (arg[++x])
		{
			if (ft_is_valid(ft_ddquote(arg[x], 0)))
			{
				env = ft_add_env(tmp, arg[x]);
				ft_remove_env(tmp, env);
				ft_finish_export(tmp, env);
			}
			else
				ft_printf("export: %s: not a valid identifier\n", arg[x]);
		}
	}
	return (1);
}

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

void	ft_remove_env(char **tmp, char *arg, int x, int y)
{
	while ((*tmp)[++x])
	{
		if ((*tmp)[x] != arg[0])
			while ((*tmp)[x] && (*tmp)[x] != '\n')
				x++;
		else
		{
			y = 0;
			while ((*tmp)[x] && y < (int)ft_strlen(arg)
				&& (*tmp)[x] == arg[y] && arg[y] != '=')
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
		if (!(*tmp)[x])
			break ;
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

int	ft_export(t_data *data, char **arg)
{
	int		x;
	char	**tmp;
	char	*env;

	x = 0;
	env = NULL;
	tmp = data->tab_env;
	if (ft_split_len(arg) == 1)
		ft_display_export(ft_sort(*tmp, 0, 0, 1), 0, 0, 0);
	else
	{
		while (arg[++x])
		{
			if (ft_is_valid(ft_ddquote(arg[x], 0)))
			{
				env = ft_add_env(tmp, arg[x]);
				ft_remove_env(tmp, env, -1, 0);
				ft_finish_export(tmp, env);
			}
			else
				ft_putstr_fd("export: not a valid identifier\n", 2);
		}
	}
	return (1);
}

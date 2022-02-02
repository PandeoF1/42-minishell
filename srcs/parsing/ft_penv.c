/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_penv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:12:22 by tnard             #+#    #+#             */
/*   Updated: 2022/02/02 13:44:27 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env_default(char **str, int *x, int y, char *env)
{
	char	*tmp;
	char	*var;
	int		b;

	b = 0;
	while ((*str)[(*x) + b] && ft_is_env_char((*str)[(*x) + b]))
		b++;
	var = ft_strndup((*str) + (*x), b);
	(*x) += b;
	tmp = ft_search_env(env, var);
	free(var);
	if (!tmp)
	{
		tmp = ft_strndup((*str), y);
		tmp = ft_strnjoin(tmp, (*str) + (*x), ft_strlen((*str) + (*x)));
	}
	else
		tmp = ft_replace((*str), tmp, (*x), y);
	free((*str));
	(*str) = tmp;
	(*x) = y;
}

void	ft_env_digit(char **str, int *x, int y)
{
	char	*tmp;

	tmp = ft_strndup((*str), (*x) - 1);
	tmp = ft_strnjoin(tmp, (*str) + (*x) + 1, ft_strlen((*str) + (*x) + 1));
	free((*str));
	(*str) = tmp;
	(*x) = y;
}

void	ft_env_tild(char **str, int *x, char *env)
{
	char	*var;
	char	*tmp;

	var = ft_search_env(env, "HOME");
	tmp = ft_strndup((*str), (*x)++);
	tmp = ft_strnjoin(tmp, var, ft_strlen(var));
	tmp = ft_strnjoin(tmp, (*str) + (*x), ft_strlen((*str) + (*x)));
	free(var);
	free((*str));
	(*str) = tmp;
}

char	*ft_penv(char *env, char *str, int x, int y)
{
	int		c[2];

	c[0] = 0;
	c[1] = 0;
	while (str[x])
	{
		ft_env_c(str, x, c);
		if (str[x] == '$')
		{
			y = x++;
			if (str[x] && c[1] == 0 && str[x] == '?')
				ft_env_return(&str, &x, y);
			else if (str[x] && c[1] == 0
				&& !ft_isdigit(str[x]) && ft_is_env_char(str[x]))
				ft_env_default(&str, &x, y, env);
			else if (str[x] && c[1] == 0 && ft_isdigit(str[x]))
				ft_env_digit(&str, &x, y);
		}
		else if (str[x] && str[x] == '~'
			&& c[0] == 0 && c[1] == 0 && ft_is_tild(str, x))
			ft_env_tild(&str, &x, env);
		if (str[x])
			x++;
	}
	return (str);
}

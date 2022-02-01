/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_penv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:12:22 by tnard             #+#    #+#             */
/*   Updated: 2022/02/01 15:30:34 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
*	ft_w_is_eon(str)
*	desc : count the number of char before the end of the string
*/

int	ft_w_is_eon(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

/*
*	ft_w_is_eon(str)
*	desc : check if c is a valid env char
*/

int	ft_is_env_char(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (1);
	return (0);
}

/*
*	ft_is_tild(str)
*	desc : check if the tilde is a valid env home path
*/

int	ft_is_tild(char *str, int x)
{
	if (str[x] == '~')
	{	
		if (str[x + 1])
			if (str [x + 1] == '~')
				return (0);
		if (str[x - 1])
			if (str[x - 1] == '~')
				return (0);
	}
	return (1);
}

void	ft_env_c(char *str, int x, int *c)
{
	if (str[x] == '\"' && c[0] == 0 && c[1] == 0)
		c[0] = 1;
	else if (str[x] == '\'' && c[0] == 0 && c[1] == 0)
		c[1] = 1;
	else if (str[x] == '\"' && c[0] == 1 && c[1] == 0)
		c[0] = 0;
	else if (str[x] == '\'' && c[0] == 0 && c[1] == 1)
		c[1] = 0;
}

/*
*	ft_env(char *env, char *str, int x, int b)
*	desc : replace all ~ and env variable in the str
*/

char	*ft_penv(char *env, char *str, int x, int b)
{
	char	*tmp;
	char	*var;
	int		c[2];
	int		y;

	c[0] = 0;
	c[1] = 0;
	while (str[x])
	{
		ft_printf("%d\n", x);
		if (str[x] && str[x] == '\"' && c[0] == 0 && c[1] == 0)
			c[0] = 1;
		else if (str[x] && str[x] == '\'' && c[0] == 0 && c[1] == 0)
			c[1] = 1;
		else if (str[x] && str[x] == '\"' && c[0] == 1 && c[1] == 0)
			c[0] = 0;
		else if (str[x] && str[x] == '\'' && c[0] == 0 && c[1] == 1)
			c[1] = 0;
		if (str[x] == '$')
		{
			ft_printf("%d\n", x);
			b = 0;
			y = x++;
			if (str[x] && c[1] == 0 && str[x] == '?')
			{
				tmp = ft_itoa(g_exit);
				x += ft_strlen(tmp);
				tmp = ft_replace(str, tmp, x, y);
				free(str);
				str = tmp;
				x = y;
			}
			else if (str[x] && c[1] == 0 && !ft_isdigit(str[x]) && ft_is_env_char(str[x]))
			{
				while (str[x + b] && ft_is_env_char(str[x + b]))
					b++;
				var = ft_strndup(str + x, b);
				x += b;
				tmp = ft_search_env(env, var);
				free(var);
				if (!tmp)
				{
					tmp = ft_strndup(str, y);
					tmp = ft_strnjoin(tmp, str + x, ft_strlen(str + x));
				}
				else
					tmp = ft_replace(str, tmp, x, y);
				free(str);
				str = tmp;
				x = y;
			}
			else if (str[x] && c[1] == 0 && ft_isdigit(str[x]))
			{
				while (str[x + b] && ft_isdigit(str[x + b]))
					b++;
				tmp = ft_strndup(str, x - 1);
				tmp = ft_strnjoin(tmp, str + x + b, ft_strlen(str + x + b));
				x += b;
				free(str);
				str = tmp;
				x = y;
			}
		}
		else if (str[x] && str[x] == '~' && c[0] == 0 && c[1] == 0 && ft_is_tild(str, x))
		{
			var = ft_search_env(env, "HOME");
			tmp = ft_strndup(str, x++);
			tmp = ft_strnjoin(tmp, var, ft_strlen(var));
			tmp = ft_strnjoin(tmp, str + x, ft_strlen(str + x));
			free(var);
			free(str);
			str = tmp;
		}
		if (str[x])
			x++;
	}
	return (str);
}

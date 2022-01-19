/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:12:22 by tnard             #+#    #+#             */
/*   Updated: 2022/01/19 14:30:25 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * ft_add_char(char *str, char c)
 * desc : desc malloc a string and add a char at the end of it
 * params : str to add c
 */

static char	*ft_add_char(char *str, char c)
{
	char	*new;
	int		x;

	x = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (NULL);
	while (str[x])
	{
		new[x] = str[x];
		x++;
	}
	new[x] = c;
	new[x + 1] = '\0';
	free(str);
	return (new);
}

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (NULL);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start] != '\0')
	{
		result[i] = s[start];
		start++;
		i++;
	}
	result[i] = '\0';
	return (result);
}

int		ft_w_is_eon(char *str)
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

char	*ft_search_env(char *env, char *var)
{
	int		x;
	int		y;
	char	*tmp2;

	x = 0;
	y = 0;
	while (env[x])
	{
		if (env[x] != var[0])
		{
			while (env[x] && env[x] != '\n')
				x++;
		}
		else
		{
			y = 0;
			while (env[x] && y < ft_strlen(var) && env[x] == var[y])
			{
				x++;
				y++;
			}
			if (y == ft_strlen(var) && env[x] == '=')
			{
				x++;
				tmp2 = ft_strndup(env + x, ft_w_is_eon(env + x));
				return (tmp2);
			}
		}
		x++;
	}
	return (NULL);
}

int	ft_is_env_char(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (1);
	return (0);
}

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

char	*ft_replace(char *str, char *tmp, int x, int y)
{
	char	*new;
	int		i;
	int		j;
	int		b;

	i = 0;
	j = 0;
	b = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(tmp)) + 1);
	if (!new)
		return (NULL);
	while (str[b])
	{
		if (i == y)
		{
			while (tmp[j])
				new[i++] = tmp[j++];
			b += (x - y);
		}
		else
			new[i++] = str[b++];
	}
	new[i] = '\0';
	free(tmp);
	return (new);
}

char	*ft_env(char *env, char *str) //encore des truc a patch
{
	char	*tmp;
	char	*var;
	int		x;
	int		y;
	int		b;

	x = 0;
	b = 0;
	while (str[x])
	{
		if (str[x] == '$')
		{
			b = 0;
			y = x++;
			if (str[x] && str[x] == '?')
			{
				//do la merde
			}
			else if (str[x] && !ft_isdigit(str[x]))
			{
				while (str[x + b] && ft_is_env_char(str[x + b]))
					b++;
				var = ft_strndup(str + x, b);
				x += b;
				tmp = ft_search_env(env, var);
				free(var);
				if (!tmp)
					tmp = ft_strdup("");
				tmp = ft_replace(str, tmp, x, y);
				free(str);
				str = tmp;
				x = y;
			}
			else if (str[x] && ft_isdigit(str[x]))
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
		else if (str[x] == '~' && ft_is_tild(str, x))
		{
			var = ft_search_env(env, "HOME");
			tmp = ft_strndup(str, x++);
			tmp = ft_strnjoin(tmp, var, ft_strlen(var));
			tmp = ft_strnjoin(tmp, str + x, ft_strlen(str + x));
			ft_printf("%s\n", tmp);
			free(var);
			free(str);
			str = tmp;
		}
		x++;
	}
	return (str);
}

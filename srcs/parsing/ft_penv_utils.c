/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_penv_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:13:50 by tnard             #+#    #+#             */
/*   Updated: 2022/02/02 13:13:50 by tnard            ###   ########lyon.fr   */
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

/*
*	ft_env(char *env, char *str, int x, int b)
*	desc : replace all ~ and env variable in the str
*/

void	ft_env_c(char *str, int x, int *c)
{
	if (str[x] && str[x] == '\"' && c[0] == 0 && c[1] == 0)
		c[0] = 1;
	else if (str[x] && str[x] == '\'' && c[0] == 0 && c[1] == 0)
		c[1] = 1;
	else if (str[x] && str[x] == '\"' && c[0] == 1 && c[1] == 0)
		c[0] = 0;
	else if (str[x] && str[x] == '\'' && c[0] == 0 && c[1] == 1)
		c[1] = 0;
}

void	ft_env_return(char **str, int *x, int y)
{
	char	*tmp;

	tmp = ft_itoa(g_exit);
	(*x) += ft_strlen(tmp);
	tmp[ft_strlen(tmp)] = '\0';
	tmp = ft_replace((*str), tmp, (*x), y);
	free((*str));
	(*str) = tmp;
	(*x) = y;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:28:24 by tnard             #+#    #+#             */
/*   Updated: 2022/01/20 12:38:36 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * ft_len_next(char *str)
 * desc : count all char in str until next > <
 * params : str to count
*/

int	ft_len_next(char *str)
{
	int		x;
	char	c;

	x = 0;
	while (str[x] && str[x] != ' ')
	{
		if (str[x] == '\'' || str[x] == '"')
		{
			c = str[x++];
			while (str[x] && str[x] != c)
				x++;
		}
		else
			x++;
	}
	return (x);
}

/*
 * int ft_quote(t_process **process, int x, int y, char **split)
 * desc : parse the curent line after the <> and return the new process
 * todo : free(process) if err ?
 */

void	ft_quote(t_process **process, int x, int *y, char **split)
{
	char	c;
	int		i;
	t_inout	*tmp;

	i = 0;
	c = split[x][(*y)];
	tmp = ft_create_inout();
	if (split[x][(*y) + 1] && (split[x][(*y) + 1] == c))
	{
		if (c == '<')
			tmp->type = 3;
		else if (c == '>')
			tmp->type = 4;
		(*y)++;
	}
	else
	{
		if (c == '<')
			tmp->type = 1;
		else if (c == '>')
			tmp->type = 2;
	}
	(*y) += ft_w_is_space(split[x] + (*y) + 1) + 1;
	tmp->file = ft_strndup(split[x] + (*y), ft_len_quote(split[x] + (*y)));
	(*y) += ft_len_next(split[x] + (*y));
}

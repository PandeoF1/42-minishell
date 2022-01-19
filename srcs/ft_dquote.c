/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dquote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:52:49 by tnard             #+#    #+#             */
/*   Updated: 2022/01/19 18:15:24 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_remove(char *str, int c)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = (char *)malloc(sizeof(char) * ft_strlen(str));
	while (str[i])
	{
		if (i != c)
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}

char	**ft_dquote(char **split)
{
	int		x;
	int		a;
	int		y;
	char	c;

	c = '\0';
	x = 0;
	y = 0;
	while (split[y])
	{
		x = 0;
		while (split[y][x])
		{
			if (c == '\0' && (split[y][x] == '\'' || split[y][x] == '"'))
			{
				c = split[y][x];
				a = x;
			}
			else if (c == split[y][x])
			{
				c = '\0';
				split[y] = ft_remove(split[y], a);
				split[y] = ft_remove(split[y], x - 1);
				x -= 2;
			}
			x++;
		}
		y++;
	}
	return (split);
}

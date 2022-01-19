/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dquote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:52:49 by tnard             #+#    #+#             */
/*   Updated: 2022/01/19 18:08:15 by tnard            ###   ########lyon.fr   */
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
		ft_printf("on touche a : %s\n", split[y]);
		while (split[y][x])
		{
			if (c == '\0' && (split[y][x] == '\'' || split[y][x] == '"'))
			{
				ft_printf("quote\n");
				c = split[y][x];
				a = x;
			}
			else if (c == split[y][x])
			{
				//destroy
				ft_printf("fin quote\n");
				c = '\0';
				split[y] = ft_remove(split[y], a);
				split[y] = ft_remove(split[y], x);
			}
			ft_printf("on passe sur %c\n", split[y][x]);
			x++;
		}
		y++;
	}
	return (split);
}

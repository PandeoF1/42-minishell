/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:41:11 by tnard             #+#    #+#             */
/*   Updated: 2022/01/20 14:12:05 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
*	ft_replace(char *str, char *tmp, int x, int y)
*	desc : replace in str the var with the value of the env
*/

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

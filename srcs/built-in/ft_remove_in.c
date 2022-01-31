/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 23:00:26 by tnard             #+#    #+#             */
/*   Updated: 2022/01/31 23:00:26 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

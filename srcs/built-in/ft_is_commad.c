/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_commad.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:03:03 by tnard             #+#    #+#             */
/*   Updated: 2022/01/26 14:03:03 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_command(char *str, char *cmd)
{
	int	x;

	x = 0;
	if (ft_strlen(cmd) != ft_strlen(str))
		return (1);
	while (cmd[x])
	{
		if (str[x] != cmd[x])
			return (1);
		x++;
	}
	return (0);
}
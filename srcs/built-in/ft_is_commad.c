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

int	ft_is_command(char *cmd, char *str)
{
	int	x;

	x = 0;
	if (ft_strlen(cmd) != ft_strlen(str))
		return (0);
	while (cmd[x])
	{
		if (cmd[x] != str[x])
			return (0);
		x++;
	}
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 04:00:30 by tnard             #+#    #+#             */
/*   Updated: 2022/01/28 04:00:30 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset(t_data *data, char **arg, int fd)
{
	int		x;
	char	**tmp;

	x = 0;
	tmp = data->tab_env;
	while (arg[++x])
	{
		if (ft_is_valid(ft_ddquote(arg[x], 0)))
			ft_remove_env(tmp, arg[x]);
		else
			ft_printf("unset: %s: not a valid identifier\n", arg[x]);
	}
	return (1);
}

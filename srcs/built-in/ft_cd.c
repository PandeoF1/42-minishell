/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:55:26 by asaffroy          #+#    #+#             */
/*   Updated: 2022/01/31 22:32:41 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(t_data *data, int fd, char **path)
{
	char	**env;
	char	*tmp;

	env = data->tab_env;
	if (ft_strstrlen(path) == 1)
	{
		tmp = ft_search_env(*env, "HOME");
		if (!tmp || ft_strlen(tmp) == 0)
			ft_printf("cd: HOME not set\n");
		else
			chdir(tmp);
		free (tmp);
	}
	else if (ft_strstrlen(path) == 2)
		chdir(path[1]);
	else
		ft_printf("wrong number of args arguments\n");
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:55:26 by asaffroy          #+#    #+#             */
/*   Updated: 2022/01/28 23:24:11 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(t_data *data, int fd, char **path)
{
	char	**env;
	char	*tmp;

	env = data->tab_env;
	if (ft_strlen(*path) == 1)
	{
		tmp = ft_search_env(*env, "HOME");
		if (!tmp || ft_strlen == 0)
			ft_printf("cd: HOME not set\n");
		else
			chdir(tmp);
		free (tmp);
	}
	else if (ft_strlen(*path) == 2)
		chdir(path[1]);
	else
		ft_perror("wrong number of args arguments");
	return (1);
}

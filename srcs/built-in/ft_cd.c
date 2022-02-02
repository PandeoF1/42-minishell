/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:55:26 by asaffroy          #+#    #+#             */
/*   Updated: 2022/02/02 09:10:19 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(t_data *data, int fd, char **path)
{
	char	**env;
	char	*tmp;

	(void)fd;
	env = data->tab_env;
	if (ft_strstrlen(path) == 1)
	{
		tmp = ft_search_env(*env, "HOME");
		if (!tmp || ft_strlen(tmp) == 0)
			ft_putstr_fd("cd: HOME not set\n", 2);
		else
			if (chdir(tmp))
				ft_putstr_fd("minishell: cd: No such file or directory\n", 2);
		free (tmp);
	}
	else if (ft_strstrlen(path) == 2)
	{
		if (chdir(path[1]))
			ft_putstr_fd("minishell: cd: No such file or directory\n", 2);
	}
	else
		ft_putstr_fd("wrong number of arguments\n", 2);
	return (1);
}

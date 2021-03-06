/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:55:26 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/12 11:26:10 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_update_cd(char **env)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = getcwd(NULL, 0);
	ft_remove_env(env, "PWD", -1, 0);
	tmp = ft_strjoin("PWD=", tmp2);
	(*env) = ft_strnjoin((*env), "\n", 1);
	(*env) = ft_strnjoin((*env), tmp, ft_strlen(tmp));
	free(tmp2);
	free(tmp);
}

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
			ft_putstr_fd("minishell: cd: Not a directory\n", 2);
	}
	else
		ft_putstr_fd("wrong number of arguments\n", 2);
	ft_update_cd(env);
	return (1);
}

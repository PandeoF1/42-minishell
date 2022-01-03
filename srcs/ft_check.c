/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 12:12:14 by tnard             #+#    #+#             */
/*   Updated: 2022/01/03 12:12:14 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
* ft_check_commad(cmd, env)
* desc : check if the command exist in the env
* params : the command to check and env
* error : leaks / normi
*/

int	ft_check_command(char *cmd, char **env)
{
	int		i;
	char	**tab;
	char	*try;

	if (!access(cmd, F_OK))
	{
		if (!access(cmd, R_OK))
			return (1);
		else
			return (-1);
	}
	cmd = ft_strjoin("/", cmd);
	i = find_path(env);
	tab = ft_split(env[i] + 5, ':');
	i = -1;
	while (tab[++i])
	{
		try = ft_strjoin(tab[i], cmd);
		i = 0;
		while (tab[i])
			free(tab[i++]);
		free(tab)
		free(try)
		free(cmd)
		if (!access(try, X_OK))
			return (1);
	}
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab)
	free(try)
	free(cmd)
	return (0);
}

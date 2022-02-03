/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:18:04 by asaffroy          #+#    #+#             */
/*   Updated: 2022/02/03 09:45:13 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
*int	find_path(char **env)
*env	env of the shell
*do :	find the line "PATH" in the env
*/

int	find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (i);
		i++;
	}
	return (-1);
}

/*
*char	*ft_check_arg(char *cmd, char **env)
*cmd	command to search in /bin
*env	env of the shell
*error	not norminette
*do :	check if the command exist and if we have the rights to use it 
*/

char	*ft_strxjoin(char *s1, char *s2, int n)
{
	int		i;
	int		j;
	char	*str;
	int		k;

	k = 0;
	j = ft_strlen(s2) + n + 1;
	str = (char *)malloc(sizeof(char) * j);
	if (!str)
		return (NULL);
	i = -1;
	while (++i < (int)ft_strlen(s1))
		str[i] = s1[i];
	while (n-- && s2[k])
		str[i++] = s2[k++];
	str[i] = '\0';
	free(s2);
	return (str);
}

char	*ft_check_arg2(char **env, char *temp, int i)
{
	char	**tab;
	char	*try;

	tab = ft_split(env[i] + 5, ':');
	i = 0;
	while (tab[i])
	{
		try = ft_strjoin(tab[i], temp);
		if (!access(try, X_OK))
		{
			i = -1;
			while (tab[++i])
				free(tab[i]);
			free(tab);
			return (try);
		}
		i++;
	}
	free(tab);
	return (NULL);
}

char	*ft_check_arg(char *cmd, char **env)
{
	char		*temp;
	char		*try_temp;

	try_temp = NULL;
	temp = ft_ddquote(ft_strdup(cmd), 0);
	if (!access(temp, F_OK))
	{
		if (ft_strlen(temp) > 2 && temp[0] == '.'
			&& temp[1] == '/' && !access(temp, X_OK))
			return (temp);
		else
			if (ft_strchr(temp, '/'))
				ft_perror("minishell: Permission denied", 126);
	}
	if (ft_strchr(temp, '/'))
		ft_perror("minishell: No such file or directory", 127);
	temp = ft_strxjoin("/", temp, ft_strlen(temp));
	if (find_path(env) == -1)
		ft_perror("minishell: No such file or directory", 127);
	else
		try_temp = ft_check_arg2(env, temp, find_path(env));
	free(temp);
	if (!try_temp)
		ft_perror("minishell: command not found", 127);
	return (try_temp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 10:48:16 by tnard             #+#    #+#             */
/*   Updated: 2022/01/03 10:48:16 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*ft_export_env(char **env)
{
	char	*str;
	int		x;

	x = 1;
	str = ft_strdup(env[0]);
	while (env[x])
	{
		str = ft_strnjoin(str, "\n", 1);
		str = ft_strnjoin(str, env[x], ft_strlen(env[x]));
		x++;
	}
	return (str);
}

char	*ft_readline(void)
{
	char	*str;
	char	*tmp;

	str = ft_strdup("\001\e[0;32m\002minishell\001\e[0m\002:\001\e[0;34m\002");
	tmp = getcwd(NULL, 0);
	str = ft_strnjoin(str, tmp, ft_strlen(tmp));
	free(tmp);
	str = ft_strnjoin(str, "\001\e[0m\001$ ", ft_strlen("\001\e[0m\002$ "));
	return (str);
}

void	ft_add_shlvl(char **env)
{
	char	*tmp;
	char	*tmp1;
	int		x;

	tmp = NULL;
	tmp = ft_search_env(*env, "SHLVL");
	if (tmp)
	{
		x = ft_atoi(tmp);
		x++;
		free(tmp);
		tmp = ft_itoa(x);
		ft_remove_env(env, "SHLVL", -1, 0);
		tmp1 = ft_strjoin("SHLVL=", tmp);
		free(tmp);
		(*env) = ft_strnjoin((*env), "\n", 1);
		(*env) = ft_strnjoin((*env), tmp1, ft_strlen(tmp1));
		free(tmp1);
	}
}

int	ft_while(char **penv)
{
	char	**splitd;
	char	*readlin;
	char	*tmp;

	readlin = ft_readline();
	tmp = readline(readlin);
	free(readlin);
	if (!tmp)
	{
		ft_printf("exit\n");
		return (0);
	}
	else if (ft_strlen(tmp) != 0)
	{
		add_history(tmp);
		tmp = ft_penv((*penv), tmp, 0, 0);
		splitd = ft_splitd((*penv), '\n');
		ft_parse_command(tmp, splitd, penv);
		ft_free_split(splitd);
		free(tmp);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*penv;

	(void)argc;
	(void)argv;
	g_exit = 0;
	signal(SIGINT, action);
	signal(SIGQUIT, sig_quit);
	if (!envp[0])
		penv = ft_strdup("MINISHELL=1");
	else
		penv = ft_export_env(envp);
	ft_add_shlvl(&penv);
	while (1)
	{
		if (ft_while(&penv))
			continue ;
		else
			break ;
	}
	free(penv);
	rl_clear_history();
	return (0);
}

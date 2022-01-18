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

static void	action(int sig)
{
	ft_printf("\b\b  \b\b");
	ft_printf("\n$> ");
	exit(0);
}

static void	sig_quit(int sig)
{
	ft_printf("\b\b  \b\b");
}

static char	*ft_export_env(char **env)
{
	char	*str;
	int		x;

	x = 1;
	str = ft_strdup(env[0]);
	while (env[x])
	{
		str = ft_strjoin(str, "\n");
		str = ft_strjoin(str, env[x]);
		x++;
	}
	return (str);
}

int	main(int argc, char **argv, char **envp)
{
	char	*tmp;
	char	*env;
	char	*penv;

	(void)argc;
	(void)argv;
	env = getenv("PATH");
	signal(SIGINT, action);
	signal(SIGQUIT, sig_quit);
	penv = ft_export_env(envp);
	while (1)
	{
		tmp = readline("%> ");
		if (ft_strlen(tmp) != 0)
		{
			if (ft_strncmp(tmp, "exit\n", ft_strlen(tmp)) == 0)
				break ;
			add_history(tmp);
			tmp = ft_env(penv, tmp);
			ft_parse_command(tmp, env);
		}
		//rl_clear_history();
		free(tmp);
	}
	free(penv);
	if (tmp)
		free(tmp);
	return (0);
}

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

static void	sig_quit(int sig)
{
	(void)sig;
	ft_putstr_fd("\b\b  \b\b", 1);
}

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

	str = ft_strdup("\e[0;32mminishell\e[0m:\e[0;34m");
	tmp = getcwd(NULL, 0);
	str = ft_strnjoin(str, tmp, ft_strlen(tmp));
	free(tmp);
	str = ft_strnjoin(str, "\e[0m$ ", ft_strlen("\e[0m$ "));
	return (str);
}

static void	action(int sig)
{
	(void)sig;
	static int x = 0;
	ft_putstr_fd("\b\b", 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd(ft_readline(), 1);
	x++;
	if (x == 10)
		exit(0);
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
		tmp = readline(ft_readline());
		if (ft_strlen(tmp) != 0)
		{
			add_history(tmp);
			tmp = ft_env(penv, tmp, 0, 0);
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

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
	if (g_exit != -1053)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
		g_exit = 131;
	}
	g_exit = 0;
}

static void	action(int sig)
{
	(void)sig;
	if (g_exit != -1053)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit = 130;
	}
	g_exit = 1;
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

void	test(int sig)
{
	ft_printf("yolo\n");
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
		ft_remove_env(env, "SHLVL");
		tmp1 = ft_strjoin("SHLVL=", tmp);
		free(tmp);
		(*env) = ft_strnjoin((*env), "\n", 1);
		(*env) = ft_strnjoin((*env), tmp1, ft_strlen(tmp1));
	}
}

void	ft_remove_shlvl(char **env) //logiquement pas besoin car l'env ce detruit
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
		ft_remove_env(env, "SHLVL");
		tmp1 = ft_strjoin("SHLVL=", tmp);
		free(tmp);
		if ((*env)[ft_strlen(*env) - 1] != '\n')
			(*env) = ft_strnjoin((*env), "\n", 1);
		(*env) = ft_strnjoin((*env), tmp1, ft_strlen(tmp1));
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*tmp;
	char	*penv;
	char	**splitd;
	char	*readlin;

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
		readlin = ft_readline();
		tmp = readline(readlin);
		free(readlin);
		if (!tmp)
		{
			ft_printf("exit\n");
			exit (1);
		}
		if (ft_strlen(tmp) != 0)
		{
			add_history(tmp);
			tmp = ft_penv(penv, tmp, 0, 0);
			ft_printf("tmp : %s\n", tmp);
			splitd = ft_splitd(penv, '\n');
			ft_parse_command(tmp, splitd, &penv);
			ft_free_split(splitd);
			free(tmp);
		}
	}
	free(penv);
	if (tmp)
		free(tmp);
	rl_clear_history();
	return (0);
}

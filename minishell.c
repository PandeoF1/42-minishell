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
	ft_printf("\n%> ");
	exit(0);
}

static void	sig_quit(int sig)
{
	ft_putstr("\b\b \b\b");
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

char	*ft_readline(char *penv, char *str)
{
	char	*tmp;
	char	*var;
	char	test[UCHAR_MAX];
	char	*a;

	tmp = malloc(sizeof(char));
	var = ft_search_env(penv, "USER");
	tmp = ft_strnjoin(tmp, "\e[0;34m", ft_strlen("\e[0;34m"));
	tmp = ft_strnjoin(tmp, var, ft_strlen(var));
	//free(var);
	tmp = ft_strnjoin(tmp, "\e[0m@\e[0;35m", ft_strlen("\e[0m@\e[0;35m"));
	getcwd(test, UCHAR_MAX);
	tmp = ft_strnjoin(tmp, test, ft_strlen(test));
	tmp = ft_strnjoin(tmp, "\e[0m%> ", ft_strlen("> \e[0m"));
	return (tmp);
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
		//ft_printf("%> ");
		//tmp = ft_get_input(0, 0, 0);
		tmp = readline("%> ");
		if (ft_strlen(tmp) != 0)
		{
			if (ft_strncmp(tmp, "exit\n", ft_strlen(tmp)) == 0)
				break ;
			add_history(tmp);
			tmp = ft_env(penv, tmp); // ajout du ~ si dans ' pas de $USER
			//tmp[ft_strlen(tmp) - 1] = '\0';
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

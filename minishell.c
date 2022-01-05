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
	ft_printf("\n$> ");
	exit(0); 	
}

static void	sig_quit(int sig)
{
	ft_printf("\b\b  \b\b");
}

int	main(int argc, char **argv, char **env)
{
	char	*tmp;

	(void)argc;
	(void)argv;
	signal(SIGINT, action);
	signal(SIGQUIT, sig_quit);
	while (1)
	{
		ft_putstr("$> ");
		tmp = ft_get_input(0, 0, 0);
		//ft_printf("log : str = %s", tmp);
		ft_parse_command(tmp, env);
		if (ft_strncmp(tmp, "exit\n", ft_strlen(tmp)) == 0)
			break ;
		free(tmp);
	}
	if (tmp)
		free(tmp);
	return (0);
}

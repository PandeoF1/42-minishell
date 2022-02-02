/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:38:46 by tnard             #+#    #+#             */
/*   Updated: 2022/02/02 13:38:46 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_quit(int sig)
{
	(void)sig;
	if (g_exit != -1053)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
		g_exit = 131;
	}
	g_exit = 0;
}

void	action(int sig)
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

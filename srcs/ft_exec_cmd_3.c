/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:31:23 by asaffroy          #+#    #+#             */
/*   Updated: 2022/02/01 09:31:49 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_execute_cmd_11(t_process *temp, t_data *data, int i, char **env)
{
	data->tab_args[0] = ft_dquote(ft_splitd(temp->cmd_arg, ' '), 0, 0);
	if (!ft_is_command(temp->command, "exit"))
	{
		write(2, "exit\n", 5);
		free_exec(data, i);
		exit(0);
	}
	if (!ft_built(0, env, data, temp))
		one_proc(data, temp, env);
	else
	{
		free_exec(data, i);
		return (0);
	}
	data->j = 0;
	return (1);
}

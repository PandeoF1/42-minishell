/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:31:23 by asaffroy          #+#    #+#             */
/*   Updated: 2022/03/16 15:07:42 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_execute_cmd_11(t_process *temp, t_data *data, int i, char **env)
{
	char	**splited;
	int		check;

	splited = ft_dquote(ft_splitd(temp->cmd_arg, ' '), 0, 0);
	check = ft_built_one(0, data, temp, splited);
	if (check == 0)
		one_proc(data, temp, env, splited);
	else
	{
		if (check == 2)
			data->status = 1;
		else
			data->status = 0;
		ft_free_split(splited);
		free_exec(data, i);
		return (0);
	}
	ft_free_split(splited);
	data->j = 0;
	return (1);
}

int	ft_status(t_data *data)
{
	if (WIFEXITED(data->status))
		return (WEXITSTATUS(data->status));
	else if (WIFSIGNALED(data->status))
		return (WTERMSIG(data->status));
	return (data->status);
}

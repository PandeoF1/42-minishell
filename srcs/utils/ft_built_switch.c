/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_switch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:33:19 by asaffroy          #+#    #+#             */
/*   Updated: 2022/02/14 09:58:22 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_built(int i, t_data *data, t_process *temp)
{
	if (!ft_is_command(temp->command, "pwd"))
		return (ft_pwd(1));
	if (!ft_is_command(temp->command, "env"))
		return (ft_env(data, 1));
	if (!ft_is_command(temp->command, "exit"))
		exit(0);
	if (!ft_is_command(temp->command, "cd"))
		return (ft_cd(data, 1, data->tab_args[i]));
	if (!ft_is_command(temp->command, "export"))
		return (ft_export(data, data->tab_args[i]));
	if (!ft_is_command(temp->command, "unset"))
		return (ft_unset(data, data->tab_args[i], 1));
	if (!ft_is_command(temp->command, "echo"))
		return (ft_echo(data->tab_args[i], 1));
	return (0);
}

int	ft_built_one(int i, t_data *data, t_process *temp, char **splited)
{
	if (!ft_is_command(temp->command, "pwd"))
		return (ft_pwd(1));
	if (!ft_is_command(temp->command, "env"))
		return (ft_env(data, 1));
	if (!ft_is_command(temp->command, "exit"))
		exit(0);
	if (!ft_is_command(temp->command, "cd"))
		return (ft_cd(data, 1, splited));
	if (!ft_is_command(temp->command, "export"))
		return (ft_export(data, splited));
	if (!ft_is_command(temp->command, "unset"))
		return (ft_unset(data, splited, 1));
	if (!ft_is_command(temp->command, "echo"))
		return (ft_echo(splited, 1));
	return (0);
}

int	ft_built_red(int i, t_data *data, t_process *temp)
{
	if (!ft_is_command(temp->command, "pwd"))
		return (ft_pwd(data->fd[2 * (data->ind + 1) + 1]));
	if (!ft_is_command(temp->command, "env"))
		return (ft_env(data, data->fd[2 * (data->ind + 1) + 1]));
	if (!ft_is_command(temp->command, "exit"))
		ft_exit(temp, data);
	if (!ft_is_command(temp->command, "cd"))
		return (ft_cd(data, data->fd[2 * (data->ind + 1) + 1],
				data->tab_args[i]));
	if (!ft_is_command(temp->command, "export"))
		return (ft_export
			(data, data->tab_args[i]));
	if (!ft_is_command(temp->command, "echo"))
		return (ft_echo(data->tab_args[i], data->fd[2 * (data->ind + 1) + 1]));
	if (!ft_is_command(temp->command, "unset"))
		return (ft_unset
			(data, data->tab_args[i], data->fd[2 * (data->ind + 1) + 1]));
	return (0);
}

int	ft_built_red2(int i, t_data *data, t_process *temp)
{
	if (!ft_is_command(temp->command, "pwd"))
		return (ft_pwd(data->file[i]));
	if (!ft_is_command(temp->command, "env"))
		return (ft_env(data, data->file[i]));
	if (!ft_is_command(temp->command, "exit"))
		ft_exit(temp, data);
	if (!ft_is_command(temp->command, "cd"))
		return (ft_cd(data, data->file[i], data->tab_args[i]));
	if (!ft_is_command(temp->command, "export"))
		return (ft_export
			(data, data->tab_args[i]));
	if (!ft_is_command(temp->command, "echo"))
		return (ft_echo(data->tab_args[i], data->file[i]));
	if (!ft_is_command(temp->command, "unset"))
		return (ft_unset
			(data, data->tab_args[i], data->file[i]));
	return (0);
}

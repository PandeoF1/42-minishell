/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:15:24 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/20 11:09:40 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	red4_proc(t_data *data, t_process *temp, char **env, int i)
{
	data->pid1[i] = fork();
	if (data->pid1[i] < 0)
		ft_ffailed("forking failed\n", 1, data);
	if (data->pid1[i] == 0)
	{
		data->file[i] = open(ft_ddquote(data->inout->file, 0),
				O_RDWR | O_APPEND | O_CREAT, 0644);
		if (data->file[i] < 0)
			ft_perror("\033[2K\r\033[0;31mError\033[0m : file creation failed", 1);
		if (!temp->command)
			exit(0);
		data->tab_args[i] = ft_dquote(ft_splitd(temp->cmd_arg, ' '), 0, 0);
		if (temp->in_prev != 0)
			if (dup2(data->fd[2 * data->ind - 2], STDIN_FILENO) == -1)
				ft_perror("dup2 n1 failed in pipe_proc", 1);
		red4_proc_2(data, temp, env, i);
		data->tab_paths[i] = ft_check_arg(temp->command, env);
		if (temp->command != NULL)
			if (data->inout->next == NULL)
				if (execve(data->tab_paths[i], data->tab_args[i], env) == -1)
					ft_perror("minishell : unable to perform this command", 1);
		exit(0);
	}
}

void	red4_proc_2(t_data *data, t_process *temp, char **env, int i)
{
	(void)env;
	if (dup2(data->fd[2 * data->ind], STDIN_FILENO) == -1)
		ft_perror("dup2 n1 failed in red_4_proc_2", 1);
	if (data->inout->next != NULL)
	{
		if (dup2(data->fd[2 * data->ind + 1], STDOUT_FILENO) == -1)
			ft_perror("dup2 n1 failed in red_4_proc_2", 1);
	}
	else if (data->inout->next == NULL)
	{
		if (ft_built_red2(i, data, temp))
			exit(0);
		if (dup2(data->file[i], STDOUT_FILENO) == -1)
			ft_perror("dup2 n1 failed in red_4_proc_2", 1);
	}
	close_pipes(data);
	close(data->file[i]);
}

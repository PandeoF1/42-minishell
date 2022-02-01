/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:10:13 by asaffroy          #+#    #+#             */
/*   Updated: 2022/02/01 15:13:57 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	one_proc(t_data *data, t_process *temp, char **env)
{
	data->pid1[0] = fork();
	if (data->pid1[0] < 0)
		ft_perror("forking failed in one_proc\n", 1);
	if (data->pid1[0] == 0)
	{
		data->tab_paths[0] = ft_check_arg(temp->command, env);
		close_pipes(data);
		if (execve(data->tab_paths[0], data->tab_args[0], env) == -1)
			ft_perror("failed to exec in one_proc", 1);
	}
}

void	pipe_proc(t_data *data, t_process *temp, char **env, int i)
{
	data->pid1[i] = fork();
	if (data->pid1[i] < 0)
		ft_perror("forking failed\n", 1);
	if (data->pid1[i] == 0)
	{
		data->tab_args[i] = ft_dquote(ft_splitd(temp->cmd_arg, ' '), 0, 0);
		pipe_proc_2(temp, data, i, env);
		close_pipes(data);
		data->tab_paths[i] = ft_check_arg(temp->command, env);
		if (execve(data->tab_paths[i], data->tab_args[i], env) != 0)
			ft_perror("failed to exec in pipe_proc", 1);
	}
}

void	pipe_proc_2(t_process *temp, t_data *data, int i, char **env)
{
	(void)env;
	if (temp->in_prev != 0)
	{
		if (dup2(data->fd[2 * data->ind], STDIN_FILENO) == -1)
			ft_perror("dup2 n1 failed in pipe_proc", 1);
	}
	if (temp->out_next != 0)
	{
		if (ft_built_red(i, data, temp))
			exit (0);
		if (dup2(data->fd[2 * (data->ind + 1) + 1], STDOUT_FILENO) == -1)
			ft_perror("dup2 n2 failed in pipe_proc", 1);
	}
	else
		if (ft_built(i, data, temp))
			exit (0);
}

void	red_proc(t_data *data, t_process *temp, char **env, int i)
{
	data->pid1[i] = fork();
	if (data->pid1[i] < 0)
		ft_perror("forking failed\n", 1);
	if (data->pid1[i] == 0)
	{
		data->file[i] = open(ft_ddquote(data->inout->file, 0), O_RDONLY);
		if (data->file[i] < 0)
			ft_perror("minishell : No such file or directory", 1);
		data->tab_args[i] = ft_dquote(ft_splitd(temp->cmd_arg, ' '), 0, 0);
		red_proc_2(data, temp, env, i);
		close_pipes(data);
		close(data->file[i]);
		data->tab_paths[i] = ft_check_arg(temp->command, env);
		if (temp->command != NULL)
		{
			if (data->inout->next == NULL)
				if (execve(data->tab_paths[i], data->tab_args[i], env) == -1)
					ft_perror("failed to exec in red2_proc\n", 1);
		}
		exit (0);
	}
}

void	red_proc_2(t_data *data, t_process *temp, char **env, int i)
{
	(void)env;
	if (data->inout->next == NULL)
	{
		if (ft_built_red2(i, data, temp))
			exit(0);
		if (dup2(data->file[i], STDIN_FILENO) == -1)
			ft_perror("dup2 n1 failed in red2_proc", 1);
	}
	if (data->inout->next == NULL && temp->out_next)
	{
		if (ft_built_red(i, data, temp))
			exit(0);
		if (dup2(data->fd[2 * (data->ind + 1) + 1], STDOUT_FILENO) == -1)
			ft_perror("dup2 n1 failed in red_proc", 1);
	}
	else if (temp->command != NULL && !data->inout->next)
		if (ft_built(i, data, temp))
			exit(0);
}

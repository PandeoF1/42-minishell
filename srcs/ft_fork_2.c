/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:13:33 by asaffroy          #+#    #+#             */
/*   Updated: 2022/02/01 13:48:57 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	red2_proc(t_data *data, t_process *temp, char **env, int i)
{
	data->pid1[i] = fork();
	if (data->pid1[i] < 0)
		ft_perror("forking failed\n", 1);
	if (data->pid1[i] == 0)
	{
		data->tab_args[i] = ft_dquote(ft_splitd(temp->cmd_arg, ' '), 0, 0);
		if (temp->out_next)
			data->fd[2 * (data->ind + 1) + 1] = open(ft_ddquote
					(data->inout->file, 0), O_RDWR | O_TRUNC | O_CREAT, 0644);
		else
			data->file[i] = open(ft_ddquote
					(data->inout->file, 0), O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (data->fd[2 * (data->ind + 1) + 1] < 0)
			ft_perror("\033[2K\r\033[0;31mError\033[0m : file creation failed", 1);
		red2_proc_2(data, temp, env, i);
		close_pipes(data);
		data->tab_paths[i] = ft_check_arg(temp->command, env);
		if (temp->command != NULL)
		{
			if (data->inout->next == NULL)
				if (execve(data->tab_paths[i], data->tab_args[i], env) == -1)
					ft_perror("failed to exec in red_proc\n", 1);
		}
		exit(0);
	}
}

void	red2_proc_2(t_data *data, t_process *temp, char **env, int i)
{
	(void)env;
	if (temp->in_prev != 0 || data->inout->red_prev == 1)
	{
		if (dup2(data->fd[2 * data->ind], STDIN_FILENO) == -1)
			ft_perror("dup2 n1 failed in pipe_proc", 1);
	}
	if (data->inout->next == NULL && temp->out_next)
	{
		if (ft_built_red(i, data, temp))
			exit (0);
		if (dup2(data->fd[2 * (data->ind + 1) + 1], STDOUT_FILENO) == -1)
			ft_perror("dup2 n2 failed in red_proc", 1);
	}
	else if (data->inout->next == NULL)
	{
		if (ft_built_red2(i, data, temp))
			exit (0);
		if (dup2(data->file[i], STDOUT_FILENO) == -1)
			ft_perror("dup2 n3 failed in red_proc", 1);
	}
	else
		if (ft_built(i, data, temp))
			exit (0);
}

void	red3_proc(t_data *data, t_process *temp, char **env, int i)
{
	(void)env;
	data->pid1[i] = fork();
	if (data->pid1[i] < 0)
		ft_perror("forking failed\n", 1);
	if (data->pid1[i] == 0)
	{
		data->tab_args[i] = ft_dquote(ft_splitd(temp->cmd_arg, ' '), 0, 0);
		if (dup2(data->fd[2 * (data->ind + 1) - 2], STDIN_FILENO) == -1)
			ft_perror("dup2 n1 failed in red3_proc", 1);
		red3_proc_2(data, temp, env, i);
		close_pipes(data);
		data->tab_paths[i] = ft_check_arg(temp->command, env);
		if (temp->command != NULL && !data->inout->next)
			if (execve(data->tab_paths[i], data->tab_args[i], env) == -1)
				ft_perror("failed to exec in red3_proc\n", 1);
		exit(0);
	}
}

void	red3_proc_2(t_data *data, t_process *temp, char **env, int i)
{
	(void)env;
	if (temp->out_next || (temp->inout->next && temp->inout->next->type != 3))
	{
		if (ft_built_red(i, data, temp))
			exit(0);
		if (dup2(data->fd[2 * (data->ind + 1) + 1], STDOUT_FILENO) == -1)
			ft_perror("dup2 n1 failed in red_proc", 1);
	}
	else if (!ft_is_command(temp->command, "exit"))
	{
		write(2, "exit\n", 5);
		exit(0);
	}
	else
		if (ft_built(i, data, temp))
			exit(0);
}

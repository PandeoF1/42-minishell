/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:02:14 by tnard             #+#    #+#             */
/*   Updated: 2022/04/20 11:05:40 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	red2_proc(t_data *data, t_process *temp, char **env, int i)
{
	data->pid1[i] = fork();
	if (data->pid1[i] < 0)
		ft_perror("forking failed", 1);
	if (data->pid1[i] == 0)
	{
		data->tab_args[i] = ft_dquote(ft_splitd(temp->cmd_arg, ' '), 0, 0);
		data->file[i] = open(ft_ddquote
				(data->inout->file, 0), O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (data->file[i] < 0)
			ft_perror("\033[2K\r\033[0;31mError\033[0m : file creation failed", 1);
		red2_proc_2(data, temp, env, i);
		close_pipes(data);
		data->tab_paths[i] = ft_check_arg(temp->command, env);
		if (temp->command != NULL)
		{
			if (data->inout->next == NULL)
				if (execve(data->tab_paths[i], data->tab_args[i], env) == -1)
					ft_perror("minishell : unable to perform this command", 1);
		}
		exit(0);
	}
}

void	red2_proc_2(t_data *data, t_process *temp, char **env, int i)
{
	int	check;

	(void)env;
	if (dup2(data->fd[2 * data->ind], STDIN_FILENO) == -1)
		ft_perror("dup2 n1 failed in red2_proc_2", 1);
	if (data->inout->next)
	{
		if (dup2(data->fd[2 * data->ind + 1], STDOUT_FILENO) == -1)
			ft_perror("dup2 n1 failed in red2_proc_2", 1);
	}
	else if (data->inout->next == NULL)
	{
		if (ft_built_red2(i, data, temp))
			exit (0);
		if (dup2(data->file[i], STDOUT_FILENO) == -1)
			ft_perror("dup2 n3 failed in red2_proc_2", 1);
	}
	else if (temp->command != NULL && !data->inout->next)
	{
		check = ft_built(i, data, temp);
		if (check == 2)
			exit (1);
		if (check == 1)
			exit (0);
	}
}

void	red3_proc(t_data *data, t_process *temp, char **env, int i)
{
	(void)env;
	data->pid1[i] = fork();
	if (data->pid1[i] < 0)
		ft_perror("forking failed", 1);
	if (data->pid1[i] == 0)
	{
		data->tab_args[i] = ft_dquote(ft_splitd(temp->cmd_arg, ' '), 0, 0);
		if (dup2(data->fd[2 * (data->ind + 1) - 2], STDIN_FILENO) == -1)
			ft_perror("dup2 n1 failed in red3_proc", 1);
		red3_proc_2(data, temp, env, i);
		close_pipes(data);
		if (temp->command != NULL && !data->inout->next)
		{
			data->tab_paths[i] = ft_check_arg(temp->command, env);
			if (execve(data->tab_paths[i], data->tab_args[i], env) == -1)
				ft_perror("minishell : unable to perform this command", 1);
		}
		exit(0);
	}
}

void	red3_proc_2(t_data *data, t_process *temp, char **env, int i)
{
	int	check;

	(void)env;
	if (temp->out_next || (temp->inout && temp->inout->next
			&& temp->inout->next->type != 3))
	{
		if (ft_built_red(i, data, temp))
			exit(0);
		if (dup2(data->fd[2 * (data->ind + 1) + 1], STDOUT_FILENO) == -1)
			ft_perror("dup2 n1 failed in red_proc", 1);
	}
	else if (temp->command != NULL && !ft_is_command(temp->command, "exit"))
	{
		write(2, "exit\n", 5);
		exit(0);
	}
	else if (temp->command != NULL && !data->inout->next)
	{
		check = ft_built(i, data, temp);
		if (check == 2)
			exit (1);
		if (check == 1)
			exit (0);
	}
}

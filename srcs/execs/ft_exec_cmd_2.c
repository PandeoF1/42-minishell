/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:06:17 by asaffroy          #+#    #+#             */
/*   Updated: 2022/02/14 10:41:56 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_execute_cmd_6(t_data *data, t_process *temp, char **env, int i)
{
	while (i >= 0 && (!data->inout))
	{
		pipe_proc(data, temp, env, i);
		temp = temp->next;
		data->ind++;
		i--;
		if (temp)
			data->inout = temp->inout;
	}
	while (i >= 0 && data->inout != 0 && data->inout->type == 2)
	{
		red2_proc(data, temp, env, i);
		data->inout = data->inout->next;
		if (!data->inout && !temp->out_next
			&& !ft_is_command(temp->command, "exit"))
			exit(0);
		i--;
	}
	i = ft_execute_cmd_7(data, temp, env, i);
	return (i);
}

int	ft_execute_cmd_7(t_data *data, t_process *temp, char **env, int i)
{
	int	check;
	int	check2;

	check = 0;
	check2 = 0;
	while (i >= 0 && data->inout != 0 && data->inout->type == 1)
	{
		if (check >= 0)
		{
			red_proc(data, temp, env, i);
			check = open(ft_ddquote(data->inout->file, 0), O_RDONLY);
			check2 = 1;
		}
		if (check2 == 1)
		{
			close(check);
			check2 = 0;
		}
		if (!data->inout && !temp->out_next
			&& !ft_is_command(temp->command, "exit"))
			exit(0);
		data->inout = data->inout->next;
		i--;
	}
	return (i);
}

void	ft_execute_cmd_8(t_data *data, t_inout *tmp)
{
	data->line = NULL;
	close(data->fd[2 * data->ind + 1]);
	if (pipe(data->fd + 2 * data->ind) < 0)
		ft_perror("pipe of heredoc failed", 1);
	while (data->inout->next != NULL && data->inout->next->type == 3)
		data->inout = data->inout->next;
	if (!ft_is_command(tmp->file, data->inout->file))
	{
		data->line = readline("> ");
		// if (!data->line)
		// 	return ;
		if (ft_is_command(data->line, data->inout->file))
		{
			write(data->fd[2 * data->ind + 1], data->line,
				ft_strlen(data->line));
			write(data->fd[2 * data->ind + 1], "\n", 1);
		}
	}
	while (ft_is_command(tmp->file, data->inout->file))
	{
		data->line = readline("> ");
		// if (!data->line)
		// 	return ;
		if (!ft_is_command(data->line, tmp->file)
			&& tmp->next && tmp->next->type == 3)
			tmp = tmp->next;
		if (ft_is_command(tmp->file, data->inout->file))
			free(data->line);
	}
}

void	ft_execute_cmd_9(t_data *data, t_process *temp, char **env, int i)
{
	while (ft_is_command(data->line, data->inout->file))
	{
		if (data->line)
			free (data->line);
		data->line = readline("> ");
		// if (!data->line)
		// 	return ;
		if (ft_is_command(data->line, data->inout->file))
		{
			write(data->fd[2 * data->ind + 1], data->line,
				ft_strlen(data->line));
			write(data->fd[2 * data->ind + 1], "\n", 1);
		}
	}
	free(data->line);
	red3_proc(data, temp, env, i);
	data->inout = data->inout->next;
	if (!data->inout && !temp->command)
		return ;
	if (!data->inout && !temp->out_next
		&& !ft_is_command(temp->command, "exit"))
		exit(0);
}

void	ft_execute_cmd_10(t_data *data, t_process *temp, char **env, int i)
{
	red4_proc(data, temp, env, i);
	data->inout = data->inout->next;
	if (!data->inout && !temp->out_next
		&& !ft_is_command(temp->command, "exit"))
		exit(0);
}

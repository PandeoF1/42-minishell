/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:06:17 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/13 10:09:52 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_execute_cmd_6(t_data *data, t_process **temp, char **env, int i)
{
	while (i >= 0 && (!data->inout))
	{
		pipe_proc(data, (*temp), env, i);
		(*temp) = (*temp)->next;
		data->ind++;
		i--;
		if ((*temp))
			data->inout = (*temp)->inout;
	}
	while (i >= 0 && data->inout != 0 && data->inout->type == 2)
	{
		red2_proc(data, (*temp), env, i);
		data->inout = data->inout->next;
		if (!data->inout && !(*temp)->out_next && (*temp)->command
			&& !ft_is_command((*temp)->command, "exit"))
			exit(0);
		i--;
	}
	i = ft_execute_cmd_7(data, &(*temp), env, i);
	return (i);
}

int	ft_execute_cmd_7(t_data *data, t_process **temp, char **env, int i)
{
	int	check;
	int	check2;

	check = 0;
	check2 = 0;
	while (i >= 0 && data->inout && data->inout->type == 1)
	{
		if (check >= 0)
		{
			red_proc(data, (*temp), env, i);
			check = open(ft_ddquote(data->inout->file, 0), O_RDONLY);
			check2 = 1;
		}
		if (check2 == 1)
		{
			close(check);
			check2 = 0;
		}
		if (!data->inout && !(*temp)->out_next && (*temp)->command
			&& !ft_is_command((*temp)->command, "exit"))
			exit(0);
		data->inout = data->inout->next;
		i--;
	}
	return (i);
}

void	ft_execute_cmd_8(t_data *data, t_inout *tmp)
{
	(void)tmp;
	data->line = NULL;
	close(data->fd[2 * data->ind + 1]);
	if (pipe(data->fd + 2 * data->ind) < 0)
		ft_perror("pipe of heredoc failed", 1);
	while (data->inout->next != NULL && data->inout->next->type == 3)
		data->inout = data->inout->next;
	write(data->fd[2 * data->ind + 1], data->inout->heredoc,
		ft_strlen(data->inout->heredoc));
}

void	ft_execute_cmd_9(t_data *data, t_process **temp, char **env, int i)
{
	red3_proc(data, (*temp), env, i);
	data->inout = data->inout->next;
	if (!data->inout && !(*temp)->command)
		return ;
	if (!data->inout && !(*temp)->out_next && (*temp)->command
		&& !ft_is_command((*temp)->command, "exit"))
		exit(0);
}

void	ft_execute_cmd_10(t_data *data, t_process *temp, char **env, int i)
{
	red4_proc(data, temp, env, i);
	data->inout = data->inout->next;
	if (!data->inout && !temp->out_next && temp->command
		&& !ft_is_command(temp->command, "exit"))
		exit(0);
}

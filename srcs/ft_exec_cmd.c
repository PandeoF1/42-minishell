/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:00:08 by asaffroy          #+#    #+#             */
/*   Updated: 2022/02/01 17:10:29 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_execute_cmd(t_process *proc, char **env, char **penv)
{
	t_data		data;
	t_process	*temp;
	t_inout		*temp2;
	int			i;

	// ft_printf("g : %d\n", g_exit);
	data.status = g_exit;
	g_exit = -1053;
	data.tab_env = penv;
	temp = proc;
	temp2 = temp->inout;
	i = ft_execute_cmd_2(temp, proc, temp2);
	if (!ft_malloc_struct(&data, i))
		ft_perror("malloc failed\n", 1);
	create_pipes(&data);
	if (ft_execute_cmd_5(&data, temp, env, i) == 0)
		return (0);
	i = data.j;
	close_pipes(&data);
	while (data.j >= 0)
	{
		waitpid(data.pid1[data.j], &data.status, 0);
		data.j--;
	}
	free_exec(&data, i);
	return (ft_status(&data));
}

int	ft_execute_cmd_2(t_process *temp, t_process *proc, t_inout *temp2)
{
	int	i;

	if (!temp2 || (temp2 && temp2->type == 3))
		i = 1;
	else
		i = 0;
	while (temp2)
	{
		if (temp2 && temp2->type != 3)
			i++;
		temp2 = temp2->next;
	}
	i = ft_execute_cmd_3(temp, temp2, i);
	temp = proc;
	return (i);
}

int	ft_execute_cmd_3(t_process *temp, t_inout *temp2, int i)
{
	while (temp->next != NULL)
	{
		temp = temp->next;
		temp2 = temp->inout;
		if (temp2)
		{
			while (temp2)
			{
				if (temp2 && temp2->type != 3)
				{
					i++;
					temp2 = temp2->next;
				}
				if (temp2 && temp2->type == 3)
				{
					i++;
					while (temp2 && temp2->type == 3)
						temp2 = temp2->next;
				}
			}
		}
		else if (temp)
			i++;
	}
	return (i);
}

void	ft_execute_cmd_4(t_data *data, t_process *temp, char **env, int i)
{
	t_inout		*tmp;

	while (i >= 0)
	{
		if (!data->inout)
			data->inout = temp->inout;
		i = ft_execute_cmd_6(data, temp, env, i);
		if (i >= 0 && data->inout != 0 && data->inout->type == 3)
		{
			tmp = data->inout;
			ft_execute_cmd_8(data, tmp);
			ft_execute_cmd_9(data, temp, env, i);
			i--;
		}
		if (i >= 0 && data->inout != 0 && data->inout->type == 4)
		{
			ft_execute_cmd_10(data, temp, env, i);
			i--;
		}
		if (temp && temp->inout && !data->inout)
		{
			temp = temp->next;
			data->ind++;
		}
	}
}

int	ft_execute_cmd_5(t_data *data, t_process *temp, char **env, int i)
{
	if (i == 1 && temp->inout == 0)
	{
		if (ft_execute_cmd_11(temp, data, i, env) != 1)
			return (0);
	}
	else
	{
		i--;
		data->j = i;
		data->ind = 0;
		data->inout = NULL;
		ft_execute_cmd_4(data, temp, env, i);
	}
	return (1);
}

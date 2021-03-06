/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:16:35 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/05 09:50:30 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_malloc_struct(t_data *data, int i)
{
	int	j;

	j = -1;
	data->line = NULL;
	data->fd = (int *)malloc(sizeof(int) * i * 2);
	if (!data->fd)
		return (0);
	data->tab_args = malloc(sizeof(char **) * i);
	if (!data->tab_args)
		return (0);
	data->tab_paths = malloc(sizeof(char *) * i);
	if (!data->tab_paths)
		return (0);
	data->file = malloc(sizeof(int) * i);
	if (!data->file)
		return (0);
	data->charset[0] = '\'';
	data->charset[1] = '\"';
	data->charset[2] = ' ';
	data->charset[3] = '\0';
	data->nb_cmd = i;
	data->pid1 = malloc(sizeof(pid_t) * i);
	return (1);
}

void	create_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmd)
	{
		if (pipe(data->fd + 2 * i) < 0)
			ft_perror("fail , lets free", 1);
		i++;
	}
}

void	close_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < 2 * data->nb_cmd)
	{
		close(data->fd[i]);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 11:15:22 by asaffroy          #+#    #+#             */
/*   Updated: 2022/02/01 11:54:51 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_exec(t_data *data, int i)
{
	int			j;

	i = 0;
	//temp = proc;
	j = 0;
	//while (++i && temp->next != NULL)
		//temp = temp->next;
	/*while (i > 0)
	{
		j = -1;
		if (temp->cmd_arg != NULL)
			free(temp->cmd_arg);
		if (temp->command != NULL)
			free(temp->command);
		if (temp->type != NULL)
			free(temp->type);
		free(temp);
		i--;
		temp = proc;
		while (++j < i - 1)
			temp = temp->next;
	}*/
	if (data->fd)
		free(data->fd);
	if (data->pid1)
		free(data->pid1);
	if (data->tab_args)
		free(data->tab_args);
	// if (data->tab_paths) //need to be free
	// {
	// 	while (data->tab_paths[j] != NULL)
	// 	{
	// 		free(data->tab_paths[j]);
	// 		ft_printf("freed\n");
	// 		j++;
	// 	}
	// }
	if (data->tab_paths) //need to be free
		free(data->tab_paths);
	// j = -1; need to be free
	// while (data->file[++j])
	// 	free(data->file[j]);
	if (data->file)
		free(data->file); // need to be free
	// g_exit = data->status;
}

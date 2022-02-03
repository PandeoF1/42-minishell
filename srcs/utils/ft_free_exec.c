/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 11:15:22 by asaffroy          #+#    #+#             */
/*   Updated: 2022/02/03 09:45:17 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_exec(t_data *data, int i)
{
	i = 0;
	if (data->fd)
		free(data->fd);
	if (data->file)
		free(data->file);
	if (data->pid1)
		free(data->pid1);
	if (data->tab_paths)
		free(data->tab_paths);
	if (data->tab_args)
		free(data->tab_args);
}

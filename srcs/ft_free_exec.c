/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 11:15:22 by asaffroy          #+#    #+#             */
/*   Updated: 2022/02/01 17:10:01 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_exec(t_data *data, int i)
{
	i = 0;
	ft_printf("uwu\n");
	if (data->fd)
		free(data->fd);
	ft_printf("a\n");
	if (data->file)
		free(data->file);
	ft_printf("a\n");
	if (data->pid1)
		free(data->pid1);
	ft_printf("a\n");
	if (data->tab_paths)
		ft_free_split(data->tab_paths);
	ft_printf("a\n");
	if (data->tab_env)
		ft_free_split(data->tab_env);
	ft_printf("a\n");
	if (data->line)
		free(data->line);
	ft_printf("a\n");
	if (data->tab_args)
		while (data->tab_args[i])
			ft_free_split(data->tab_args[i++]);
	ft_printf("a\n");
}
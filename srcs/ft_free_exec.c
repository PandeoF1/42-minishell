/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 11:15:22 by asaffroy          #+#    #+#             */
/*   Updated: 2022/02/02 13:12:55 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_exec(t_data *data, int i)
{
	i = 0;
	//ft_printf("uwu\n");
	if (data->fd)
		free(data->fd);
	//ft_printf("a0\n");
	if (data->file)
		free(data->file);
	//ft_printf("a1\n");
	if (data->pid1)
		free(data->pid1);
	//ft_printf("a\n");
	//if (data->tab_paths)
	// 	ft_free_split(data->tab_paths);
	//ft_printf("a\n");
	// if (data->tab_env)
	// 	free(data->tab_env);
		//ft_free_split(data->tab_env);
	if (data->tab_paths)
		free(data->tab_paths);
	//free(data->tab_env);
	//ft_printf("a2\n");
	if (data->line)
		free(data->line);
	// ft_printf("a\n");
	// if (data->tab_args[0] != 0)
	// 	while (data->tab_args[i])
	// 	{
	// 		ft_printf("atta boiiii\n");
	 		//ft_free_split(data->tab_args[i++]);
	// 		//ft_printf("%d\n", i);
	// 	}
	if (data->tab_args)
		free(data->tab_args);
}

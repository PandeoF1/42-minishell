/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:05:22 by tnard             #+#    #+#             */
/*   Updated: 2022/01/03 15:05:22 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_free(t_process **process)
{
	t_process	*tmp;

	while ((*process))
	{
		tmp = (*process)->next;
		if ((*process)->command)
			free((*process)->command);
		if ((*process)->cmd_arg)
			free((*process)->cmd_arg);
		if ((*process)->path)
			free((*process)->path);
		if ((*process)->args)
			free((*process)->args);
		if ((*process)->input)
			free((*process)->input);
		if ((*process)->inout_file)
			free((*process)->inout_file);
		if ((*process)->in_file)
			free((*process)->in_file);
		if ((*process)->out_file)
			free((*process)->out_file);
		if ((*process)->type)
			free((*process)->type);
		free(*process);
		(*process) = tmp;
	}
}

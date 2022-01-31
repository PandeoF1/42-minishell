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

int	ft_free_split_r(char **split, int x)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (x);
}

void	ft_free_inout(t_inout **inout)
{
	t_inout	*tmp;
	t_inout	*tmp2;

	tmp = *inout;
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp->file);
		free(tmp);
		tmp = tmp2;
	}
	*inout = NULL;
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
		if ((*process)->type)
			free((*process)->type);
		if ((*process)->inout)
			ft_free_inout(&(*process)->inout);
		free(*process);
		(*process) = tmp;
	}
}

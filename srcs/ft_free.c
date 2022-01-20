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

void	ft_safe_free(t_process **process)
{
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
}

void	ft_free(t_process **process)
{
	t_process	*tmp;

	while ((*process))
	{
		tmp = (*process)->next;
		ft_safe_free(process);
		ft_free_inout(&(*process)->inout);
		free(*process);
		(*process) = tmp;
	}
}

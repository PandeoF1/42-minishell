/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 22:48:07 by tnard             #+#    #+#             */
/*   Updated: 2022/01/31 22:48:07 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
*	ft_structlen(t_process *process)
*	desc : count the number of struct in struct
*/

int	ft_structlen(t_process *process)
{
	t_process	*tmp;
	int			len;

	tmp = process;
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

/*
*	ft_config_inout(t_inout **inout)
*	desc : configure the output and input on the inout
*/

void	ft_config_inout(t_inout *inout)
{
	t_inout	*tmp;
	int		x;

	x = 0;
	tmp = inout;
	while (tmp)
	{
		if (x)
		{
			x = 0;
			tmp->red_prev = 1;
		}
		if (tmp->type == 3)
			x = 1;
		tmp = tmp->next;
	}
}

/*
*	ft_clear_process(t_process *process)
*	desc : patch all command null
*/

void	ft_clear_process(t_process *process)
{
	char		**splitd;

	if (ft_strlen(process->command) == 0 && ft_strlen(process->cmd_arg) != 0)
	{
		splitd = ft_splitd(process->cmd_arg, ' ');
		process->command = ft_strdup(splitd[0]);
		ft_free_split(splitd);
	}
}

/*
*	ft_config_process(t_process *process)
*	desc : configure the output and input on the process
*/

void	ft_config_process(t_process *process, int x, int next, int inout)
{
	t_process	*tmp;

	tmp = process;
	while (tmp && ++x < ft_structlen(process))
	{
		if (tmp->type && tmp->type[0] == '|')
		{
			if (x != 0)
				tmp->in_prev = 1;
			tmp->out_next = 1;
			next = 1;
			if (tmp->inout)
				inout = 1;
		}
		else if (next)
		{
			tmp->in_prev = 1;
			inout = 0;
			next = 0;
		}
		if (tmp->inout)
			ft_config_inout(tmp->inout);
		ft_clear_process(tmp);
		tmp = tmp->next;
	}
}

/*
* ft_space(str)
* desc : compare number of space with strlen
* params : string
*/

int	ft_space(char *str)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			x++;
		i++;
	}
	if (x == i)
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 15:33:50 by tnard             #+#    #+#             */
/*   Updated: 2022/01/05 15:33:50 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * ft_malloc_process(t_process **prev)
 * desc : return the next of t_process malloced
 * params : prev to add next malloced
 */

static void	ft_malloc_process(t_process **prev)
{
	t_process	*new;

	new = malloc(sizeof(t_process));
	if (!new)
		return ;
	new->inout = NULL;
	new->command = NULL;
	new->cmd_arg = NULL;
	new->out_next = 0;
	new->in_prev = 0;
	new->red_prev = 0;
	new->type = NULL;
	new->next = NULL;
	if (*prev)
		(*prev)->next = new;
	else
		(*prev) = new;
}

/*
 * ft_create_inout(void)
 * desc : return a malloced struct of t_inout
 * params : void
 */

t_inout	*ft_create_inout(void)
{
	t_inout	*inout;

	inout = malloc(sizeof(t_inout));
	if (!inout)
		return (NULL);
	inout->type = 0;
	inout->file = NULL;
	inout->red_prev = 0;
	inout->next = NULL;
	return (inout);
}

/*
 * ft_prep_process(t_process **process, int x)
 * desc : just a small part of ft_create_process
*/

int	ft_cmd_process(t_process **process, char **split, int x, int y)
{
	y = ft_w_is_space(split[x]);
	(*process)->command = ft_strndup(split[x] + y, ft_word_len(split[x] + y));
	(*process)->cmd_arg = ft_strdup((*process)->command);
	(*process)->cmd_arg = ft_strnjoin((*process)->cmd_arg, " ", 1);
	y += ft_word_len(split[x] + y);
	return (y);
}

/*
 * ft_prep_process(t_process **process, int x)
 * desc : just a small part of ft_create_process
 */

void	ft_prep_process(t_process **process, int x, t_process **tmp)
{
	if (x == 0)
	{
		(*tmp) = malloc(sizeof(t_process));
		if (!(*tmp))
			return ;
		ft_malloc_process(tmp);
		(*process) = (*tmp)->next;
		free((*tmp));
	}
	else
	{
		ft_malloc_process(process);
		(*process) = (*process)->next;
	}
	if (x == 0)
		(*tmp) = (*process);
}

/*
 * ft_create_process(char *str, int (*status))
 * desc : parse the string and create all process
 * params : str to parse and status to return
 * todo : free(process) when error and some thing else
 * todo : split of "|"
 */

t_process	*ft_create_process(int x, int y, char **split)
{
	t_process	*process;
	t_process	*tmp;

	while (split[++x])
	{
		ft_prep_process(&process, x, &tmp);
		y = ft_cmd_process(&process, split, x, 0);
		while (split[x][y])
		{
			y += ft_w_is_space(split[x] + y);
			if (split[x][y] == '<' || split[x][y] == '>')
				ft_quote(&process, x, &y, split);
			else if (split[x][y])
			{
				process->cmd_arg = ft_strnjoin(process->cmd_arg,
						split[x] + y, ft_len_quote(split[x] + y));
				process->cmd_arg = ft_strnjoin(process->cmd_arg, " ", 1);
				y += ft_len_quote(split[x] + y);
			}
		}
		if (split[x + 1])
			process->type = ft_strdup("|");
	}
	ft_free_split(split);
	return (tmp);
}

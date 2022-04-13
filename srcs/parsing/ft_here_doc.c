/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:25:16 by tnard             #+#    #+#             */
/*   Updated: 2022/04/13 10:28:06 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_heredoc_process_2(t_inout *inout, char *ctmp, char *rd)
{
	rd = readline("> ");
	if (ctmp)
		free(ctmp);
	ctmp = ft_strdup("");
	while (rd)
	{
		if (!ft_is_command(rd, inout->file))
		{
			inout->heredoc = ctmp;
			free(rd);
			break ;
		}
		else
		{
			ctmp = ft_strnjoin(ctmp, rd, ft_strlen(rd));
			ctmp = ft_strnjoin(ctmp, "\n", 1);
		}
		free(rd);
		rd = readline("> ");
	}
	if (!rd)
	{
		inout->heredoc = ctmp;
		free(rd);
	}
}

void	ft_heredoc_process(t_process *process)
{
	t_process	*tmp;
	t_inout		*inout;
	char		*rd;
	char		*ctmp;

	tmp = process;
	ctmp = NULL;
	rd = NULL;
	while (tmp)
	{
		if (tmp->command && tmp->inout)
		{
			inout = tmp->inout;
			while (inout)
			{
				inout->heredoc = NULL;
				if (inout->type == 3)
					ft_heredoc_process_2(inout, ctmp, rd);
				inout = inout->next;
			}
		}
		tmp = tmp->next;
	}
}

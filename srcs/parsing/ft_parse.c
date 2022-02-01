/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 12:03:03 by tnard             #+#    #+#             */
/*   Updated: 2022/01/03 12:03:03 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_clean_process(t_process *process)
{
	t_process	*tmp;

	tmp = process;
	while (tmp)
	{
		if (tmp->command && ft_strlen(tmp->command) == 0)
		{
			free(tmp->command);
			tmp->command = NULL;
		}
		tmp = tmp->next;
	}
}

void	ft_check_in_split(char **splitd, int x, int *y, char *c)
{
	if (splitd[x][(*y)] == '"' || splitd[x][(*y)] == '\'')
	{
		*c = splitd[x][(*y)++];
		while (splitd[x][*y] && splitd[x][(*y)] != *c)
			(*y)++;
	}
}

int	ft_check_split(char	*str, int x, int y, int test)
{
	char	**splitd;
	char	c;

	splitd = ft_splitd(str, ' ');
	while (splitd[++x])
	{
		y = -1;
		while (splitd[x][++y])
		{
			ft_check_in_split(splitd, x, &y, &c);
			if (splitd[x][y])
			{
				if (splitd[x][y] == '|')
					test++;
				else
					test = 0;
				if (test == 2 || (splitd[x][y + 1]
					&& splitd[x][y] == '|' && splitd[x][y + 1] == '|'))
					return (ft_free_split_r(splitd, 0));
			}
		}
	}
	if (test != 0 || splitd[0][0] == '|')
		return (ft_free_split_r(splitd, 0));
	return (ft_free_split_r(splitd, 1));
}

/*
* ft_parse_command(str)
* desc : parse the command and return the struct
* params : str to parse
* todo : free(process)
*/

void	ft_parse_command(char *str, char **env, char **penv)
{
	t_process	*process;
	t_process	*tmp;
	t_inout		*tmpi;
	int			x;

	x = 0;
	if (ft_strlen(str) == 0 || ft_space(str) == 0)
		return ;
	if (ft_check_quote(str) && ft_check_split(str, -1, 0, 0))
	{
		process = ft_create_process(-1, 0, ft_splitd(str, '|'));
		if (ft_check_process(process))
		{
			ft_config_process(process, -1, 0, 0);
			ft_clean_process(process);
			 tmp = process;
			 while (process)
			 {
			 	ft_printf("---- parse ----\n");
			 	ft_printf("command : %s.\n", process->command);
			 	ft_printf("cmd_arg : %s.\n", process->cmd_arg);
			 	ft_printf("out_next : %d.\n", process->out_next);
			 	ft_printf("in_prev : %d.\n", process->in_prev);
			 	ft_printf("type : %s.\n", process->type);
			 	if (process->inout)
			 	{
			 		tmpi = process->inout;
			 		ft_printf("--- INOUT ----\n");
			 		while (tmpi)
			 		{
			 			ft_printf("-------\n");
			 			if (tmpi->file)
			 				ft_printf("inout : %s.\n", tmpi->file);
			 			ft_printf("type : %d.\n", tmpi->type);
			 			ft_printf("red_prev : %d.\n", tmpi->red_prev);
			 			ft_printf("-------\n");
			 			tmpi = tmpi->next;
			 		}
			 		ft_printf("--- INOUT ----\n");
			 	}
			 	ft_printf("---- end parse ----\n");
			 	process = process->next;
			 }
			 process = tmp;
			g_exit = ft_execute_cmd(process, env, penv);
			x = 1;
		}
		else
			ft_printf("minishell: syntax error near token `newline'\n");
		ft_free(&process);
	}
	else
		ft_printf("minishell: syntax error with open quotes or > | <\n");
	if (x == 0)
		g_exit = 258;
}

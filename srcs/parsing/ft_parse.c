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
*	ft_config_process(t_process *process)
*	desc : configure the output and input on the process
*/

void	ft_config_process(t_process *process)
{
	t_process	*tmp;
	int			x;
	int			len;
	int			next;

	x = -1;
	next = 0;
	tmp = process;
	len = ft_structlen(tmp);
	while (tmp && ++x < len)
	{
		if (tmp->type && tmp->type[0] == '|')
		{
			if (x != 0)
				tmp->in_prev = 1;
			tmp->out_next = 1;
			next = 1;
		}
		else if (next)
		{
			tmp->in_prev = 1;
			next = 0;
		}
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

/*
* ft_parse_command(str)
* desc : parse the command and return the struct
* params : str to parse
* todo : free(process)
*/

void	ft_parse_command(char *str, char *env)
{
	t_process	*process;
	t_process	*tmp;
	t_inout		*tmpi;
	int			x;

	x = 0;
	if (ft_strlen(str) == 0 || ft_space(str) == 0)
		return ;
	if (ft_check_quote(str))
	{
		process = ft_create_process(str, -1, 0, ft_splitd(str, '|'));
		if (1)
		{
			ft_config_process(process);
			tmp = process;
			while (process)
			{
				ft_printf("---- parse ----\n");
				ft_printf("command : %s.\n", process->command);
				ft_printf("cmd_arg : %s.\n", process->cmd_arg);
				ft_printf("path : %s.\n", process->path);
				ft_printf("args : %s.\n", process->args);
				ft_printf("inout : %s.\n", process->inout_file);
				ft_printf("in : %s.\n", process->inout_file);
				ft_printf("out : %s.\n", process->inout_file);
				ft_printf("out_next : %d.\n", process->out_next);
				ft_printf("out_prev : %d.\n", process->out_prev);
				ft_printf("in_prev : %d.\n", process->in_prev);
				ft_printf("in_next : %d.\n", process->in_next);
				ft_printf("input : %s.\n", process->input);
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
						if (tmpi->type)
							ft_printf("type : %d.\n", tmpi->type);
						ft_printf("-------\n");
						tmpi = tmpi->next;
					}
					ft_printf("--- INOUT ----\n");
				}
				ft_printf("---- end parse ----\n");
				process = process->next;
			}
			process = tmp;
			ft_execute_cmd(process, env);
		}
		else
			ft_printf("minishell: syntax error near token `newline'\n");
		ft_free(&process);
	}
	else
		ft_printf("minishell: syntax error with open quotes\n");
}

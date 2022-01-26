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

int	ft_check_split(char	*str, int x, int y)
{
	char	**splitd;
	int		test;
	char	c;

	test = 0;
	splitd = ft_splitd(str, ' ');
	while (splitd[x])
	{
		y = 0;
		while (splitd[x][y])
		{
			if (splitd[x][y] == '"' || splitd[x][y] == '\'')
			{
				c = splitd[x][y];
				y++;
				while (splitd[x][y] && splitd[x][y] != c)
					y++;
			}
			if (splitd[x][y])
			{
				if (splitd[x][y] == '|')
					test++;
				else
					test = 0;
				if (test == 2 || (splitd[x][y + 1] &&  	splitd[x][y] == '|' && splitd[x][y + 1] == '|'))
				{
					ft_free_split(splitd);
					return (0);
				}
			}
			y++;
		}
		x++;
	}
	if (test != 0 || splitd[0][0] == '|')
	{
		ft_free_split(splitd);
		return (0);
	}
	ft_free_split(splitd);
	return (1);
}

/*
* ft_parse_command(str)
* desc : parse the command and return the struct
* params : str to parse
* todo : free(process)
*/

void	ft_parse_command(char *str, char **env)
{
	t_process	*process;
	t_process	*tmp;
	t_inout		*tmpi;
	int			x;

	x = 0;
	if (ft_strlen(str) == 0 || ft_space(str) == 0)
		return ;
	if (ft_check_quote(str) && ft_check_split(str, 0 , 0))
	{
		process = ft_create_process(-1, 0, ft_splitd(str, '|'));
		if (ft_check_process(process))
		{
			ft_config_process(process, -1, 0, 0);
			ft_clean_process(process);
			//  tmp = process;
			//  while (process)
			//  {
			//  	ft_printf("---- parse ----\n");
			//  	ft_printf("command : %s.\n", process->command);
			//  	ft_printf("cmd_arg : %s.\n", process->cmd_arg);
			//  	ft_printf("out_next : %d.\n", process->out_next);
			//  	ft_printf("in_prev : %d.\n", process->in_prev);
			//  	ft_printf("type : %s.\n", process->type);
			//  	if (process->inout)
			//  	{
			//  		tmpi = process->inout;
			//  		ft_printf("--- INOUT ----\n");
			//  		while (tmpi)
			//  		{
			//  			ft_printf("-------\n");
			//  			if (tmpi->file)
			//  				ft_printf("inout : %s.\n", tmpi->file);
			//  			ft_printf("type : %d.\n", tmpi->type);
			//  			ft_printf("red_prev : %d.\n", tmpi->red_prev);
			//  			ft_printf("-------\n");
			//  			tmpi = tmpi->next;
			//  		}
			//  		ft_printf("--- INOUT ----\n");
			//  	}
			//  	ft_printf("---- end parse ----\n");
			//  	process = process->next;
			//  }
			//  process = tmp;
			ft_execute_cmd(process, env);
		}
		else
			ft_printf("minishell: syntax error near token `newline'\n");
		ft_free(&process);
	}
	else
		ft_printf("minishell: syntax error with open quotes or > | <\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:21:17 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/12 11:11:53 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

long long	ft_atol(const char *str)
{
	long long	i;
	long long	nbr;
	int			revert;

	i = 0;
	nbr = 0;
	revert = 0;
	while (str[i] != '\0' && (str[i] == 32 || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] != '\0' && str[i] == '-')
	{
		revert = 1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0' && ft_isdigit(str[i]))
		nbr = (nbr * 10) + (str[i++] - '0');
	if (revert == 1)
		return (-nbr);
	return (nbr);
}

void	ft_exit_error(int i, char **t, char ***splited, t_process *temp)
{
	if (i != 0)
		free(*t);
	ft_free_split(*splited);
	if (!temp->out_next)
		write(2, "minishell: numeric argument required\n", 37);
	exit(255);
}

void	ft_exit_switch(char **t, char ***splited, t_process *temp)
{
	char	*llmax;
	char	*llmax_plus;

	llmax = "9223372036854775807";
	llmax_plus = "+9223372036854775807";
	if ((((*splited)[0][0] == '-' || (*splited)[0][0] == '+')
		&& ft_strlen((*splited)[0]) == ft_strlen(llmax_plus))
		|| (ft_strlen((*splited)[0]) == ft_strlen(llmax)))
	{
		if ((*splited)[0][0] == '-')
			ft_llmin(1, &(*t), &(*splited), temp);
		else if ((*splited)[0][0] == '+')
			ft_llmax_plus(1, &(*t), &(*splited), temp);
		else
			ft_llmax(1, &(*t), &(*splited), temp);
	}
	else if ((((*splited)[0][0] == '-' || (*splited)[0][0] == '+')
		&& ft_strlen((*splited)[0]) < ft_strlen("+9223372036854775807"))
		|| (ft_strlen((*splited)[0]) < ft_strlen("9223372036854775807")))
	{
		ft_return_exit(&(*t), &(*splited));
	}
	else
		ft_exit_error(1, &(*t), &(*splited), temp);
}

int	ft_exit(t_process *temp, t_data *data)
{
	char		**splited;
	char		*t;
	int			i;

	if (!temp->out_next && !temp->in_prev)
		write(2, "exit\n", 5);
	splited = ft_dquote(ft_splitd(temp->cmd_arg, ' '), 0, 0);
	if (splited[1] && splited[2])
	{
		if (!temp->out_next)
			write(2, "minishell: exit: too many arguments\n", 36);
		ft_free_split(splited);
		return (2);
	}
	if (temp->cmd_arg[5])
	{
		ft_check_exit(0, &t, &splited, temp);
		i = 1;
		ft_exit_switch(&t, &splited, temp);
	}
	ft_free_split(splited);
	exit(data->status);
}

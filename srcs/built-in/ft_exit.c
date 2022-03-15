/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:21:17 by asaffroy          #+#    #+#             */
/*   Updated: 2022/03/15 17:55:19 by asaffroy         ###   ########lyon.fr   */
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

void	ft_exit(t_process *temp, t_data *data)
{
	char	**splited;
	char	*t;
	int		i;
	int		sign;

	if (!temp->out_next && !temp->in_prev)
		write(2, "exit\n", 5);
	splited = ft_dquote(ft_splitd(temp->cmd_arg, ' '), 0, 0);
	if (splited[2])
	{
		free(splited);
		if (!temp->out_next && !temp->in_prev)
			write(2, "minishell: numeric argument required\n", 37);
		exit(255);
	}
	if (temp->cmd_arg[5])
	{
		t = splited[1];
		free(splited);
		splited = ft_splitd(t, ' ');
		if (splited[1])
		{
			free(splited);
			if (!temp->out_next && !temp->in_prev)
				write(2, "minishell: numeric argument required\n", 37);
			exit(255);
		}
		i = 0;
		sign = 1;
		while (splited[0][i])
		{
			if (i == 0 && splited[0][i] == '-')
				sign = -1;
			if (!((i == 0 && (((splited[0][i] == '-' || splited[0][i] == '+') && splited[0][1]) || (splited[0][i] - 48 >= 0 && splited[0][i] - 48 <= 9))) || (i != 0 && splited[0][i] - 48 >= 0 && splited[0][i] - 48 <= 9)))
			{
				free(splited);
				if (!temp->out_next && !temp->in_prev)
					write(2, "minishell: numeric argument required\n", 37);
				exit(255);
			}
			i++;
		}
		if (((splited[0][0] == '-' || splited[0][0] == '+')
			&& ft_strlen(splited[0]) <= ft_strlen("+9223372036854775807"))
			|| (ft_strlen(splited[0]) <= ft_strlen("9223372036854775807")))
		{
			free(splited);
			exit(ft_atol(splited[0]) % 256);
		}
		else
		{
			free(splited);
			if (!temp->out_next && !temp->in_prev)
				write(2, "minishell: numeric argument required\n", 37);
			exit(255);
		}
	}
	free(splited);
	exit(data->status);
}

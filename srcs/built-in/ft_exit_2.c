/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:54:30 by asaffroy          #+#    #+#             */
/*   Updated: 2022/03/16 13:56:25 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_check_exit(int i, char **t, char ***splited, t_process *temp)
{
	(*t) = ft_strdup((*splited)[1]);
	ft_free_split((*splited));
	(*splited) = ft_split((*t), ' ');
	if ((*splited)[1])
		ft_exit_error(1, &(*t), &(*splited), temp);
	while ((*splited)[0][i])
	{
		if (!((i == 0 && ((((*splited)[0][i] == '-' \
			|| (*splited)[0][i] == '+') && (*splited)[0][1])
			|| ((*splited)[0][i] - 48 >= 0 && (*splited)[0][i] - 48 <= 9)))
			|| (i != 0 && (*splited)[0][i] - 48 >= 0
			&& (*splited)[0][i] - 48 <= 9)))
			ft_exit_error(1, &(*t), &(*splited), temp);
		i++;
	}
}

void	ft_return_exit(char **t, char ***splited)
{
	long long	ret;

	free(*t);
	ret = ft_atol((*splited)[0]);
	ft_free_split((*splited));
	exit(ret % 256);
}

void	ft_llmax_plus(int i, char **t, char ***splited, t_process *temp)
{
	char		*llmax_plus;

	llmax_plus = "+9223372036854775807";
	while (i < ft_strlen(llmax_plus))
	{
		if ((*splited)[0][i] > llmax_plus[i])
			ft_exit_error(1, &(*t), &(*splited), temp);
		i++;
	}
	ft_return_exit(&(*t), &(*splited));
}

void	ft_llmax(int i, char **t, char ***splited, t_process *temp)
{
	char		*llmax;

	llmax = "9223372036854775807";
	while (i < ft_strlen(llmax))
	{
		if ((*splited)[0][i] > llmax[i])
			ft_exit_error(1, &(*t), &(*splited), temp);
		i++;
	}
	ft_return_exit(&(*t), &(*splited));
}

void	ft_llmin(int i, char **t, char ***splited, t_process *temp)
{
	char		*llmin;

	llmin = "-9223372036854775808";
	while (i < ft_strlen(llmin))
	{
		if ((*splited)[0][i] > llmin[i])
			ft_exit_error(1, &(*t), &(*splited), temp);
		i++;
	}
	ft_return_exit(&(*t), &(*splited));
}

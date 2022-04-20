/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaffroy <asaffroy@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 14:11:51 by asaffroy          #+#    #+#             */
/*   Updated: 2022/04/20 10:58:47 by asaffroy         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_perror(char *str, int code)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	write (1, "\n", 1);
	exit(code);
}

void	ft_ffailed(char *str, int code, t_data *data)
{
	write(1, str, ft_strlen(str));
	data->status = code;
	data->fork_status = -1;
}

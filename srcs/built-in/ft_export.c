/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 13:46:05 by tnard             #+#    #+#             */
/*   Updated: 2022/01/26 13:46:06 by tnard            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_export(t_data *data, char **arg, int fd)
{
	char	**tmp;

	tmp = data->tab_env;
	ft_printf("test : %s", (*tmp)[0]);
	return (1);
}
